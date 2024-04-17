#include "working_with_file.h"

File Parsing(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("Please, submit correct number of arguments");
    }
    File user_args;
    user_args.program_name_ = argv[0];
    user_args.file_in_ = argv[1];
    user_args.file_out_ = argv[2];
    for (auto i = 3; i < argc;) {
        if (argv[i][0] == '-') {
            std::string current_filter = argv[i];
            if (user_args.correct_filters_names.find(current_filter) == user_args.correct_filters_names.end()) {
                throw std::invalid_argument("Invalid filter flag");
            }
            user_args.filters_.push_back(current_filter);
            ++i;
            while (i < argc && argv[i][0] != '-') {
                user_args.filter_attributes_[current_filter].push_back(argv[i]);
                ++i;
            }
        } else {
            throw std::invalid_argument("filter command should start with -");
        }
    }
    return user_args;
}