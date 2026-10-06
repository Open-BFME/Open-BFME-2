// cl: /Ireference/shims/bfme2_ascii /MD /EHs-c-
// ??1Rva0033B1CD@@QAE@XZ @0x0033B1CD 17B dtor releases AsciiString plus UnicodeString tail
// Evidence: call releaseBuffer D 0x00036410 then tail jmp releaseBuffer G 0x00036E70; no vptr; neighbours ThingTemplate and BfmeStringRecord dtor
#include "ascii_string.h"
#include "unicode_string.h"
class Rva0033B1CD {
public:
	void rva0033B1CD();
private:
	AsciiString m_00;
	UnicodeString m_04;
};
void Rva0033B1CD::rva0033B1CD()
{
	m_00.clear();
	m_04.clear();
}
