// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva003004E7@@QAE@ABVAsciiString@@ABURva003004E7Payload@@@Z retail 0x003004E7 39B
// Two-arg ctor: AsciiString key via rowed StringBase copy 0x365F0 then 12-byte payload via 3 moves; caller 0x00302555 builds pair for map insert 0x301ED9; ret 8 proves two args.
#include "ascii_string.h"
struct Rva003004E7Payload
{
	int a;
	int b;
	int c;
};
class Rva003004E7
{
public:
	Rva003004E7(const AsciiString &key, const Rva003004E7Payload &payload);
private:
	AsciiString m_key;
	int m_a;
	int m_b;
	int m_c;
};
Rva003004E7::Rva003004E7(const AsciiString &key, const Rva003004E7Payload &payload) : m_key(key), m_a(payload.a), m_b(payload.b), m_c(payload.c)
{
}
