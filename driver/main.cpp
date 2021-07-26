#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <prep/prep.h>

int main(int argc, char* argv[])
{
    int option;
    while ((option = getopt(argc, argv, "o:")) != -1)
    {
        switch (option)
        {
        case 'o':
            // Output file is 'optarg'
            break;
        default:
            // Error
            break;
        }
    }

    // read input files from command line
    std::vector<std::string> input_files;
    while (optind < argc)
        input_files.push_back(argv[optind++]);

    if (input_files.size() == 0)
    {
        fprintf(stderr, "fatal: no input files\n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
