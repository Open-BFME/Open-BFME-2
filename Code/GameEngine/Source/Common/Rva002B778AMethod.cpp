// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva002B778A@Rva002B778A@@QAEXABVAsciiString@@@Z @0x002B778A 24B.
// Find-by-name then erase/notify: rowed Rva002B68AA find 0x002B68AA on this
// with the name ref, then rowed Rva002B4CED erase 0x002B4CED on this with the
// found element. Evidence: thiscall ret 4 single const-ref arg; push order and
// both this uses (ecx=this) match; caller at 0x00564F50; same +0xBC vector
// container family as both callees.
#include "ascii_string.h"
struct FindElem002B68AA;
class Rva002B68AA
{
public:
	FindElem002B68AA *rva002B68AA(const AsciiString &name);
};
class Rva002B4CED
{
public:
	void rva002B4CED(void *p);
};
class Rva002B778A
{
public:
	void rva002B778A(const AsciiString &name);
};
void Rva002B778A::rva002B778A(const AsciiString &name)
{
	FindElem002B68AA *elem = ((Rva002B68AA *)this)->rva002B68AA(name);
	((Rva002B4CED *)this)->rva002B4CED(elem);
}
