// cl: /DNDEBUG /MD /EHsc
// Retail 0x00418F7D..0x0041901D: 160-byte cdecl INI field parser.
// Target evidence: Target/Priority subtokens; eight AutoResolveUnit names at
// VA 0x00DC85C4; availability word array beginning at store+0x10; map at +4.
// Known callees and the INIException ThrowInfo establish the parser's behavior.
// The Target FieldParse entry at VA 0x00C3A9A8 identifies the standard four-
// argument callback ABI; instance and userData are unused by this body.
// The original parser and receiver names are unknown; the RVA names preserve
// that uncertainty. The saved attempt at reverse/attempts/0x00418f7d.cpp was
// the structural starting point, independently checked against retail.
// /O1 needs forced-inline bit accessors and a reference-taking key constructor.
// The branch-local exception lets its storage share the key temporary's slot.

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

#include "../../Include/Common/INI/INI.h"

#include "../../../../reference/shims/iniexception/Common/INIException.h"

// Rowed 0x00418BE3: bounds-checked index into the eight AutoResolveUnit_* names.
const char *getAutoResolveUnitNameFromIndex(int index);
extern const char *g_Va00DC85C4Names[];

struct Rva00418BFBKey
{
	int lo;
	int hi;
	__forceinline Rva00418BFBKey(const int &lowValue, const int &highValue) : lo(lowValue), hi(highValue) {}
};
#include "../../Include/Common/Rva00418BFBNode.h"
#include "../../Include/Common/Rva00418BFBComp.h"
struct Rva00418BFBIter
{
	Rva00418BFBNode *node;
};
struct Rva00418BFBPair
{
	Rva00418BFBNode *first;
	bool second;
	Rva00418BFBPair(Rva00418BFBNode *f, bool inserted) : first(f), second(inserted) {}
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

struct Rva00418F7DFlags
{
	unsigned int words[1];
	__forceinline bool test(unsigned int index) const { return (words[index >> 5] & (1u << (index & 31))) != 0; }
	__forceinline void clear(unsigned int index) { words[index >> 5] &= ~(1u << (index & 31)); }
};
struct Rva00418F7DStore
{
	int _pad0;
	Rva00418DE2 m_map;
	Rva00418F7DFlags m_bits;
};

void __cdecl Rva00418F7DParse(INI *ini, void * /*instance*/, void *priorityStorePtr, const void * /*userData*/)
{
	Rva00418F7DStore *priorityStore = static_cast<Rva00418F7DStore *>(priorityStorePtr);
	const char *targetToken = ini->getNextSubToken("Target");
	unsigned int index = (unsigned int)ini->scanIndexList(targetToken, g_Va00DC85C4Names);
	const char *priorityToken = ini->getNextSubToken("Priority");
	int attackPriority = ini->scanInt(priorityToken);

	if (!priorityStore->m_bits.test(index))
	{
		throw INIException(3, "Cannot redefine attack priority for unit type %s", getAutoResolveUnitNameFromIndex((int)index));
	}

	if (attackPriority == 0)
		return;

	priorityStore->m_bits.clear(index);
	priorityStore->m_map.rva00418DE2(Rva00418BFBKey((int)index, attackPriority));
}
