// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva00407A6A@Rva00407A6A@@QAE_NABVUnicodeString@@@Z retail 0x00407A6A 124B
// Evidence: unlock lane; wide compare 0x00006A7A plus set pin 0x00037150 plus isEmpty 0x00001E2F plus CoCreateGuid IAT plus format 0x00038150 plus string 0x00838C88; callers 0x00409375 0x005B4C10; prev Rva004076EE same /O1.
#include "ascii_string.h"
#include "unicode_string.h"
struct GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};
extern "C" __declspec(dllimport) long __stdcall CoCreateGuid(GUID *guid);
class Rva00407A6A
{
public:
	bool rva00407A6A(const UnicodeString &arg);
private:
	char m_pad00[8];
	UnicodeString m_wide08;
	char m_pad0C[0x38 - 0x0C];
	unsigned long m_flags38;
	char m_pad3C[0x4C - 0x3C];
	AsciiString m_ascii4C;
	char m_pad50[0x71 - 0x50];
	unsigned char m_flag71;
};
bool Rva00407A6A::rva00407A6A(const UnicodeString &arg)
{
	if (m_wide08.compare(arg) != 0) {
		m_wide08.set(arg);
		m_flags38 |= 0x10;
	}
	if (m_ascii4C.isEmpty()) {
		GUID guid;
		CoCreateGuid(&guid);
		m_ascii4C.format("%X%X%X%X%X%X%X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3]);
		m_flag71 = 1;
	}
	return true;
}
