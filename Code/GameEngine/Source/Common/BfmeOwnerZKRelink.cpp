// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <stl/_algobase.h>
// Keep the shared out-of-line max provider; the inlined operation is unchanged.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
// Neutral storage for an x86 list-slot address, not the original element type.
// This aggregate is POD; STLport needs user-type traits stated explicitly.
struct BfmeScriptSlotAddress { unsigned int address; };
typedef char ScriptSlotAddressWidth[sizeof(BfmeScriptSlotAddress) == 4 ? 1 : -1];
namespace _STL {
template<> struct __type_traits<BfmeScriptSlotAddress> : __type_traits_aux<1> {};
}
#include <deque>


//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeOwnerZKRelink.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeOwnerZK::bfmeRelinkZK 0x003B8556 (51B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Retail RVA 0x0035DCF0. The body walks a singly linked list to find the slot
// that points at one node and then forwards to BfmeOwnerZK::bfmeMoveZK at
// 0x0035D940, which is what places it on that class.

// Measured target prefixes used by the move helper below. These Bfme names
// are donor ABI views, not recovered original class identities.
class BfmeKeyZK
{
public:
	unsigned char m_head[0x2C];
	unsigned char m_table[4];
};

struct BfmeEntryZK
{
	unsigned char m_head[0x0E];
	short m_references;
	unsigned char m_tail[4];
};

class Rva003B573E
{
public:
	int rva003B820D(Rva003B573E *other, int index);
	unsigned char m_head[0x0C];
	BfmeEntryZK *m_records;
};

struct BfmeNodeZK
{
	BfmeNodeZK *m_bfmeNextZK;
	int m_bfmeIdZK;
	int m_bfmeKindZK;
};

struct BfmeHeadZK
{
	int m_bfmePadZK;
	BfmeNodeZK *m_bfmeFirstZK;
};

class BfmeOwnerZK
{
public:
	void bfmeRelinkZK(BfmeKeyZK *key, BfmeHeadZK *list, BfmeNodeZK *node,
		BfmeHeadZK *fallback, BfmeNodeZK **where);
	void bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to);
private:
	unsigned char m_head[0x2C];
	Rva003B573E m_table;
};

void BfmeOwnerZK::bfmeRelinkZK(BfmeKeyZK *key, BfmeHeadZK *list, BfmeNodeZK *node,
	BfmeHeadZK *fallback, BfmeNodeZK **where)
{
	BfmeNodeZK **slot = &list->m_bfmeFirstZK;

	while (*slot != node)
	{
		if (*slot == 0)
			return;

		slot = &(*slot)->m_bfmeNextZK;
	}

	bfmeMoveZK(key, slot, where != 0 ? where : &fallback->m_bfmeFirstZK);
}

// From BFME 1 BfmeConv1878.cpp at verified donor revision
// 968ca36c3265b295297e6aed45a6bd89ffe59c40. Target boundary is independently
// 0x003B847B..0x003B84C9 (RET 12); the existing relink body calls it.
// Native reads prove the table at +0x2C, its records at +0x38, the 0x14
// record stride and the signed short at +0x0E. The native first call is the
// independently verified 0x003B820D transfer; only that donor callee view
// changes here. Node words at +0/+4/+8 follow the three native stores.
void BfmeOwnerZK::bfmeMoveZK(BfmeKeyZK *key, BfmeNodeZK **from, BfmeNodeZK **to)
{
	int id = (*from)->m_bfmeIdZK;
	int index = m_table.rva003B820D((Rva003B573E *)key->m_table, id);
	if (index == -1)
		return;
	(*from)->m_bfmeIdZK = index;
	(*from)->m_bfmeKindZK = m_table.m_records[index].m_references;
	BfmeNodeZK *next = (*from)->m_bfmeNextZK;
	(*from)->m_bfmeNextZK = *to;
	*to = *from;
	*from = next;
}

class ScriptList { public: void takeScripts(ScriptList *source,BfmeNodeZK **from,BfmeNodeZK **to); };
// WB Scripts.cpp's takeScripts walks the source's next links, saves the
// addresses of those links, then transfers in reverse order. Retail has a
// complete 141-byte RET12 extent at 003B84C9..003B8556 and uses the rowed
// BfmeOwnerZK transfer (003B847B). That opaque node view preserves its native
// index/link words. The local holds list-slot addresses, not owned nodes.
void ScriptList::takeScripts(ScriptList *source,BfmeNodeZK **from,BfmeNodeZK **to)
{
    _STL::deque<BfmeScriptSlotAddress> slots;
    BfmeScriptSlotAddress slot;
    slot.address=reinterpret_cast<unsigned int>(from);
    for(;*reinterpret_cast<BfmeNodeZK**>(slot.address);slot.address=reinterpret_cast<unsigned int>(&(*reinterpret_cast<BfmeNodeZK**>(slot.address))->m_bfmeNextZK))
        slots.push_back(slot);
    while(!slots.empty()) {
        reinterpret_cast<BfmeOwnerZK*>(this)->bfmeMoveZK(reinterpret_cast<BfmeKeyZK*>(source),reinterpret_cast<BfmeNodeZK**>(slots.back().address),to);
        slots.pop_back();
    }
}
