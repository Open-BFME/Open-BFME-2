// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva003004C1@@QAE@ABVAsciiString@@ABE@Z retail 0x003004C1 27B
// Two-arg ctor: AsciiString key via rowed StringBase copy 0x365F0 then one byte from second ref to +4; caller 0x002056C1 forwards pair for insert; ret 8 proves two args.
#include "ascii_string.h"
class Rva003004C1
{
public:
	Rva003004C1(const AsciiString &key, const unsigned char &flag);
private:
	AsciiString m_key;
	unsigned char m_flag;
};
Rva003004C1::Rva003004C1(const AsciiString &key, const unsigned char &flag) : m_key(key), m_flag(flag)
{
}
