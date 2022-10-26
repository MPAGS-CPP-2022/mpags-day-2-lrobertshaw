#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string transformChar(const char in_char);

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const vector<string> cmdLineArgs{argv, argv + argc};
    const size_t nCmdLineArgs{cmdLineArgs.size()};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    string inputFile{""};
    string outputFile{""};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            helpRequested = true;
        } else if (cmdLineArgs[i] == "--version") {
            versionRequested = true;
        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                cerr << "[error] -i requires a filename argument" << endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                inputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                cerr << "[error] -o requires a filename argument" << endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                outputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            cerr << "[error] unknown argument '" << cmdLineArgs[i] << "'\n";
            return 1;
        }
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        cout << "0.1.0" << endl;
        return 0;
    }

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }


    // Initialise variables
    char inputChar{'x'};
    string inputText{""};
    // loop over each character from user input
    while (cin >> inputChar) {
        string res = transformChar(inputChar);
        inputText += res;
    }

    // Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    cout << inputText << endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}


string transformChar(const char in_char){

    string output{""};
    // Uppercase alphabetic characters
    if (isalpha(in_char)) {
        output += toupper(in_char);
        return output;
    }

    // Transliterate digits to English words
    switch (in_char) {
        case '0':
            return "ZERO";
        case '1':
            return "ONE";
        case '2':
            return "TWO";
        case '3':
            return "THREE";
            break;
        case '4':
            return "FOUR";
            break;
        case '5':
            return "FIVE";
            break;
        case '6':
            return "SIX";
            break;
        case '7':
            return "SEVEN";
            break;
        case '8':
            return "EIGHT";
            break;
        case '9':
            return "NINE";
            break;
    }

// If the character isn't alphabetic or numeric, DONT add it
}