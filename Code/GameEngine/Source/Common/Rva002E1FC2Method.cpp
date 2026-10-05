// cl: /Ireference/shims/bfmelist /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva002E1FC2@Rva002E1FC2@@QAEXXZ 0x002E1FC2 139 merge second map minus first via rowed increment fetch and forEach vtable 0x00875590 callers 0x0020F53F
#define _STLP_NO_EXCEPTIONS 1
#include <map>

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

extern Rva002BA8F1Logic *g_009FEF10;

// &rva005CC208 compiles to MSVC's vcall thunk for its vtable slot, and retail's DIR32 at
// +0x6A is 0x009CC208 = mov eax,[ecx]; jmp [eax+8]: the slot at +8 (??_9@$B7AE). As the
// only virtual (slot 0) it named the +0 thunk 0x005FF3A9 and failed DIR32 consistency.
class Rva005CC208
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void rva005CC208();
};

class Rva002E1FC2
{
public:
	void rva002E1FC2();
private:
	char m_pad0[4];
	Rva002E1E6FList m_list;
	char m_pad1[0x29C - 4 - 16];
	_STL::map<int, int> m_map1;
	_STL::map<int, int> m_map2;
};

void Rva002E1FC2::rva002E1FC2()
{
	_STL::map<int, int>::iterator it1 = m_map1.begin();
	_STL::map<int, int>::iterator it2 = m_map2.begin();
	while (it2 != m_map2.end()) {
		if (it1 == m_map1.end() || (*it1).first > (*it2).first) {
			Rva0020E8DBEntry *entry = g_009FEF10->m_holder->m_db->rva0020E8DB((*it2).first);
			if (entry != 0) {
				m_list.forEach((void (Rva002E1E6FListener::*)(void *, int, int))&Rva005CC208::rva005CC208, this, (int)entry, (int)&entry->m_extra);
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
