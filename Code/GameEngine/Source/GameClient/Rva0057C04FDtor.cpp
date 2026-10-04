// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ??1Rva0057C04F@@QAE@XZ @0x0057C04F 69B: dtor destroying AsciiString at +8 and Rva0052413E at +0xC.
// Stores vtable 0x0086F2D4 then s_first0C 0x0086FFFC (folded CategoryModuleClass FXParticleSystem).
// Evidence: reverse member destruction order (+0xC then +8) with EH states 1 then 0 proves dtor;
// callees Rva dtor and StringBase releaseBuffer are rowed; unblocks 3 callees; neighbours share FX shard.
#include "ascii_string.h"
#pragma comment(linker, "/alternatename:??_7Base00@@6B@=_s_first0C")

class Rva0052413E
{
public:
	~Rva0052413E();
};
extern "C" int s_first0C;
struct Base00
{
	virtual void dummy();
	~Base00() {}
};
class Rva0057C04F : public Base00
{
public:
	~Rva0057C04F();
	virtual void dummy();
private:
	unsigned char m_pad04[4];
	AsciiString m_08; // +0x08
	Rva0052413E m_0C; // +0x0C
};

Rva0057C04F::~Rva0057C04F()
{
}
