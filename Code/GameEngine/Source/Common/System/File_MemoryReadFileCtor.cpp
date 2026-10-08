// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??0MemoryReadFile@@QAE@PADH@Z @0x00602255 89B: MemoryReadFile ctor over caller-owned block
// Evidence: pinned name; donor open-bfme-1/game/GameEngine/Source/Common/System/File.cpp:536; base File ctor 0x006024FD (File 0x14-byte layout) and "<no file>" default; StringBase::set 0x000055F5 with "<MemoryReadFile>"; vtable 0x00C7A748; caller 0x00602301 createMemoryReadFile.
#include "ascii_string.h"

class File
{
public:
	File();
	virtual ~File();

protected:
	AsciiString m_sourceFile; // +0x04
	int m_08; // +0x08 File m_access
	unsigned char m_0C; // +0x0C File m_open
	unsigned char m_0D; // +0x0D
	unsigned char m_pad0E[2];
	int m_10; // +0x10 File m_mutex
};

class MemoryReadFile : public File
{
public:
	MemoryReadFile(char *data, int size);

private:
	char *m_data; // +0x14
	int m_size; // +0x18
	int m_pos; // +0x1C
};

MemoryReadFile::MemoryReadFile(char *data, int size)
{
	m_data = data;
	m_size = size;
	m_pos = 0;
	m_0C = 1;
	m_08 = 0x41;
	((StringBase<char> *)&m_sourceFile)->set("<MemoryReadFile>");
}
