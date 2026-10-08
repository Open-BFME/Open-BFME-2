// cl: /O1 /MD /EHs /Ireference/shims/moduledata
//
// ??1Rva00427611@@UAE@XZ retail 0x00427611 82B.
// MI dtor in the shape of Rva002D3573Dtor.cpp: primary GameEngineDeletingBase
// (size 0xC) at +0 with vtable 0x00C3C644, secondary Snapshot at +0xC with
// vtable 0x00C3C634 restored to 0x00BBB554 by the inline Snapshot dtor, then
// the rowed ??1GameEngineDeletingBase@@UAE@XZ at 0x001B4E74. Between them,
// under unwind state 1, the member at +0x10 frees its buffer through the
// rowed _free 0x00030830 when set: the inlined teardown of a malloc-config
// vector of trivially destructible elements. /EHs keeps the unwind frame
// retail has around that C call. The snapped-boundary queue named it
// Anim2DCollection's dtor; that identity is not established, so the names
// are generated and the member is declared as only its buffer pointer.

extern "C" void __cdecl free(void *p);

class Rva00427611Buffer
{
public:
	~Rva00427611Buffer() { if (m_start) free(m_start); }
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

#include "Common/Snapshot.h"

class Rva00427611 : public GameEngineDeletingBase, public Snapshot
{
public:
	virtual ~Rva00427611();
private:
	Rva00427611Buffer m10;
};

inline Rva00427611::~Rva00427611()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva00427611DtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva00427611DtorInlineAnchor()
{
    static_cast<Rva00427611 *>(0)->Rva00427611::~Rva00427611();
}
#pragma inline_depth()
