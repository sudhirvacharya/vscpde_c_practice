# my wekanes i forgot every time  
1.(*fnptr)
2.move zero to end
3.delte node in linked list
2.get char


### intrduction about myself
"Hi, I am Sudhir Acharya. 
I have over 11 years of experience in Embedded C, with a strong focus on the Automotive domain — specifically in the MCAL layer.
My core work has been in MCAL driver development, testing, and integration. 
I have hands-on experience with microcontrollers from Infineon, NXP, and STMicroelectronics.
On the tools side, I have worked with LAUTERBACH TRACE32 for software debugging, Logic Analyzers for signal-level analysis, and CANoe for automotive communication testing.
From a quality and compliance perspective, I have experience with ASPICE process requirements and MISRA C coding guidelines,


### use this cmd yo copy all to single file toprint 
# Clear file first (optional)
> all_code.txt

echo "===== FILE LIST =====" >> all_code.txt

files=( *.md *.c )

# Check if files actually exist
if [ -e "${files[0]}" ]; then
    printf "%s\n" "${files[@]}" >> all_code.txt
else
    echo "No .md or .c files found" >> all_code.txt
fi

echo "" >> all_code.txt

# Append contents
for f in "${files[@]}"; do
    [ -e "$f" ] || continue
    echo "" >> all_code.txt
    echo "===== $f =====" >> all_code.txt
    echo "" >> all_code.txt
    cat "$f" >> all_code.txt
done


--->html format, looks good
# Step 1: Add page break before each C file
awk '/^===== .*\.c =====$/ { print "\f" } { print }' all_code.txt > final.txt

# Step 2: Convert to HTML (print-friendly)
cat << 'EOF' > final.html
<html>
<head>
<style>
body {
    font-family: monospace;
    white-space: pre;
    margin: 20mm;
}
pre {
    page-break-inside: avoid;
}
</style>
</head>
<body>
<pre>
EOF

# Step 3: Append your content
cat final.txt >> final.html

# Step 4: Close HTML
echo "</pre></body></html>" >> final.html

---


##### AI prompt
The source is HTML content containing:
### intrduction about myself

theory


Source code files




Use ONLY the provided content.


Do NOT generate any new theory, explanations, or code.


Do NOT add extra examples.


Only format and organize the existing content.



FORMAT REQUIREMENTS:


Page size: A4


Color: Strictly black and white (printer-friendly)


Fonts:


Serif or sans-serif for normal text


Monospace for code




Margins: 2.5 cm on all sides


Page numbers: Bottom center


Optional: Chapter title in header



COVER PAGE:


Title: C Programming Notes & Practice


Subtitle: Beginner to Intermediate Guide


Author: Sudhir Acharya


Center-aligned layout


Minimal, clean design


Must appear on a separate page



STRUCTURE:


Generate a Table of Contents based only on the provided content


Do NOT create or invent new chapters


Use file names or sections from README.md as chapter titles



THEORY SECTIONS (FROM README.md ONLY):


Preserve the original text exactly (no rewriting)


Maintain headings and formatting


Keep bullet points and spacing intact


Ensure tables remain aligned and readable


Do NOT split tables across pages



CODE SECTIONS:


Each program must start on a new page


Do NOT split any program across pages


Preserve code exactly (no modifications)


Use a monospace font


Add a heading:
Program: <filename>


Place code inside a thin bordered box



PAGE LAYOUT RULES:


Avoid awkward page breaks


Keep headings with their content


Maintain consistent spacing throughout


Ensure clean readability for printing



OUTPUT:


A clean, print-ready PDF


Structured like a professional textbook or notebook


Must strictly use only the provided content (no additions)

---


### Lesson Learnt
 1. bracket missed
 2.simple logice not able to answer
 3. if condition coudl have used

 ### list of Questions
 Interview Preparation Checklist
🔢 Array Problems
Basic

 Maximum subarray sum (Kadane's Algorithm)
 Move zeros to end
 Remove duplicates from sorted array
 Sort 0s and 1s (Dutch flag - 2 elements)
 Sort 0s, 1s and 2s (Dutch flag - 3 elements)
 Reverse an array
 Find max and min in array
 Second largest element

Intermediate

 Two sum (find pair with given sum)
 Subarray with given sum
 Rotate array by K positions
 Merge two sorted arrays
 Find missing number (1 to N)
 Majority element (appears > N/2 times)
 Best time to buy & sell stock
 Trapping rain water


🔤 String Problems
Basic

 Reverse a string
 Check palindrome
 Count vowels/consonants
 Remove duplicates from string
 Check anagram

Intermediate

 Longest substring without repeating characters
 String compression (aaabbb → a3b3)
 Valid parentheses
 First non-repeating character
 Reverse words in a sentence


🔗 Linked List

 Reverse a linked list
 Detect cycle (Floyd's algorithm)
 Find middle of linked list
 Merge two sorted linked lists
 Remove Nth node from end
 Intersection of two linked lists


📚 Stack & Queue

 Implement stack using array/queue
 Valid parentheses using stack
 Next greater element
 Min stack (getMin in O(1))
 Implement queue using two stacks


🌳 Trees

 Inorder / Preorder / Postorder traversal
 Height of binary tree
 Level order traversal (BFS)
 Check if binary tree is BST
 Lowest common ancestor
 Diameter of binary tree


🔍 Searching & Sorting

 Binary search
 Binary search on rotated array
 Bubble / Selection / Insertion sort
 Merge sort
 Quick sort
 Find first and last position of element


💡 Dynamic Programming (Basics)

 Fibonacci (memoization vs tabulation)
 0/1 Knapsack
 Longest Common Subsequence
 Longest Increasing Subsequence
 Coin change problem
 Climbing stairs


⚙️ Bit Manipulation (Important for Semiconductor!)

 Next power of 2 ✅
 Check if number is power of 2
 Count set bits (Hamming weight)
 Find only odd-occurring number (XOR trick)
 Swap two numbers without temp variable
 Find the two non-repeating numbers
 Set / Clear / Toggle a specific bit
 Reverse bits of a number


🧮 Math & Number Theory

 Check prime number
 GCD / LCM (Euclidean algorithm)
 Reverse a number
 Check Armstrong number
 Sieve of Eratosthenes (all primes up to N)
 Integer overflow detection


🏭 Semiconductor / Embedded Specific

 Implement a circular buffer / ring buffer
 Endianness check (big vs little endian)
 Memory alignment concepts
 Bitfield manipulation in structs
 Fixed-point arithmetic
 CRC checksum basic concept
 Interrupt-safe data structures (volatile, atomic)

