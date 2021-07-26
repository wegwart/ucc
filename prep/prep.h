#pragma once

#include <string>
#include <vector>

namespace prep {

    void preprocess(
        const std::vector<const std::string>& input_files,
        const std::map<std::string, std::string>& predefines,
        const std::string& output_file
    );

}
