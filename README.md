> **Tip:** This file is written in Markdown. The raw view in the VS Code
> editor will show symbols such as `#`, `|`, and `` ``` `` instead of
> formatted headings, tables, and code blocks. For the formatted view,
> press **Ctrl+Shift+V** (macOS: **Cmd+Shift+V**) to open the rendered
> preview.

# Homework 3 — Secret Message Decoder

## Overview

A *Caesar cipher* hides a message by replacing every letter with the
letter a fixed number of positions later in the alphabet (the *shift*),
wrapping around from Z back to A. With a shift of 3, `Attack at dawn!`
becomes `Dwwdfn dw gdzq!`. Spaces, punctuation, and line breaks are not
changed.

This program works on text files. From a menu, the user can:

1. print a letter-frequency report for a file,
2. encode a file with a chosen shift,
3. decode a file when the shift is known, and
4. crack a file automatically, by assuming that the most frequent letter
   in the secret file stands for `E`, the most common letter in English.

Every file the program writes is recorded at the end of the log file
`decoder_log.txt`.

`main()` and the global constants are provided and complete. Your job is
to write the ten functions marked `TODO` in `main.cpp`. See the full
assignment handout on Canvas for the complete problem statement, the
exact report format, an example interaction, and the grading rubric.

## Constraints

- Do **not** modify `main()`, the provided constants, the `#include`
  lines, or any function's name, return type, or parameter list. The
  autograder calls your functions directly.
- Use only the headers already included in the template (`<iostream>`,
  `<fstream>`, `<iomanip>`, `<string>`, `<cstdlib>`, `<cctype>`).
- Use `std::string` only for file names, as `main()` does. Arrays of
  strings, `std::vector`, library sorting or searching functions, and
  global variables (other than the provided constants) are not allowed.
- Use the provided named constants instead of writing their values
  (26, `'E'`, 5) directly in your code.
- `guessShift`, `printFrequencyReport`, and `transformText` must call the
  functions listed for them in the table below.
- You may assume input files contain only ASCII characters (no accented
  letters or "smart" quotation marks).
- Your program must compile with no errors using
  `g++ -std=c++11 main.cpp -o main`.

## Function Interface

| Function | Parameters | Returns | Behavior |
|---|---|---|---|
| `shiftLetter` | `char ch`, `int shift` (0–25) | `char` | Returns `ch` shifted `shift` positions, wrapping around and keeping its case; any non-letter is returned unchanged. |
| `openInputFile` | `std::ifstream& inStream`, `const std::string& fileName` | `void` | Opens `fileName` for reading, or prints `Input file opening failed: <fileName>` and ends the program with exit status 1. |
| `openOutputFile` | `std::ofstream& outStream`, `const std::string& fileName`, `bool append` | `void` | Opens `fileName` for writing (adding to the end when `append` is `true`, replacing the contents otherwise), or prints `Output file opening failed: <fileName>` and ends the program with exit status 1. |
| `countLetters` | `std::istream& inStream`, `int counts[]` | `void` | Reads to the end of the input and stores in `counts[0]`–`counts[25]` how many times each letter A–Z appeared, ignoring case. |
| `sumArray` | `const int a[]`, `int size` | `int` | Returns the sum of the first `size` elements of `a`. |
| `indexOfLargest` | `const int a[]`, `int size` | `int` | Returns the smallest index of the largest value among the first `size` elements of `a`. |
| `rankLetters` | `const int counts[]`, `char ranked[]` | `void` | Fills `ranked` with the letters A–Z from most to least frequent, with equal counts in alphabetical order. |
| `guessShift` | `const int counts[]` | `int` | Returns the shift (0–25) that turns `'E'` into the most frequent letter, or 0 if there are no letters; calls `sumArray` and `indexOfLargest`. |
| `printFrequencyReport` | `std::ostream& outStream`, `const int counts[]` | `void` | Writes the letter-frequency report in the handout's exact format to `outStream`; calls `sumArray` and `rankLetters`. |
| `transformText` | `std::istream& inStream`, `std::ostream& outStream`, `int shift` (0–25) | `int` | Copies all remaining input to `outStream` with every letter shifted and every other character unchanged, and returns the number of letters; calls `shiftLetter`. |

## Compiling and Running

```
g++ -std=c++11 main.cpp -o main
./main            # macOS / Linux
.\main.exe        # Windows
```

The program looks for input files, and creates output files and
`decoder_log.txt`, in the folder where you run it. Run it from a terminal
opened in the same folder as your test files. Create your own test files
with VS Code (File → New Text File, then save with a `.txt` name).

## Submission Checklist

- [ ] Filled in the file header at the top of `main.cpp` (name, student ID, section).
- [ ] Program compiles with no errors using `g++ -std=c++11 main.cpp -o main`.
- [ ] Tested every menu option with files of my own, including an empty file, a file with several lines, a file whose last line has no line break, and a file name that does not exist.
- [ ] Checked that an encoded file decodes back to exactly the original text, spaces and line breaks included.
- [ ] Code is commented and consistently formatted.
- [ ] Committed and pushed all changes to GitHub (not just once, right before the deadline).
- [ ] Submitted through Gradescope by selecting this repository and the correct branch.
- [ ] Submitted the Part A Concept Check answers as a PDF on Canvas.

## Academic Integrity

Write this code independently. Do not copy code from another student,
share your submission files with classmates, or use an AI tool to
generate, complete, modify, or correct any part of this program. See
the course syllabus, Section B, for the full policy. Keep this
repository private for the entire semester.
