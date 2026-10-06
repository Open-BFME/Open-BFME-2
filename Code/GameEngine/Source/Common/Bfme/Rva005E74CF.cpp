// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva005E74CF@@QAE@XZ @0x005E74CF 90B
// Ctor with temp AsciiString "BuildQueueDetailsPanel" passed as int to base
// ??0Rva00221635@@QAE@H@Z then vtable 0x00877EF4 plus +8 0x80FFFFFF +0xC 0.
// Evidence: packet disasm with rowed StringBase ctor 0x00037BA0 plus releaseBuffer
// 0x00036410 plus pin base 0x00221635 plus literals; vtable from mov [esi];
// next dtor Rva005E7529 flags; +8/+0xC as separate subobjects to keep mov then and.
#include "ascii_string.h"
class Rva00221635
{
public:
	Rva00221635(int arg);
	~Rva00221635();
	virtual void _pure() = 0;
	int m_4;
};
extern const void *const g_00C77EF4[];
struct Rva005E74CFM8
{
	int m_8;
	Rva005E74CFM8()
	{
		m_8 = (int)0x80FFFFFF;
	}
};
struct Rva005E74CFMC
{
	int m_C;
	Rva005E74CFMC()
	{
		m_C = 0;
	}
};
class Rva005E74CF : public Rva00221635
{
public:
	Rva005E74CF();
private:
	Rva005E74CFM8 m_08;
	Rva005E74CFMC m_0C;
};
Rva005E74CF::Rva005E74CF() : Rva00221635((int)&AsciiString("BuildQueueDetailsPanel"))
{
}
