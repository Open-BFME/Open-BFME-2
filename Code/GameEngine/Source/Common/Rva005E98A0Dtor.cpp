// cl: -O1 -arch:SSE -G7 -MD -EHsc
// ??1Rva005E98A0@@QAE@XZ retail 0x005E98A0 65B
// Pointee dtor run by the rowed owning-pointer reset 0x005E9E27. Body (EH
// state 0): reset the member at +0x18 through the rowed
// ?rva005E9705@Rva005E971F 0x005E9705, unload the content at +4 through the
// rowed ?rva0057C2CC@Rva0057C2CC 0x0057C2CC; then the +0x18 member's complete
// dtor runs the same reset. Supersedes Peppy's 0.85 stash
// reverse/attempts/0x005e98a0.cpp (it was a dtor, not a plain method).

class Rva005E9625 { public: virtual ~Rva005E9625(); };
#include <new>
struct Rva005E971F
{
    ~Rva005E971F();
    void rva005E9705();
    Rva005E9625 *m_ptr;
};
// Native member cleanup owns the complete26-byte reset at5E9705. It
// nulls the pointer before destroying and freeing the previous pointee.
Rva005E971F::~Rva005E971F()
{
    Rva005E9625 *old = m_ptr;
    m_ptr = 0;
    if (old) {
        old->Rva005E9625::~Rva005E9625();
        operator delete(old);
    }
}

#include "../../Include/Common/Rva0057C2CC.h"

class Rva005E98A0
{
public:
	~Rva005E98A0();

private:
	int m_00;
	Rva0057C2CC *m_content; // +0x04
	unsigned char m_pad08[0x18 - 8];
	Rva005E971F m_18; // +0x18
};

Rva005E98A0::~Rva005E98A0()
{
	m_18.rva005E9705();
	m_content->rva0057C2CC();
}
