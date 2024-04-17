#include "controller.h"
#include "working_with_file.h"

int main(int argc, char* argv[]) {
    File user_args = Parsing(argc, argv);
    Image image = ReadFile(user_args.file_in_);
    image = Controller(image, user_args);
    SaveFile(user_args.file_out_, image);
    return 0;
}
