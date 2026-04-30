#!/usr/bin/env python3
"""
cmd-->this is used for script.google input
python3 generate_flashcards.py README.md imp.md *.c doc/*.svg --out flashcards.js
generate_flashcards.py

Parses .md, .c and .svg files and generates a JS flashcards array.

  .md files  -> ## / ### headings become Q, content below becomes A
  .c files   -> Q: "Write <filename> code?",     A: full source code
  .svg files -> Q: "Explain <filename> diagram?", A: extracted labels + raw SVG

Usage:
    python3 generate_flashcards.py README.md imp.md *.c doc/*.svg --out flashcards.js
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


def extract_svg_text_labels(content):
    """
    Extract all visible text from <text> and <tspan> elements inside SVG.
    Handles nested tspans, XML entities, and deduplicates results.
    Useful for ADC/SPI/DMA block diagrams with signal/pin/block name labels.
    """
    # Grab everything between <text ...>...</text> (including nested tspans)
    text_blocks = re.findall(r'<text[^>]*>(.*?)</text>', content, re.DOTALL | re.IGNORECASE)

    labels = []
    seen = set()

    for block in text_blocks:
        # Strip any nested tags like <tspan>, keeping only text content
        raw = re.sub(r'<[^>]+>', ' ', block)
        # Decode common XML entities
        raw = (raw.replace('&amp;', '&')
                  .replace('&lt;', '<')
                  .replace('&gt;', '>')
                  .replace('&quot;', '"')
                  .replace('&#xa;', ' ')
                  .replace('&#xA;', ' '))
        # Collapse whitespace
        clean = re.sub(r'\s+', ' ', raw).strip()

        if clean and len(clean) > 1 and clean not in seen:
            seen.add(clean)
            labels.append(clean)

    return labels


def parse_svg_file(filename, content):
    """
    Parse an SVG diagram file (ADC, SPI, DMA, etc.).

    Question : "Explain <Readable Name> diagram?"
    Answer   : metadata + extracted signal/pin labels + raw SVG source
    """
    name = os.path.splitext(filename)[0]
    readable_name = name.replace("_", " ").replace("-", " ").title()
    question = f"Explain {readable_name} diagram?"

    # ── Metadata from SVG tags ──
    title_match = re.search(r'<title[^>]*>(.*?)</title>', content, re.IGNORECASE | re.DOTALL)
    desc_match  = re.search(r'<desc[^>]*>(.*?)</desc>',  content, re.IGNORECASE | re.DOTALL)

    meta_lines = []
    if title_match:
        t = title_match.group(1).strip()
        if t:
            meta_lines.append(f"Title: {t}")
    if desc_match:
        d = desc_match.group(1).strip()
        if d:
            meta_lines.append(f"Description: {d}")
    if not meta_lines:
        meta_lines.append(f"Diagram: {readable_name}")

    # ── Text labels extracted from diagram blocks ──
    labels = extract_svg_text_labels(content)

    label_section = ""
    if labels:
        label_section = "\nKey Labels / Signals:\n" + "\n".join(f"  - {lbl}" for lbl in labels)

    # ── Compose answer ──
    answer_parts = ["\n".join(meta_lines)]
    if label_section:
        answer_parts.append(label_section)
    answer_parts.append("\nSVG Source:\n" + content.strip())

    answer = "\n".join(answer_parts)
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
        print("Usage: python3 generate_flashcards.py README.md imp.md *.c doc/*.svg --out flashcards.js", file=sys.stderr)
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
            labels = extract_svg_text_labels(content)
            print(f"✅ {input_file} (.svg): '{cards[0][0]}'", file=sys.stderr)
            if labels:
                preview = ', '.join(labels[:5])
                more = f" (+{len(labels)-5} more)" if len(labels) > 5 else ""
                print(f"   └─ {len(labels)} labels: {preview}{more}", file=sys.stderr)
            else:
                print(f"   └─ No <text> labels found; using title/desc only", file=sys.stderr)

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