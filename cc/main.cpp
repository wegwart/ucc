#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>

#include <parser.h>
#include <codegen/generator.h>

static void print_version()
{
    printf("ucc version ...\n");
}

static void print_help()
{
    printf("help goes here\n");
}

static void compile(FILE* f)
{
    parse(f);

    codegen::CodeGenerator generator{ "myprogram" };
    ast::Ast::get().visit(&generator);
}

int main(int argc, char* argv[])
{
    static struct option long_options[] = {
        { "version",    no_argument, 0, 'v' },
        { "help",       no_argument, 0, 'h' }
    };

    int c, opt_index;
    while ((c = getopt_long(argc, argv, "vh", long_options, &opt_index)) != -1)
    {
        switch (c)
        {
        case 'v':
            print_version();
            return EXIT_SUCCESS;
        default:
            // getopt_long() will print an error here
            // [ fallthrough intended ]
        case 'h':
            print_help();
            return EXIT_SUCCESS;
        }
    }

    std::vector<std::string> input_files;
    opt_index = optind;
    while (opt_index < argc)
        input_files.push_back(argv[opt_index++]);
    
    if (input_files.size() == 0)
    {
        fprintf(stderr, "fatal: no input files\n");
        return EXIT_FAILURE;
    }

    for (auto& file : input_files)
    {
        FILE* f_ptr = fopen(file.c_str(), "r");
        if (f_ptr == NULL)
        {
            fprintf(stderr, "error: %s: cannot open file\n", file.c_str());
            return EXIT_FAILURE;
        }

        compile(f_ptr);
    }
}
