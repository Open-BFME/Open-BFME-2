#pragma once
// Shared legacy nested-record binding, not a recovered archive-class layout.
// Target2174DF/217624: three32-bit words then an AsciiString at+C; stride16.
// Font parser218E96 uses these words as size/style data. Donor WWLib's
// StringClass archive record is NOT imported. No outer-instance ABI is asserted.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class MixFileCreator
{
public:
 struct FileInfoStruct
 {
  FileInfoStruct() {}
  FileInfoStruct(const FileInfoStruct &);
  FileInfoStruct &operator=(const FileInfoStruct &);
  unsigned long CRC;
  unsigned long Offset;
  unsigned long Size;
  AsciiString Filename;
 };
};
typedef char MixFileCreator_FileInfo_record_size16[(sizeof(MixFileCreator::FileInfoStruct)==16)?1:-1];
