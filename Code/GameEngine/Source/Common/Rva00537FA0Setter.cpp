// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00537FA0@Rva00537FA0@@QAEXABVAsciiString@@@Z @0x00537FA0 44B setter: if arg.compare(m_s24)!=0 then m_s24.set(arg) plus virtual [eax+0xc].
// Evidence: packet disassembly; callees rowed compare 0x000069D6 set 0x000366F0; prev row 0x00537F74 same shape at +0x20 with [eax+8].
#include "ascii_string.h"

class Rva00537FA0
{
public:
	virtual ~Rva00537FA0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	void rva00537FA0(const AsciiString &v);

private:
	unsigned char m_pad[0x20];
	AsciiString m_s24;
};

void Rva00537FA0::rva00537FA0(const AsciiString &v)
{
	const StringBase<char> &vs = reinterpret_cast<const StringBase<char> &>(v);
	StringBase<char> &ms = reinterpret_cast<StringBase<char> &>(m_s24);
	if (vs.compare(ms) != 0) {
		ms.set(vs);
		v3();
	}
}
