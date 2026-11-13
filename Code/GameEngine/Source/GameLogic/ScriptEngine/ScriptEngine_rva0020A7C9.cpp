// cl: /Ireference/shims/bfme2_ascii /EHs
// stlport
//
// Retail 0x0020A7C9 (144 bytes): ScriptEngine clears the +0x1A120 vector,
// then records each world object's non-empty name and pointer. Target calls
// the already-matched vector erase at 0x00207F0D, GameLogic::getFirstObject
// at 0x0023CAD2, and the rowed string/vector helpers used by the loop.
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct FXBoneInfo
{
public:
	AsciiString m_boneName; // +0x00
	const void *m_template; // +0x04
};

// This TU only calls the erase implementation owned by FXBoneInfoVectorErase.cpp.
// Keep this view declaration-only so STLport does not emit a second
// __copy_ptrs<FXBoneInfo *> COMDAT here.
namespace _STL
{
template <> class vector<FXBoneInfo, allocator<FXBoneInfo> >
{
public:
	typedef FXBoneInfo *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

class Object;

#include "../../../Include/GameLogic/Rva0020A227Element.h"

// Target views used by ScriptEngine::walkNamed at 0x0020A775. The node's
// first two words and the array offsets below come from that body; meanings
// beyond the observed accesses are intentionally left address-derived.
struct Rva003412E0Node
{
	Rva003412E0Node *m_next;
	int m_index;
};

class Rva00355950Arr
{
	public:
	char m_pad[0x38];
	void *m_entries;
};

// Reuse the established helper owner and signatures from ScriptLeafCheck.cpp.
// The walkNamed target passes its first argument as ECX to both methods.
class Rva003B489CHolder
{
public:
	bool check(const void *arg) const;
	int rva003B4885(const void *arg) const;

private:
	char m_pad[0x38];
	void *m_table;
};

struct Rva00355950Record
{
	char m_pad[0x2A];
	bool m_skip;
};

class Object
{
public:
	Object *getNextObject() { return m_next; }

	char m_pad[0x88];
	AsciiString m_name88;
	Object *m_next;
};

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class ScriptEngine
{
public:
	void rva0020A7C9();
	void walkNamed(Rva00355950Arr *array, Rva003412E0Node *node, bool requireMatch);
	void rva0020A586(void *record, void *entry);

private:
	char m_pad[0x1A120];
	_STL::vector<Rva0020A227Element> m_vec;
};

// bfme link decl-only begin
namespace _STL { template <> Rva0020A227Element * __uninitialized_copy<Rva0020A227Element *,Rva0020A227Element *>(Rva0020A227Element *,Rva0020A227Element *,Rva0020A227Element *,_STL::__false_type const &); }
namespace _STL { template <> Rva0020A227Element * __uninitialized_fill_n<Rva0020A227Element *,unsigned int,Rva0020A227Element>(Rva0020A227Element *,unsigned int,Rva0020A227Element const &,_STL::__false_type const &); }
namespace _STL { template <> void vector<Rva0020A227Element,_STL::allocator<Rva0020A227Element> >::_M_clear(); }
namespace _STL { template <> void vector<Rva0020A227Element,_STL::allocator<Rva0020A227Element> >::_M_insert_overflow(Rva0020A227Element *,Rva0020A227Element const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> Rva0020A227Element * _STLP_alloc_proxy<Rva0020A227Element *,Rva0020A227Element,_STL::allocator<Rva0020A227Element> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> Rva0020A227Element * allocator<Rva0020A227Element>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<Rva0020A227Element *,Rva0020A227Element,_STL::allocator<Rva0020A227Element> >::deallocate(Rva0020A227Element *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<Rva0020A227Element>::deallocate(Rva0020A227Element *,unsigned int) const; }
namespace _STL { template <> void vector<Rva0020A227Element,_STL::allocator<Rva0020A227Element> >::push_back(Rva0020A227Element const &); }
// bfme link decl-only end
void ScriptEngine::rva0020A7C9()
{
	_STL::vector<FXBoneInfo> &fv = (_STL::vector<FXBoneInfo> &)m_vec;
	fv.erase(fv.begin(), fv.end());
	GameLogic *gameLogic = TheGameLogic;
	if (gameLogic == 0)
		return;
	Object *obj = gameLogic->getFirstObject();
	if (obj == 0)
		return;
	for (; obj != 0; obj = obj->getNextObject()) {
		if (((StringBase<char> *)&obj->m_name88)->isEmpty())
			continue;
		Rva0020A227Element tmp;
		((StringBase<char> &)(tmp.key)).set((const StringBase<char> &)(obj->m_name88));
		tmp.obj = obj;
		m_vec.push_back(tmp);
	}
}

// ?walkNamed@ScriptEngine@@QAEXPAVRva00355950Arr@@PAURva003412E0Node@@_N@Z
// @0x0020A775 84B. The target walks the node chain, optionally tests each
// node with the rowed helper at RVA 0x003B489C, obtains its record through
// the rowed helper at RVA 0x003B4885, and calls the
// rowed-by-pin ScriptEngine helper at 0x0020A586 for records whose +0x2A byte
// is clear. The target evidence proves these accesses; record semantics remain
// unresolved.
void ScriptEngine::walkNamed(Rva00355950Arr *array, Rva003412E0Node *node, bool requireMatch)
{
	for (; node != 0; node = node->m_next) {
		const Rva003B489CHolder *holder = (const Rva003B489CHolder *)array;
		if (requireMatch && !holder->check(node))
			continue;
		Rva00355950Record *record = (Rva00355950Record *)holder->rva003B4885(node);
		if (!record->m_skip) {
			char *entry = (char *)array->m_entries + node->m_index * 0x14 + 8;
			rva0020A586(record, entry);
		}
	}
}
