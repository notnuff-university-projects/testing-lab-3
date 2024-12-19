#ifndef FILE_READ_STD_WRITE_IO_H
#define FILE_READ_STD_WRITE_IO_H

#include "file_system_io_read.h"
#include "file_system_io_write.h"
#include "std_io_write.h"

namespace tetris_view {

class FileReadStdWriteIO : public virtual FileSystemIO_Read, public virtual StdIoWrite {
public:
  explicit FileReadStdWriteIO( const std::string& tar_dir = "",
                const std::string& in_file = ""
                );
};

}


#endif //FILE_READ_STD_WRITE_IO_H
