#ifndef FILESYSTEMIO_READ_H
#define FILESYSTEMIO_READ_H

#include <string>

#include "file_system_directory_io.h"
#include "game_io_interface.h"

namespace tetris_view {

class FileSystemIO_Read : public virtual FileSystemDirectoryIO_I {
public:
  virtual ~FileSystemIO_Read() = default;

    // creates filesystem io object with default targets
    // target_directory - rsc
    // target_input_file - test-input.txt
    // target_output_file - test-output.txt
    explicit FileSystemIO_Read(const std::string& tar_dir = "",
                const std::string& in_file = ""
                );

    virtual std::string Read() override;

    std::string TargetInputFile();
    void TargetInputFile(const std::string& new_input_file);

protected:
    std::string target_input_file_;
};

}



#endif //FILESYSTEMIO_READ_H
