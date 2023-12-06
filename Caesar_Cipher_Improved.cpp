
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Function prototypes
std::string encrypt(const std::string &text, int key);
void caesarCipher(int key, const std::string &inputFile, const std::string &outputFile);

/**
 * Encrypts the given text using Caesar Cipher.
 *
 * @param text The string to encrypt.
 * @param key The encryption key (shift).
 * @return The encrypted string.
 */
std::string encrypt(const std::string &text, int key)
{
    std::string result;
    for (char c : text)
    {
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + key) % 26 + base; // Wrap around the alphabet
        }
        result += c;
    }
    return result;
}

/**
 * Performs Caesar Cipher encryption on the contents of inputFile and writes the result to outputFile.
 *
 * @param key The encryption key (shift).
 * @param inputFile The name of the input file.
 * @param outputFile The name of the output file.
 */
void caesarCipher(int key, const std::string &inputFile, const std::string &outputFile)
{
    // Validate key range
    if (key < 0 || key > 25)
    {
        throw std::invalid_argument("Key must be between 0 and 25");
    }

    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    // Check if files are open
    if (!inFile.is_open() || !outFile.is_open())
    {
        throw std::runtime_error("Error opening files");
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        outFile << encrypt(line, key) << std::endl;
    }
}

int main()
{
    int key = 3; // Example key
    std::string inputFile = "samson.txt";
    std::string outputFile = "output.txt";

    try
    {
        caesarCipher(key, inputFile, outputFile);
        std::cout << "Encryption completed successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
