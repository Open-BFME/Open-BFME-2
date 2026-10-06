// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
// ?step@Rva005E5565@@QAEXXZ @0x005E5565 16B via Helper-then-virtual twin of RvaHelperMemberSteps
// Evidence: push esi/mov esi/call rowed ?validate@?$StringBase@G@@ABEXXZ 0xB3FD0 then vptr+0xC tail-jmp;
// neighbours table slots with deleting dtors/NullForwarder/validate; prev 0x5E5554 step in same dir.
#include "ascii_string.h"
template <> class StringBase<unsigned short>
{
	friend class Rva005E5565;
	void validate() const;
};
class Rva005E5565
{
public:
	void step();
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
};
void Rva005E5565::step()
{
	((StringBase<unsigned short> *)this)->validate();
	this->f3();
}
