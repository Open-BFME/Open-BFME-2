// ?rva00289180@ExperienceLevelSystem@@UAEXXZ
// partial score=0.91 date=2026-10-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00289180@ExperienceLevelSystem@@UAEXXZ retail 0x00289180 91 bytes v1.
// Slot 9 cleanup of ExperienceLevelSystem (vtable 0x007FB8F4): iterate hash_map at +0x0C
// via rowed hashtable begin 0x00427195 and operator++ 0x0041E832, walk each
// WindowVideo circular list via head at +0 until sentinel calling rowed
// Overridable::deleteOverrides 0x001E35ED, then clear map at +0x28 via rowed
// Rva0028881C::rva002889BB 0x002889BB. Layout mirrors Rva0028951F find.
// Evidence: vtable slot 9 of 0x007FB8F4 class of ??0Rva00289ABD; callers 0x00289D7A.
#include <map>
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline void *&_STL::vector<void*>::operator[](size_t __n) { return *(this->_M_start + __n); }
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return this->_M_finish; }
}

class GameWindow;
class WindowVideo;

#include "../../Include/Common/Overridable.h"

struct ListNode
{
	ListNode *m_next;
	int m_pad04;
};

class WindowVideo
{
public:
	ListNode *m_head;
};

class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
	{
		size_t operator()(const GameWindow *const &p) const
		{
			return (size_t)p;
		}
	};
};

typedef std::hash_map<const GameWindow *, WindowVideo *, WindowVideoManager::hashConstGameWindowPtr, std::equal_to<const GameWindow *> > WindowVideoMap;

class Rva0028881C
{
public:
	void rva002889BB();
private:
	void *m_00Head;
	int m_04Flag;
};

class ExperienceLevelSystem
{
public:
	virtual void rva00289180();
	char m_pad04[8];
	WindowVideoMap *m_hash0C;
	char m_pad10[0x18];
	Rva0028881C m_map28;
};

void ExperienceLevelSystem::rva00289180()
{
	WindowVideoMap::iterator tmp = m_hash0C->begin();
	WindowVideoMap::iterator jt = tmp;
	for (; jt != m_hash0C->end(); ++jt)
	{
		WindowVideo *&windowVideo = (*jt).second;
		for (ListNode *listNode = windowVideo->m_head; listNode != (ListNode *)windowVideo; listNode = listNode->m_next)
			((Overridable *)((char *)listNode + 8))->deleteOverrides();
	}
	m_map28.rva002889BB();
}
