// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x0024955E, 55 bytes.
// ?rva0024955E@Rva0024955E@@QAEXVAsciiString@@@Z
// Honest address name: __thiscall (ret 4: one by-value AsciiString,
// destroyed in the EH epilogue via rowed narrow releaseBuffer). Translates
// the argument into the UnicodeString member at +0x1B0 via rowed
// UnicodeString::translate. Owner class unproven (four callers in unclaimed
// bodies), so the class carries the address. String models follow
// LANAPIRequestSetName, with releaseBuffer declared private to match the
// rowed AAE spellings. Unlock lane.
typedef unsigned short WideChar;
typedef bool Bool;

#include "ascii_string.h"


#include "unicode_string.h"

class Rva0024955E
{
public:
	void rva0024955E(AsciiString name);
	void rva00249595(AsciiString name);
private:
	char m_pad[0x1B0];
	UnicodeString m_name;
	UnicodeString m_name2;
};

void Rva0024955E::rva0024955E(AsciiString name)
{
	m_name.translate(name);
}

// Retail 0x00249595, 55 bytes. Twin of 0x0024955E above, translating into
// the adjacent UnicodeString member at +0x1B4. Same FuncInfo, callees and
// caller family.
void Rva0024955E::rva00249595(AsciiString name)
{
	m_name2.translate(name);
}
