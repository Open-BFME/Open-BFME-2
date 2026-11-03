// cl: /MD /GX /D_CRTIMP=
// ??1Rva005AA55D@@UAE@XZ @0x005AA55D 81B: virtual dtor of unknown class
// (vptr 0x00871EB0 stored at +0x0). Member at +0x58 points at a heap record
// whose +0x4 buffer is released with _free (row 0x00030830) before the record
// itself goes through global operator delete (row ??3@YAXPAX@Z); then the base
// dtor ??1Rva005DC73C@@UAE@XZ (row 0x005DC73C) runs. Evidence: vtable store,
// EH prolog with state stores, free/delete pair, base call, and the 28B
// caller at 0x005AA62B (unclaimed, ??_G shape). Base size unproven: base is
// declared vptr-only here and the derived pads to the retail +0x58 offset.
#include <stdlib.h>
#include <new>

class AITacticOffensive
{
public:
	virtual ~AITacticOffensive();
};

struct Rva005AA55DData
{
	void *m_00;
	void *m_buf;
};

class AIFlankAttackTactic : public AITacticOffensive
{
public:
	virtual ~AIFlankAttackTactic();

private:
	unsigned char m_pad[0x54];
	Rva005AA55DData *m_route;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIFlankAttackTactic::~AIFlankAttackTactic()
{
	// The destination's existing +0x58 owner is m_route. Keep the destructor's
	// observed two-word prefix view when composed with its vector owner.
	Rva005AA55DData *data = reinterpret_cast<Rva005AA55DData *>(m_route);
	if (data != 0) {
		if (data->m_buf != 0)
			free(data->m_buf);
		delete data;
	}
}

// ?bfmeAnchorAIFlankAttackTacticDtor absent-from-retail
void bfmeAnchorAIFlankAttackTacticDtor(AIFlankAttackTactic *tactic)
{
	tactic->AIFlankAttackTactic::~AIFlankAttackTactic();
}
