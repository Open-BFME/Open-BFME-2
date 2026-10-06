// ?rva00289180@Rva00289ABD@@UAEXXZ
// partial score=0.91 date=2026-10-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00289180@Rva00289ABD@@UAEXXZ retail 0x00289180 91 bytes v1.
// Slot 9 cleanup of Rva00289ABD (vtable 0x007FB8F4): iterate hash_map at +0x0C
// via rowed hashtable begin 0x00427195 and operator++ 0x0041E832, walk each
// WindowVideo circular list via head at +0 until sentinel calling rowed
// Overridable::deleteOverrides 0x001E35ED, then clear map at +0x28 via rowed
// Rva0028881C::rva002889BB 0x002889BB. Layout mirrors Rva0028951F find.
// Evidence: vtable slot 9 of 0x007FB8F4 class of ??0Rva00289ABD; callers 0x00289D7A.
#include <map>
#include <hash_map>

class GameWindow;
class WindowVideo;

class Overridable
{
public:
	Overridable *deleteOverrides();
};

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

class Rva00289ABD
{
public:
	virtual void rva00289180();
	char m_pad04[8];
	WindowVideoMap *m_hash0C;
	char m_pad10[0x18];
	Rva0028881C m_map28;
};

void Rva00289ABD::rva00289180()
{
	WindowVideoMap::iterator tmp = m_hash0C->begin();
	WindowVideoMap::iterator jt = tmp;
	for (; jt != m_hash0C->end(); ++jt)
	{
		WindowVideo *&v = (*jt).second;
		for (ListNode *n = v->m_head; n != (ListNode *)v; n = n->m_next)
			((Overridable *)((char *)n + 8))->deleteOverrides();
	}
	m_map28.rva002889BB();
}
