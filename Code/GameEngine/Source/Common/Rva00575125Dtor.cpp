// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva00575125@@UAE@XZ retail 0x00574C6E 83B
// Native secondary table C6E4C0 has one callback (5747CC); base C6E360
// has one empty RET4 callback (47A69C). Its destructor is nonvirtual.
// MI dtor: base Rva005746AF at +0 plus second base at +0x10 with member at +0x14.
// Evidence: vtable stores 0x00C6E4C4 then 0x00C6E4C0 then 0x00C6E360; rowed erase 0x002B7250 with this=second arg+4 and arg=sub at +0x10; pinned base dtor 0x005746D2; caller 0x00574E6D deleting dtor; neighbours share /O1. Honest Rva name.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
#include "../../Include/Common/Rva005746AF.h"
class Rva00575125Second
{
public:
	virtual void slot0(int);
	~Rva00575125Second();
};
inline Rva00575125Second::~Rva00575125Second() {}
class Rva00575125 : public Rva005746AF, public Rva00575125Second
{
public:
	virtual ~Rva00575125();
	virtual void slot0(int);
private:
	void *m_14;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00575125::~Rva00575125()
{
	((Rva002B7250 *)((char *)m_14 + 4))->rva002B7250((CreateAHeroData *)((char *)this + 0x10));
}

// ?bfmeAnchorRva00575125Dtor absent-from-retail
void bfmeAnchorRva00575125Dtor(Rva00575125 *p)
{
	p->Rva00575125::~Rva00575125();
}


void Rva00575125Second::slot0(int) {}
#include "../../Include/Common/Rva000AD6F4.h"

// Native C6E4C0 slot 0 receives the secondary-base pointer. MSVC adjusts
// this override's receiver by -0x10, producing the native [ecx-0x0C] load.
void Rva00575125::slot0(int)
{
	((Rva000AD6F4 *)(*(char **)((char *)this + 4) + 0x54))->~Rva000AD6F4();
}
