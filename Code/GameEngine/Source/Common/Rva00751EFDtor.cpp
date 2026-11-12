// cl: /O1 /MD /EHsc
// ??1Rva00751EF@@UAE@XZ, retail 0x000751EF..0x00075279 (138 bytes, EH):
// the destructor the rowed scalar deleting destructor ??_GRva00751EF calls
// (call at 0x0007527C; table 0x00BC6620 slot 0). It hands the
// +0x28 display string back to TheDisplayStringManager (slot 15) when both
// exist, releases and clears the five reference-counted pointers at +0x11C,
// clears the static at 0x00DE1ED0, then the twenty 0x0C-byte records at
// +0x2C die through the eh vector destructor iterator with the shared
// first-pointer-free body 0x0007FAB3, and the vptr falls back to the base
// table 0x00BC65A8 (deleting destructor plus three pure slots). Owner
// identity and field roles are not established; names stay address-derived.
#include "../../Include/Common/Rva00074626.h"

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

// The record's teardown frees its first pointer: the 14-byte body retail
// ICF-folds with vector<int>'s destructor at 0x0007FAB3.
struct Rva000751EFSlot
{
	void *m_first;
	unsigned char m_data[0x0C - 4];
	~Rva000751EFSlot()
	{
		if (m_first != 0)
			free(m_first);
	}
};

class Rva000751EFRef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

class DisplayStringManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void freeDisplayString(void *string);
};
extern DisplayStringManager *TheDisplayStringManager;

void * g_00DE1ED0;	// retail RVA 0x009E1ED0 (.bss), defined here

class Rva00751EF : public Rva00074626
{
public:
	virtual ~Rva00751EF();
private:
	unsigned char m_pad04[0x28 - 4];
	void *m_string28;			// +0x28
	Rva000751EFSlot m_slots[20];		// +0x2C
	Rva000751EFRef *m_refs[5];		// +0x11C
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00751EF::~Rva00751EF()
{
	if (m_string28 && TheDisplayStringManager)
		TheDisplayStringManager->freeDisplayString(m_string28);
	for (int i = 0; i < 5; ++i)
	{
		if (m_refs[i])
		{
			m_refs[i]->Release_Ref();
			m_refs[i] = 0;
		}
	}
	g_00DE1ED0 = 0;
}

// Rva0007517F (ctor 0x0007517F) installs the same vtable 0x00BC6620, whose
// slot 0 0x00075279 calls this destructor.
#pragma comment(linker, "/alternatename:??1Rva0007517F@@UAE@XZ=??1Rva00751EF@@UAE@XZ")

// ?bfmeAnchorRva00751EFDtor absent-from-retail
void bfmeAnchorRva00751EFDtor(Rva00751EF *p)
{
	p->Rva00751EF::~Rva00751EF();
}
