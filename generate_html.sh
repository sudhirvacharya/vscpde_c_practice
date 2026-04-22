#!/usr/bin/env bash

set -e

# ---------- Step 0: Collect files ----------
shopt -s nullglob
files=( *.md *.c *.h )
shopt -u nullglob

echo "FILES FOUND: ${files[*]}"

# ---------- Step 1: Create combined text ----------
> all_code.txt

for f in "${files[@]}"; do
    [ -e "$f" ] || continue

    echo "" >> all_code.txt
    echo "===== $f =====" >> all_code.txt
    echo "" >> all_code.txt

    cat "$f" >> all_code.txt
done

# ---------- Step 2: Add page break before each .c file ----------
awk '/^===== .*\.c =====$/ { print "\f" } { print }' all_code.txt > final.txt

# ---------- Step 3: Create HTML ----------
cat << 'EOF' > final.html
<html>
<head>
<meta charset="utf-8">
<style>
body {
    font-family: monospace;
    white-space: pre;
    margin: 20mm;
}
h1 {
    font-family: sans-serif;
}
pre {
    page-break-inside: avoid;
}
</style>
</head>
<body>
<h1>Project Documentation</h1>
<pre>
EOF

# ---------- Step 4: Append content ----------
cat final.txt >> final.html

# ---------- Step 5: Close HTML ----------
echo "</pre></body></html>" >> final.html

echo "✅ Done: final.html"