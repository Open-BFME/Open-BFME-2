// cl: /O1 /DNDEBUG /MD /GX-
// ??0Rva003FD3EF@@QAE@IABVRva0036CA00Str@@D@Z @0x003FD3C7 40B: constructor of the
// class whose vtable 0x007FE024 (dtor 0x003FD3EF, slot 4 0x003FD43B) derives from
// BfmeBaseVNH (pinned base ctor 0x003FD199, +4 scaled width, +8 flag); stores its own
// vtable, then copy-constructs the counted string handle at +0x0C through the rowed
// handle copy 0x000A8C7C. Without /EHsc: retail carries no unwind state here.
// Target evidence: bytes and callee relocations of 0x003FD3C7; layout from the rowed
// dtor Rva003FD3EFDtor.cpp (m_pad04[8], handle at +0x0C).
#include "../../Include/Common/Rva0036CA00Str.h"

class Xfer;
class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);
	virtual ~BfmeBaseVNH();

	unsigned m_bfme04;
	char m_bfme08;
};

class Rva003FD3EF : public BfmeBaseVNH
{
public:
	Rva003FD3EF(unsigned width, const Rva0036CA00Str &text, char flags);
	virtual ~Rva003FD3EF();
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual bool slot4();
	virtual void slot5();
	virtual int getType();
	Rva0036CA00Str m_0c;
};

Rva003FD3EF::Rva003FD3EF(unsigned width, const Rva0036CA00Str &text, char flags)
	: BfmeBaseVNH(width, flags)
	, m_0c(text)
{
}
