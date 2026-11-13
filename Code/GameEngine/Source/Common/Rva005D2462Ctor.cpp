// cl: /Ireference/shims/bfme2_ascii /MD
// ??0Rva005D2462@@QAE@HABVAsciiString@@HH@Z retail 0x005D2462 42B
// Evidence: calls base 0x00528B06 (int AsciiString); stores +0x10 +0x14; vtable 0x008757E4; ret 0x10; callers 0x0052975A 0x005D2778
#include "ascii_string.h"

#include "../../Include/Common/Rva005C31FB.h"

#include "../../Include/Common/Rva00528B06.h"

class Rva005D2462 : public Rva00528B06
{
public:
	Rva005D2462(int level, const AsciiString &name, int a, int b);
private:
	int m_10;
	int m_14;
};

Rva005D2462::Rva005D2462(int level, const AsciiString &name, int a, int b) : Rva00528B06(level, name), m_10(a), m_14(b)
{
}
