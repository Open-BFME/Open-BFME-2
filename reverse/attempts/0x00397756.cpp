// ?rva00397756@@YAXPAUIdRange@@H@Z
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00397756@@YAXPAUIdRange@@H@Z @0x00397756 59B: over every ObjectID in
// [first,last), resolve via rowed GameLogic::findObjectByID at 0x00049DC5 and
// pass found objects with the range to the pinned 0x0023D0C2 GameLogic entry.
// Evidence: ret 8 with the second arg dead (the call re-pushes the range),
// TheGameLogic global at 0x00DFE78C hoisted into ebx past the empty check,
// callee cleans its own arg (thiscall); flags and decls follow neighbouring
// Behavior TUs.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class GameLogic;

struct IdRange
{
	ObjectID *first;
	ObjectID *last;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void rva0023D0C2(Object *obj, int arg);
};

extern GameLogic *TheGameLogic;

void __cdecl rva00397756(IdRange *range, int /*unused*/)
{
	ObjectID *p = range->first;
	if (p == range->last)
		return;
	GameLogic *gameLogic = TheGameLogic;
	do {
		Object *obj = gameLogic->findObjectByID(*p);
		if (obj != 0)
			gameLogic->rva0023D0C2(obj, (int)range);
		++p;
	} while (p != range->last);
}
