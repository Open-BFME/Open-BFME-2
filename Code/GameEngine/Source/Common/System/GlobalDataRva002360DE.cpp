// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ?rva002360DE@GlobalData@@QBE?AVAsciiString@@XZ,
// retail 0x002360DE, 30 bytes, plus the Unicode twin
// ?rva002360FC@GlobalData@@QBE?AVUnicodeString@@XZ at 0x002360FC.
// Dedicated TU.
//
// Value-returning string getters on GlobalData: each returns the string
// member at its offset (+0x1240 narrow, +0x1244 wide). The stack arg is the
// hidden return pointer; the member copy-constructs directly into it (RVO)
// through the StringBase copy bodies at 0x365F0 (narrow) / 0x37050 (wide),
// and the function returns the hidden pointer. Callers pass a stack temp
// and read the string out of it (FileSystem Art setup at 0x00786BD for the
// narrow twin; DataChunk/Scripts callers for the wide twin). The class name
// is load-bearing (calls resolve via ledger rows); member names positional.

typedef int Int;
typedef unsigned short WideChar;

#define NULL 0

#include "ascii_string.h"


#include "unicode_string.h"

class GlobalData
{
public:
	AsciiString rva002360DE() const;
	UnicodeString rva002360FC() const;

private:
	char m_pad[0x1240];
	AsciiString m_string1240; // +0x1240
	UnicodeString m_wide1244; // +0x1244
};

// ?rva002360DE@GlobalData@@QBE?AVAsciiString@@XZ
AsciiString GlobalData::rva002360DE() const
{
	return m_string1240;
}

// ?rva002360FC@GlobalData@@QBE?AVUnicodeString@@XZ
UnicodeString GlobalData::rva002360FC() const
{
	return m_wide1244;
}
