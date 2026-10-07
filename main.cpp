/*
 * Full Name:     [Your Name]
 * Student ID:    [Your NUID]
 * Course:        EECE 2140 - Computing Fundamentals for Engineers
 * Section:       [Your Section]
 * Semester:      Fall 2026
 * Assignment:    Homework 3 - Secret Message Decoder
 * Compilation:   g++ -std=c++11 main.cpp -o main
 * Description:   A menu-driven program that encodes, decodes, and cracks
 *                Caesar-cipher text files. It counts how often each
 *                letter appears in a file, prints a formatted frequency
 *                report, guesses the secret shift from those counts, and
 *                logs every file it writes.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>

// ---------------------------------------------------------------------
// Global named constants (provided in the template)
// ---------------------------------------------------------------------
const int ALPHABET_SIZE = 26;          // letters 'A' through 'Z'
const char MOST_COMMON_LETTER = 'E';   // most frequent letter in English text
const int TOP_LETTERS = 5;             // letters listed on the "Most frequent:" line
const std::string LOG_FILE_NAME = "decoder_log.txt";

// ---------------------------------------------------------------------
// Function declarations (provided in the template)
// ---------------------------------------------------------------------
char shiftLetter(char ch, int shift);
void openInputFile(std::ifstream& inStream, const std::string& fileName);
void openOutputFile(std::ofstream& outStream, const std::string& fileName, bool append);
void countLetters(std::istream& inStream, int counts[]);
int sumArray(const int a[], int size);
int indexOfLargest(const int a[], int size);
void rankLetters(const int counts[], char ranked[]);
int guessShift(const int counts[]);
void printFrequencyReport(std::ostream& outStream, const int counts[]);
int transformText(std::istream& inStream, std::ostream& outStream, int shift);

// ---------------------------------------------------------------------
// main() -- provided; do not modify anything above the line of "=" signs.
// ---------------------------------------------------------------------
int main()
{
    int counts[ALPHABET_SIZE];
    int choice = 0;

    std::cout << "=== EECE 2140 Secret Message Decoder ===" << std::endl;

    do
    {
        std::cout << std::endl
                  << "1) Letter frequency report" << std::endl
                  << "2) Encode a file" << std::endl
                  << "3) Decode a file with a known shift" << std::endl
                  << "4) Crack a file automatically" << std::endl
                  << "5) Exit" << std::endl
                  << "Enter your choice: ";

        if (!(std::cin >> choice))
        {
            choice = 5;   // end of input: leave the menu
        }

        if (choice == 1)
        {
            std::string inName;
            std::cout << "Enter the input file name: ";
            std::cin >> inName;

            std::ifstream inStream;
            openInputFile(inStream, inName);
            countLetters(inStream, counts);
            inStream.close();

            std::cout << std::endl;
            printFrequencyReport(std::cout, counts);
        }
        else if (choice >= 2 && choice <= 4)
        {
            std::string inName, outName;
            int shift = 0;

            std::cout << "Enter the input file name: ";
            std::cin >> inName;
            std::cout << "Enter the output file name: ";
            std::cin >> outName;

            if (choice != 4)
            {
                std::cout << "Enter the shift (1-25): ";
                std::cin >> shift;
            }

            if (inName == outName)
            {
                std::cout << "The output file must be different from the input file."
                          << std::endl;
            }
            else if (choice != 4 && (shift < 1 || shift > 25))
            {
                std::cout << "The shift must be between 1 and 25." << std::endl;
            }
            else
            {
                std::ifstream inStream;
                std::ofstream outStream;
                std::string action;

                if (choice == 4)
                {
                    // First pass: count the letters to guess the shift.
                    openInputFile(inStream, inName);
                    countLetters(inStream, counts);
                    inStream.close();
                    shift = guessShift(counts);
                    std::cout << "Guessed shift: " << shift << std::endl;
                }

                // Second pass (or only pass): reopen and transform the text.
                openInputFile(inStream, inName);
                openOutputFile(outStream, outName, false);

                int letters = 0;
                if (choice == 2)
                {
                    action = "encode";
                    letters = transformText(inStream, outStream, shift);
                }
                else
                {
                    if (choice == 3)
                    {
                        action = "decode";
                    }
                    else
                    {
                        action = "crack";
                    }
                    letters = transformText(inStream, outStream,
                                            (ALPHABET_SIZE - shift) % ALPHABET_SIZE);
                }
                inStream.close();
                outStream.close();

                if (choice == 2)
                {
                    std::cout << "Encoded ";
                }
                else
                {
                    std::cout << "Decoded ";
                }
                std::cout << letters << " letters into " << outName << "." << std::endl;

                std::ofstream logStream;
                openOutputFile(logStream, LOG_FILE_NAME, true);
                logStream << action << " " << inName << " -> " << outName
                          << " (shift " << shift << ")" << std::endl;
                logStream.close();
            }
        }
        else if (choice == 5)
        {
            std::cout << "Goodbye." << std::endl;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1-5." << std::endl;
        }
    } while (choice != 5);

    return 0;
}

// =====================================================================
// Complete each function below. Do not change any function's name,
// return type, or parameter list, and do not modify main() or the
// provided constants. Each placeholder "return" statement is there only
// so that the template compiles; replace it with your own code.
// =====================================================================

// TODO 1: shiftLetter
//   Parameters: ch    -- any character.
//               shift -- the number of positions to shift (0 to 25).
//   Returns:    If ch is an uppercase letter, the uppercase letter that is
//               shift positions later in the alphabet, wrapping around
//               from 'Z' back to 'A'. If ch is a lowercase letter, the
//               lowercase letter shift positions later, wrapping around
//               from 'z' back to 'a'. Any other character is returned
//               unchanged.
char shiftLetter(char ch, int shift)
{
    return '\0';
}

// TODO 2: openInputFile
//   Parameters: inStream -- the input-file stream to connect.
//               fileName -- the name of the file to open for reading.
//   Behavior:   Connects inStream to the file fileName. If the file
//               cannot be opened, prints exactly
//                   Input file opening failed: <fileName>
//               as one line on the screen and then ends the whole program
//               with exit status 1.
void openInputFile(std::ifstream& inStream, const std::string& fileName)
{
}

// TODO 3: openOutputFile
//   Parameters: outStream -- the output-file stream to connect.
//               fileName  -- the name of the file to open for writing.
//               append    -- true:  new output is added after the file's
//                                   existing contents (the file is created
//                                   if it does not exist);
//                            false: the file's existing contents are
//                                   discarded.
//   Behavior:   Connects outStream to the file fileName in the requested
//               mode. If the file cannot be opened, prints exactly
//                   Output file opening failed: <fileName>
//               as one line on the screen and then ends the whole program
//               with exit status 1.
void openOutputFile(std::ofstream& outStream, const std::string& fileName, bool append)
{
}

// TODO 4: countLetters
//   Parameters: inStream -- an input stream (cin, an ifstream, or any
//                           other istream) that is ready to be read.
//               counts   -- an array of ALPHABET_SIZE elements.
//   Behavior:   Reads all remaining input from inStream, to the end of
//               the input. Afterward, counts[0] holds the number of times
//               the letter A appeared, counts[1] the number of times B
//               appeared, and so on through counts[25] for Z. Uppercase
//               and lowercase forms of a letter count as the same letter,
//               and every character that is not a letter is ignored. All
//               ALPHABET_SIZE elements are set, whatever counts held
//               before the call. Does not close the stream.
void countLetters(std::istream& inStream, int counts[])
{
}

// TODO 5: sumArray
//   Parameters: a    -- an array of integers (not modified).
//               size -- the number of elements of a to use (size >= 0).
//   Returns:    The sum a[0] + a[1] + ... + a[size - 1], or 0 when size
//               is 0.
int sumArray(const int a[], int size)
{
    return -1;
}

// TODO 6: indexOfLargest
//   Parameters: a    -- an array of integers (not modified).
//               size -- the number of elements of a to use (size >= 1).
//   Returns:    The index of the largest value among a[0] through
//               a[size - 1]. If that value occurs more than once, the
//               smallest such index is returned.
int indexOfLargest(const int a[], int size)
{
    return -1;
}

// TODO 7: rankLetters
//   Parameters: counts -- an array of ALPHABET_SIZE letter counts, in the
//                         format produced by countLetters (not modified).
//               ranked -- an array of ALPHABET_SIZE characters to fill.
//   Behavior:   Fills ranked with the 26 uppercase letters 'A' through 'Z'
//               ordered from the most frequent letter to the least
//               frequent, according to counts. Letters with equal counts
//               appear in alphabetical order.
void rankLetters(const int counts[], char ranked[])
{
}

// TODO 8: guessShift
//   Parameters: counts -- an array of ALPHABET_SIZE letter counts, in the
//                         format produced by countLetters (not modified).
//   Returns:    The shift (0 to 25) that would turn MOST_COMMON_LETTER
//               into the letter with the largest count (the alphabetically
//               first such letter if there is a tie), or 0 when every
//               count is 0. Must call sumArray and indexOfLargest.
int guessShift(const int counts[])
{
    return -1;
}

// TODO 9: printFrequencyReport
//   Parameters: outStream -- an output stream (cout, an ofstream, or any
//                            other ostream) to write the report to.
//               counts    -- an array of ALPHABET_SIZE letter counts, in
//                            the format produced by countLetters (not
//                            modified).
//   Behavior:   Writes the letter-frequency report to outStream in the
//               exact format given in the assignment handout: the header
//               line; one row for each letter whose count is greater than
//               0, in alphabetical order, showing the letter, its count,
//               and its percentage of all letters; then the
//               "Total letters:" line and the "Most frequent:" line. When
//               every count is 0, writes only the line
//                   No letters found.
//               Must call sumArray and rankLetters.
void printFrequencyReport(std::ostream& outStream, const int counts[])
{
}

// TODO 10: transformText
//   Parameters: inStream  -- an input stream that is ready to be read.
//               outStream -- an output stream to write to.
//               shift     -- the shift to apply to every letter (0 to 25).
//   Behavior:   Reads all remaining input from inStream, to the end of
//               the input, and writes it to outStream with every letter
//               replaced by the result of shiftLetter for that letter and
//               shift. Every other character -- including spaces, tabs,
//               and line breaks -- is written exactly as it was read, so
//               the output has the same layout as the input. Must call
//               shiftLetter. Does not close either stream.
//   Returns:    The number of letters that were read (and shifted).
int transformText(std::istream& inStream, std::ostream& outStream, int shift)
{
    return -1;
}
