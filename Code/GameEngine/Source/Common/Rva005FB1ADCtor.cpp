// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva005FB1AD@@QAE@PAX00@Z @0x005FB14E 95B.
// Constructor of the class whose destructor 0x005FB1AD is rowed (vtable
// 0x00C79EDC): base Rva006003FC(a,b,c) (constructor 0x00600432, pinned;
// its destructor 0x006003FC is rowed), store the vptr, then the +0x20
// owning pointer takes a new 0x54-byte Rva005FAD8D(this, c) (constructor
// 0x005FAFE8, pinned; its destructor 0x005FAD8D is pinned); a null new stays
// null. The same new-inner-into-member shape as the rowed 0x0056858C.
// Names are address-derived.
class Rva006003FC
{
public:
	virtual ~Rva006003FC();
	Rva006003FC(void *a, void *b, void *c);
};

#include "../../Include/Common/Rva005FAD8D.h"

struct Rva005FB14EMember
{
	void *m_value;
};

class Rva005FB1AD : public Rva006003FC
{
public:
	virtual ~Rva005FB1AD();
	Rva005FB1AD(void *a, void *b, void *c);
private:
	char m_unmodelled_04[0x1C];
	Rva005FB14EMember m_member;	// +0x20
};

Rva005FB1AD::Rva005FB1AD(void *a, void *b, void *c)
	: Rva006003FC(a, b, c)
{
	m_member.m_value = new Rva005FAD8D(this, c);
}
