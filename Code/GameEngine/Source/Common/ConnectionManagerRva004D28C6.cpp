// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /Og /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?getFileTransferProgress@ConnectionManager@@QAEHHVAsciiString@@@Z @ 0x004D28C6 123B
// ConnectionManager::getFileTransferProgress: iterate FileCommandMap at +0x12138 (map<ushort AsciiString>)
// for value matching path; return FileProgressMap[pid][key] at +0x12150 (map<ushort int>[8]) or 0.
// Evidence: donor ConnectionManager.cpp getFileTransferProgress same logic; callees rowed StringBase compare 0x69D6 increment 0x24250 releaseBuffer 0x36410 map operator[] 0x4DD277; caller 0x25E3E2 in 0x25E3BB.
#include <map>
#include "ascii_string.h"

struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};
typedef _STL::map<unsigned short, AsciiString> FileCommandMap;
typedef _STL::map<unsigned short, unsigned char> FileMaskMap;
typedef _STL::map<unsigned short, int, Gen_lt_00940b40> FileProgressMap;

class ConnectionManager
{
public:
	int getFileTransferProgress(int pid, AsciiString path);
private:
	char m_pad[0x12138];
	FileCommandMap m_fileCommandMap;
	FileMaskMap m_fileMaskMap;
	FileProgressMap m_fileProgress[8];
};

int ConnectionManager::getFileTransferProgress(int pid, AsciiString path)
{
	for (FileCommandMap::iterator it = m_fileCommandMap.begin(); it != m_fileCommandMap.end(); ++it)
	{
		StringBase<char> &lhs = *(StringBase<char> *)&it->second;
		StringBase<char> &rhs = *(StringBase<char> *)&path;
		if (lhs.compare(rhs) == 0)
			return m_fileProgress[pid][it->first];
	}
	return 0;
}
