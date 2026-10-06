// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva005EA635@@QAE@XZ @0x005EA635 86B ctor with AsciiString temp plus base plus vtable
// Constructs AsciiString DynamicAutoResolveDialog passes to base Rva00221635 then installs vtable g_00C781B8 and +8=10; base needs dtor for EH states per lever
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
class Rva005EA635 : public Rva00221635
{
public:
	virtual void g0();
	Rva005EA635();
private:
	int m_val;
};
Rva005EA635::Rva005EA635() : Rva00221635(AsciiString("DynamicAutoResolveDialog"))
{
	m_val = 10;
}
