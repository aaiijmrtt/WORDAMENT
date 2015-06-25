#WORDAMENT

Wordament: solving the game

The code in this repository presents a solution to the game of Wordament, using
a simply backtracking algorithm to find each word. For those unfamiliar with the
rules, the game is played on a 4 \* 4 grid, each tile containing a letter. Words
must be formed from sequences of (vertically, horizontally or diagonally)
contiguous cells. Each tile may be used at most once in a word. The objective is
to form as many words as possible.

**Instructions**:

1. **Compiling**: $gcc -o wrdmnt wrdmnt.c
2. **Using**: $./wrdmnt [grid]

**Arguments**:

* **grid**: [char[16]] the (capitalized) letters in the input grid: top to
bottom, left to right.

**Note**:

* Requires gcc.

**Credits**:

* [word list](http://www.mieliestronk.com/wordlist.html)
