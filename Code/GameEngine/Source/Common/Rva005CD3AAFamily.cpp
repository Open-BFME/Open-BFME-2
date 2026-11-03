// cl: /MD /EHsc
// Family 0: 0x005CD3AA, 0x005CD43D, 0x005CD4D0 (147 bytes each, total 441 bytes)
// Factory helpers constructing refcounted Rva005CD257/Rva005CD2A3/Rva005CD2EF elements
// and adding them to Rva005CD1A9 container.

#include "../../../Libraries/Source/Apt/AptRefTarget.h"

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct BfmeRefPtr
{
	TargetRef00217D4C *m_ptr;

	BfmeRefPtr(TargetRef00217D4C *target = 0) : m_ptr(target)
	{
		if (m_ptr)
			++m_ptr->references;
	}

	BfmeRefPtr(const BfmeRefPtr &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}

	~BfmeRefPtr()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class Rva005CD1A9
{
public:
	void AddItem(BfmeRefPtr *item);
};

class Rva005CD257 : public TargetRef00217D4C
{
public:
	Rva005CD257(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

class Rva005CD2A3 : public TargetRef00217D4C
{
public:
	Rva005CD2A3(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

class Rva005CD2EF : public TargetRef00217D4C
{
public:
	Rva005CD2EF(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

void rva005CD3AA(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *textSource)
{
	BfmeRefPtr item(new Rva005CD257(container, p1, p2, p3, textSource));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

void rva005CD43D(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *textSource)
{
	BfmeRefPtr item(new Rva005CD2A3(container, p1, p2, p3, textSource));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

class Rva005CDMorph : public TargetRef00217D4C
{
public:
	Rva005CDMorph(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

void rva005CD4D0(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *textSource)
{
	BfmeRefPtr item(new Rva005CD2EF(container, p1, p2, p3, textSource));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

void rva005CD563(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *textSource)
{
	BfmeRefPtr item(new Rva005CDMorph(container, p1, p2, p3, textSource));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005CD0C2 reads ?AddItem@Checklist@StrategicInGameUI@@QAEXABUChecklistItemRef@2@@Z
#pragma comment(linker, "/alternatename:?AddItem@Rva005CD1A9@@QAEXPAUBfmeRefPtr@@@Z=?AddItem@Checklist@StrategicInGameUI@@QAEXABUChecklistItemRef@2@@Z")
//   0x005CD257 reads ?setup84@Rva005CDMorph@@QAEPAV1@HHHHH@Z
#pragma comment(linker, "/alternatename:??0Rva005CD257@@QAE@PAVRva005CD1A9@@PAX111@Z=?setup84@Rva005CDMorph@@QAEPAV1@HHHHH@Z")
//   0x005CD2A3 reads ?setupA0@Rva005CDMorph@@QAEPAV1@HHHHH@Z
#pragma comment(linker, "/alternatename:??0Rva005CD2A3@@QAE@PAVRva005CD1A9@@PAX111@Z=?setupA0@Rva005CDMorph@@QAEPAV1@HHHHH@Z")
//   0x005CD2EF reads ?setupBC@Rva005CDMorph@@QAEPAV1@HHHHH@Z
#pragma comment(linker, "/alternatename:??0Rva005CD2EF@@QAE@PAVRva005CD1A9@@PAX111@Z=?setupBC@Rva005CDMorph@@QAEPAV1@HHHHH@Z")
//   0x005CD34B reads ?setupD8@Rva005CDMorph@@QAEPAV1@HHHHH@Z
#pragma comment(linker, "/alternatename:??0Rva005CDMorph@@QAE@PAVRva005CD1A9@@PAX111@Z=?setupD8@Rva005CDMorph@@QAEPAV1@HHHHH@Z")
