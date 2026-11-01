// cl: /DNDEBUG /MD /EHsc
// ?write@RAMFile@@UAEHPBXH@Z retail 0x00574473 6 bytes.
// Slot 4 (offset 0x10) of vtables 0x0087AA00 and 0x0087AA50; ZH donor
// GameEngine/Source/Common/System/RAMFile.cpp RAMFile::write returns -1.
// Evidence: direct callers push 2 args then call at 0x0042C108 and 0x005E592B
// plus jmp at 0x005753AF; cmp eax -1 in 0x005E5920 proves -1 sentinel.
class AsciiString;

#include "../../../Include/Common/File.h"

class RAMFile : public File
{
public:
	virtual int write(const void *buffer, int bytes);
};

int RAMFile::write(const void *buffer, int bytes)
{
	return -1;
}
