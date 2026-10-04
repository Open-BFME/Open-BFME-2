// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??0Rva005D00A6@@QAE@XZ, retail 0x005D00A6, 90 bytes.
// Evidence: hardcoded "BattleResolver" AsciiString temp passed to base pinned at 0x00221635, then two 1000 stores and vtable store; caller at 0x007B4A1F.
#include "ascii_string.h"

class Rva00221635
{
public:
	virtual void f0();
	virtual ~Rva00221635() {}
	Rva00221635(const AsciiString &s);
private:
	int m_x;
};

class Rva005D00A6 : public Rva00221635
{
public:
	virtual void g0();
	Rva005D00A6();
private:
	int m_8;
	int m_c;
};

Rva005D00A6::Rva005D00A6() : Rva00221635(AsciiString("BattleResolver")), m_8(1000), m_c(1000)
{
}
