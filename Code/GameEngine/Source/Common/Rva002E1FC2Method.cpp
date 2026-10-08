// cl: /Ireference/shims/bfmelist /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?CheckForRemovedMultiRegionBonuses@LivingWorldPlayer@@QAEXXZ 0x002E1FC2 139 merge second map minus first via rowed increment fetch and forEach vtable 0x00875590 callers 0x0020F53F

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define _STLP_NO_EXCEPTIONS 1
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva002E1E6FListener
{
public:
	virtual void notify(void *, int, int);
};

class Rva002E1E6FList
{
public:
	void forEach(void (Rva002E1E6FListener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const void *call);
private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
	unsigned int m_index;
};

struct Rva0020E8DBEntry
{
	int m_id;
	int m_extra;
};

class Rva0020E8DB
{
public:
	Rva0020E8DBEntry *rva0020E8DB(int key);
};

struct Rva0020E8DBHolder
{
	char m_pad[8];
	Rva0020E8DB *m_db;
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva0020E8DBHolder *m_holder;
};

// Target callback VA 0x009CC208 is the slot-two thunk 8B01FF6008.
// Rowed forEach/walk prove a receiver and three dword arguments;
// the listener's original class and method names remain unknown.
class Rva002E1FC2Slot2Callback
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void notify(void *, int, int);
};

class LivingWorldPlayer
{
public:
	void CheckForRemovedMultiRegionBonuses();
private:
	char m_pad0[4];
	Rva002E1E6FList m_list;
	char m_pad1[0x29C - 4 - 16];
	_STL::map<int, int> m_map1;
	_STL::map<int, int> m_map2;
};

void LivingWorldPlayer::CheckForRemovedMultiRegionBonuses()
{
	_STL::map<int, int>::iterator it1 = m_map1.begin();
	_STL::map<int, int>::iterator it2 = m_map2.begin();
	while (it2 != m_map2.end()) {
		if (it1 == m_map1.end() || (*it1).first > (*it2).first) {
			Rva0020E8DBEntry *entry = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_holder->m_db->rva0020E8DB((*it2).first);
			if (entry != 0) {
				m_list.forEach((void (Rva002E1E6FListener::*)(void *, int, int))&Rva002E1FC2Slot2Callback::notify, this, (int)entry, (int)&entry->m_extra);
			}
			++it2;
		} else if ((*it1).first == (*it2).first) {
			++it1;
			++it2;
		} else {
			++it1;
		}
	}
}
