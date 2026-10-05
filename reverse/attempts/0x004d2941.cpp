// ??A?$map@GVAsciiString@@U?$less@G@_STL@@V?$allocator@U?$pair@$$CBGVAsciiString@@@_STL@@@3@@_STL@@QAEAAVAsciiString@@ABG@Z
// partial score=0.98 date=2026-10-05
// ??A?$map@GVAsciiString@@U?$less@G@_STL@@V?$allocator@U?$pair@$$CBGVAsciiString@@@_STL@@@3@@_STL@@QAEAAVAsciiString@@ABG@Z
// partial score=1.0 date=2026-10-05
// ?operator[] map<unsigned short,AsciiString>
// partial score=1.0 date=2026-10-05
// cl: /O1
// stlport
// BFME2 target: 0x004D2941 is a Ghidra 134B function. Its lookup/insert path
// compares a 16-bit key and returns the value at node+0x14. The matched
// ConnectionManager::getFileTransferProgress at 0x004D28C6 independently
// establishes FileCommandMap as map<unsigned short, AsciiString>.
// Donor: Open-BFME-1 FileCommandMapIndex.cpp at revision 6583b3c1.
// ???A?$map@GVAsciiString@@U?$less@G@_STL@@V?$allocator@U?$pair@$$CBGVAsciiString@@@_STL@@@3@@_STL@@QAEAAVAsciiString@@ABG@Z present-unmatched
#include <stl/_config.h>

#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

template <typename T>
class StringBase
{
 friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

private:
	void *m_data;
};

#include <map>

typedef std::map<unsigned short, AsciiString> FileCommandMap;
template AsciiString &FileCommandMap::operator[](const unsigned short &key);
