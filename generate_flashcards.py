#!/usr/bin/env python3
"""
cmd-->this is used for script.google input
python3 generate_flashcards.py README.md imp.md *.c --out flashcards.js
generate_flashcards.py

Parses .md, .c and .svg files and generates a JS flashcards array.

  .md files  -> ## / ### headings become Q, content below becomes A
  .c files   -> Q: "Write <filename> code?",     A: full source code
  .svg files -> Q: "Write <filename> SVG code?", A: description + raw SVG code

Usage:
    python3 readme_to_flashcards.py README.md imp.md *.c doc/*.svg --out flashcards.js
"""

import sys
import re
import glob
import os


# ─── Helpers ────────────────────────────────────────────────────────────────

def escape_backtick(text):
    text = text.replace("\\", "\\\\")
    text = text.replace("`", "\\`")
    text = text.replace("${", "\\${")
    return text.strip()

def clean_heading(text):
    text = re.sub(r'\*{1,2}([^*]+)\*{1,2}', r'\1', text)
    text = re.sub(r'`([^`]+)`', r'\1', text)
    text = text.strip().strip('"').strip("'").strip()
    if not text.endswith('?'):
        text = text + '?'
    return text

def clean_answer(text):
    text = re.sub(r'\n{3,}', '\n\n', text)
    return text.strip()


# ─── Parsers ─────────────────────────────────────────────────────────────────

def parse_readme(content):
    lines = content.split('\n')
    cards = []
    current_q = None
    current_a_lines = []

    for line in lines:
        heading_match = re.match(r'^(#{2,3})\s+(.+)$', line)
        if heading_match:
            if current_q is not None:
                answer = clean_answer('\n'.join(current_a_lines))
                if answer:
                    cards.append((current_q, answer))
            current_q = clean_heading(heading_match.group(2))
            current_a_lines = []
        else:
            if current_q is not None:
                current_a_lines.append(line)

    if current_q is not None:
        answer = clean_answer('\n'.join(current_a_lines))
        if answer:
            cards.append((current_q, answer))

    return cards


def parse_c_file(filename, content):
    name = os.path.splitext(filename)[0]
    question = f"Write {name} code?"
    return [(question, content.strip())]


def parse_svg_file(filename, content):
    name = os.path.splitext(filename)[0]
    question = f"Write {name} SVG code?"

    # Try to extract description from SVG metadata
    title_match = re.search(r'<title[^>]*>(.*?)</title>', content, re.IGNORECASE | re.DOTALL)
    desc_match  = re.search(r'<desc[^>]*>(.*?)</desc>',  content, re.IGNORECASE | re.DOTALL)

    description_parts = []
    if title_match:
        t = title_match.group(1).strip()
        if t:
            description_parts.append(f"Title: {t}")
    if desc_match:
        d = desc_match.group(1).strip()
        if d:
            description_parts.append(f"Description: {d}")

    # Fallback: readable name from filename
    if not description_parts:
        readable = name.replace("_", " ").replace("-", " ").title()
        description_parts.append(f"Diagram: {readable}")

    description = "\n".join(description_parts)
    answer = f"{description}\n\n{content.strip()}"
    return [(question, answer)]


# ─── JS Output ───────────────────────────────────────────────────────────────

def to_js(cards):
    lines = ["const FLASHCARDS = ["]
    for q, a in cards:
        q_escaped = q.replace('"', '\\"')
        a_escaped = escape_backtick(a)
        lines.append("  {")
        lines.append(f'    q: "{q_escaped}",')
        lines.append(f'    a: `{a_escaped}`')
        lines.append("  },")
    lines.append("];")
    lines.append("")
    lines.append(f"// Total: {len(cards)} flashcards")
    return "\n".join(lines)


# ─── Main ────────────────────────────────────────────────────────────────────

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 readme_to_flashcards.py README.md imp.md *.c doc/*.svg --out flashcards.js", file=sys.stderr)
        sys.exit(1)

    args = sys.argv[1:]
    output_file = None
    raw_inputs = []

    i = 0
    while i < len(args):
        if args[i] == "--out" and i + 1 < len(args):
            output_file = args[i + 1]
            i += 2
        else:
            raw_inputs.append(args[i])
            i += 1

    # Expand glob patterns (e.g. *.c, doc/*.svg)
    input_files = []
    for pattern in raw_inputs:
        matched = glob.glob(pattern)
        if matched:
            input_files.extend(sorted(matched))
        else:
            input_files.append(pattern)

    all_cards = []
    counts = {".md": 0, ".c": 0, ".svg": 0}

    for input_file in input_files:
        ext = os.path.splitext(input_file)[1].lower()

        try:
            with open(input_file, "r", encoding="utf-8", errors="replace") as f:
                content = f.read()
        except FileNotFoundError:
            print(f"⚠️  '{input_file}' not found, skipping.", file=sys.stderr)
            continue

        if ext == ".md":
            cards = parse_readme(content)
            counts[".md"] += 1
            print(f"✅ {input_file} (.md): {len(cards)} flashcards.", file=sys.stderr)
            for j, (q, _) in enumerate(cards, 1):
                print(f"    {j}. {q}", file=sys.stderr)

        elif ext == ".c":
            cards = parse_c_file(os.path.basename(input_file), content)
            counts[".c"] += 1
            print(f"✅ {input_file} (.c): {cards[0][0]}", file=sys.stderr)

        elif ext == ".svg":
            cards = parse_svg_file(os.path.basename(input_file), content)
            counts[".svg"] += 1
            print(f"✅ {input_file} (.svg): {cards[0][0]}", file=sys.stderr)

        else:
            print(f"⚠️  '{input_file}' skipped (unsupported: {ext})", file=sys.stderr)
            cards = []

        all_cards.extend(cards)

    if not all_cards:
        print("No flashcards found. Check your files.", file=sys.stderr)
        sys.exit(1)

    print(f"\n✅ Total: {len(all_cards)} flashcards", file=sys.stderr)
    print(f"   .md  files : {counts['.md']}", file=sys.stderr)
    print(f"   .c   files : {counts['.c']}", file=sys.stderr)
    print(f"   .svg files : {counts['.svg']}", file=sys.stderr)

    js_output = to_js(all_cards)

    if output_file:
        with open(output_file, "w", encoding="utf-8") as f:
            f.write(js_output)
        print(f"✅ Written to {output_file}", file=sys.stderr)
    else:
        print(js_output)


if __name__ == "__main__":
    main()
