// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /ICode/Libraries/Include/Lib
class FreelistPool;
extern FreelistPool g_freelistPool00DB8FEC;
// FormationAssistant formation build (WB twins 0x0113B990 and 0x0113C210 in
// FormationAssistant.cpp, unnamed there).
//
// ?rva0042481E@FormationAssistant@@QAE_NPAVFormationRowList@@PBVFormationTemplateRows@@PAVFormationObjectList@@@Z
// @0x0042481E 384B: appends one slot row to the row list, sized to the
// template's cell count, and fills it centre-out (idx, idx+1, idx-1, ...):
// each cell takes the first candidate entry whose filter accepts an unused
// object, records entry, object and the 0x00422377 offset, and erases the
// object from the pool. A row that took nothing is popped again; the result
// says whether anything was placed.
// Evidence: retail body; WB twin 0x0113B990 gives the countdown loop, the
// centre-out walk and the found flag. Callees are the rowed STLport helpers
// (list push_back 0x004246BD, zero resize 0x0042468D, pop_back 0x004246D7,
// pooled erase 0x0029DFC5) and filter accepts 0x00362437.

#include "BfmeE16.h"

// The erased iterator's complete existing36B provider stays visible below.
// MSVC then reuses the dead candidate spill[-20] for its hidden return buffer;
// a declaration-only call allocated an extra slot and shifted the whole frame.
// Canonical BfmeE16 supplies storage; FormationSlot is the target field view.
// EH handlerB8709C -> FuncInfoD34564: one state, temporary FormationRow
// cleanup atB87094. All384 body bytes and its EH graph are verified.
typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class Player;

void __cdecl Rva00030830GameFree(void *) throw();

struct Rva00422377Out
{
	Int x;
	Int y;
};
struct Rva00422377In;
void Rva00422377Get(Rva00422377Out *out, Rva00422377In *obj);

#include "../../../Include/GameLogic/Module/Rva2225E0Filter.h"

// One template candidate: its filter at +0.
struct FormationCandidate
{
	Rva2225E0Filter *m_filter;
};

// One placed slot (16 bytes): candidate, object and its offset.
struct FormationSlot
{
	FormationCandidate *m_candidate;
	Object *m_object;
	Rva00422377Out m_offset;
};

namespace _STL
{
template <class _Tp> class allocator
{
public:
	allocator() {}
};
template <class _Tp> class char_traits;
template <class _Tp, class _Traits, class _Alloc> class basic_string;

template <class _Value, class _Tp, class _MaybeReboundAlloc> class _STLP_alloc_proxy : public _MaybeReboundAlloc
{
public:
	__declspec(noinline) _STLP_alloc_proxy(const _MaybeReboundAlloc &a, _Value p) : _MaybeReboundAlloc(a), _M_data(p) {}
	_Value _M_data;
};

template <class _Tp, class _Alloc> class _Vector_base
{
public:
	__declspec(noinline) _Vector_base(const _Alloc &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {}
	_Tp *_M_start;
	_Tp *_M_finish;
	_STLP_alloc_proxy<_Tp *, _Tp, _Alloc> _M_end_of_storage;
};

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};
template <class _Tp> struct _Nonconst_traits;
template <class _Tp, class _Traits> struct _List_iterator
{
	_List_iterator(_List_node_base *x) : _M_node(x) {}
	_List_iterator(const _List_iterator &x) : _M_node(x._M_node) {}
	_List_node_base *_M_node;
};

template <class _Tp, class _Alloc = allocator<_Tp> > class list
{
public:
	void push_back(const _Tp &x);
	void pop_back();
	_List_node_base *_M_node;
};
}

class BfmeE16Vector : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	void rva0042468D(unsigned int n);
	FormationSlot &operator[](unsigned int i) { return *(FormationSlot*)&_M_start[i]; }
};

// Temporary row: the folded _Vector_base<int> constructor 0x00211E58 and an
// inline free of its storage.
class FormationRow : public _STL::_Vector_base<int, _STL::allocator<int> >
{
public:
	explicit FormationRow(const _STL::allocator<int> &a = _STL::allocator<int>()) : _STL::_Vector_base<int, _STL::allocator<int> >(a) {}
	~FormationRow()
	{
		if (_M_start)
			Rva00030830GameFree(_M_start);
	}
};

class Rva004246BDObj;
typedef _STL::list<Rva004246BDObj *> Rva004246BDList;
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BfmeStlString;
typedef _STL::list<BfmeStlString> BfmeStlStringList;

// list<vector<BfmeE16> >: rows hang at node+8.
class FormationRowList
{
public:
	BfmeE16Vector &back() { return *(BfmeE16Vector *)(m_node->_M_prev + 1); }
	_STL::_List_node_base *m_node;
};

struct FormationCandidateVector
{
	FormationCandidate **m_begin;
	FormationCandidate **m_end;
	FormationCandidate **m_cap;
	Int size() const { return m_end - m_begin; }
	FormationCandidate *operator[](Int i) const { return m_begin[i]; }
};

class FormationTemplateRows
{
public:
	unsigned int size() const { return m_end - m_begin; }
	const FormationCandidateVector &operator[](unsigned int i) const { return m_begin[i]; }
	FormationCandidateVector *m_begin;
	FormationCandidateVector *m_end;
	FormationCandidateVector *m_cap;
};

typedef _STL::_List_iterator<Object *, _STL::_Nonconst_traits<Object *> > ObjectListIter;

class Rva0029DFC5List
{
public:
	__declspec(noinline) ObjectListIter rva0029DFC5(ObjectListIter position) {
 _STL::_List_node_base *node=position._M_node;
 _STL::_List_node_base *prev=node->_M_prev;
 _STL::_List_node_base *next=node->_M_next;
 prev->_M_next=next;next->_M_prev=prev;
 node->_M_next=(_STL::_List_node_base*)(*(void **)((char *)&::g_freelistPool00DB8FEC + 8));
 (*(void **)((char *)&::g_freelistPool00DB8FEC + 8))=node;
 return ObjectListIter(next);
}
};

#include "../../../Include/Common/ObjectListNode.h"

class FormationObjectList
{
public:
	ObjectListNode *m_node;
};

#include "../../../../Libraries/Source/WWVegas/WWLib/FormationAssistant.h"

Bool FormationAssistant::rva0042481E(FormationRowList *rows, const FormationTemplateRows *cells, FormationObjectList *objects)
{
	Bool placed = false;
	((Rva004246BDList *)rows)->push_back(*(Rva004246BDObj *const *)&FormationRow());
	BfmeE16Vector &row = rows->back();
	row.rva0042468D(cells->size());

	Int step = 1;
	Int sign = 1;
	unsigned int idx = (cells->size() - 1) / 2;
	for (Int remainingCells = cells->size(); remainingCells > 0; --remainingCells)
	{
		const FormationCandidateVector &candidates = (*cells)[idx];
		for (Int j = 0; j < candidates.size(); ++j)
		{
			FormationCandidate *candidate = candidates[j];
			if (candidate && candidate->m_filter)
			{
				ObjectListNode *it;
				for (it = objects->m_node->m_next; it != objects->m_node; it = it->m_next)
				{
					if (candidate->m_filter->accepts(it->m_data, 0))
					{
						FormationSlot &slot = row[idx];
						slot.m_object = it->m_data;
						slot.m_candidate = candidate;
						Rva00422377Out offset;
						Rva00422377Get(&offset, (Rva00422377In *)it->m_data);
						slot.m_offset = offset;
						((Rva0029DFC5List *)objects)->rva0029DFC5(ObjectListIter((_STL::_List_node_base *)it));
						placed = true;
						goto nextCell;
					}
				}
			}
		}
	nextCell:
		idx += step * sign;
		++step;
		sign *= -1;
	}

	if (!placed)
	{
		((BfmeStlStringList *)rows)->pop_back();
		return false;
	}
	return true;
}
