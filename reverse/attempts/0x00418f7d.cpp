// ?Rva00418F7DParse@@YAXPAVINI@@PAXPAURva00418F7DStore@@@Z
// partial score=0.5 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
// ?Rva00418F7DParse@@YAXPAVINI@@PAXPAURva00418F7DStore@@@Z, retail 0x00418F7D, 160 bytes.
// INI field parser for auto-resolve attack priorities. Reads the Target and
// Priority subtokens, resolves the unit index through the eight-entry
// AutoResolveUnit_* table at 0x00DC85C4, and guards the per-index availability
// bit: taken bits throw INIException code 3 with retail literal "Cannot
// redefine attack priority for unit type %s" (string_xrefs.tsv), zero
// priorities return silently, otherwise the bit is claimed and the
// (index, priority) key is inserted through the rowed 0x00418DE2 forwarder
// (whose comment names this address as the unblocked caller).
// Evidence: four retail string/DIR32 anchors (Target, Priority, Cannot...,
// AutoResolveUnit table), all six callees rowed (getNextSubToken 0x2E06B,
// scanIndexList 0x2BD39, scanInt 0x2ECCF, getAutoResolveUnitNameFromIndex
// 0x418BE3, INIException ctor 0x2F681, _CxxThrowException), clean ret boundary
// after ret-8 at 0x418F7A, Ghidra FUN_00818f7d 160B. Sibling INI-parser shape
// follows AutoResolveArmorParse.cpp (honest Rva free function, rva002f681_fill
// plus _CxxThrowException). Receiver identity (real class/method name) is not
// established; the Rva spelling is honest, not a claim.

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	int scanInt(const char *token);
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void rva002f681_fill(void *e, int argCount, const char *format, ...);

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva00418F7DThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva00418F7DThrowInfoAnchor rva00418F7DThrowInfoAnchor = { 0, 0, 0, 0 };

// Rowed 0x00418BE3: bounds-checked index into the eight AutoResolveUnit_* names.
const char *getAutoResolveUnitNameFromIndex(int index);
extern const char *g_AutoResolveUnitNames[];

struct Rva00418BFBKey
{
	int lo;
	int hi;
};
struct Rva00418BFBNode
{
	int _c0;
	Rva00418BFBNode *_parent;
	Rva00418BFBNode *_left;
	Rva00418BFBNode *_right;
	Rva00418BFBKey _key;
};
struct Rva00418BFBComp
{
	bool operator()(const void *a, const void *b) const;
};
struct Rva00418BFBIter
{
	Rva00418BFBNode *node;
};
struct Rva00418BFBPair
{
	Rva00418BFBNode *first;
	bool second;
	Rva00418BFBPair(Rva00418BFBNode *f, bool s) : first(f), second(s) {}
};
struct Rva00418BFB
{
	Rva00418BFBNode *_head;
	int _size;
	Rva00418BFBComp _comp;
	Rva00418BFBIter rva00418C33(Rva00418BFBNode *x, Rva00418BFBNode *y, const Rva00418BFBKey &v, Rva00418BFBNode *w);
	Rva00418BFBPair rva00418D3C(const Rva00418BFBKey &v);
};
struct Rva00418DE2
{
	Rva00418BFB m_tree;
	Rva00418BFBPair rva00418DE2(const Rva00418BFBKey &v);
};

struct Rva00418F7DStore
{
	int _pad0;
	Rva00418DE2 m_map;
	int m_bits[8];
};

void __cdecl Rva00418F7DParse(INI *ini, void * /*instance*/, Rva00418F7DStore *store)
{
	const char *targetTok = ini->getNextSubToken("Target");
	unsigned int index = (unsigned int)ini->scanIndexList(targetTok, g_AutoResolveUnitNames);
	const char *priTok = ini->getNextSubToken("Priority");
	int value = ini->scanInt(priTok);

	unsigned int bit = 1u << (index & 31);
	unsigned int word = index >> 5;
	if ((store->m_bits[word] & bit) == 0)
	{
		INIException e;
		rva002f681_fill(&e, 3, "Cannot redefine attack priority for unit type %s", getAutoResolveUnitNameFromIndex((int)index));
		_CxxThrowException(&e, (const _s__ThrowInfo *)&rva00418F7DThrowInfoAnchor);
	}

	if (value == 0)
		return;

	store->m_bits[word] &= ~bit;

	Rva00418BFBKey key;
	key.lo = (int)index;
	key.hi = value;
	store->m_map.rva00418DE2(key);
}
