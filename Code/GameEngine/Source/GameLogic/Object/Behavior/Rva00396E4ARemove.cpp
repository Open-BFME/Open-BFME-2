// cl: /Oy- /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00396E4A@Rva00396E4A@@QAEXPAVObject@@@Z @0x00396E4A 72B
// Map remove: find key from Object+0x74 in map at +0x8c via rowed _M_find
// 0x00388F63 (int-int spelling: _M_find only reads key at node+0x10 so value
// type does not change bytes; erase proves void* value), clear status 0x55,
// erase via rowed 0x005530A8 (int-void*).
// Evidence: ret 4 thiscall, test ebx null, [ebx+0x74] key, [ecx+0x8c] map,
// callers unclaimed, callees all rowed. /Oy- keeps retail EBP frame; local
// key copy reproduces retail mov/mov/lea.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

enum ObjectStatusTypes
{
	DUMMY_00 = 0x00,
	DUMMY_55 = 0x55
};
typedef bool Bool;

class Object
{
public:
	void setStatus(ObjectStatusTypes bit, Bool flag);
	char m_pad00[0x74];
	int m_key74;
};

class Rva00396E4A
{
public:
	void rva00396E4A(Object *obj);
private:
	char m_pad00[0x8c];
	_STL::map<int, void *> m_map8c;
};

void Rva00396E4A::rva00396E4A(Object *obj)
{
	if (obj == 0)
		return;
	int key = obj->m_key74;
	_STL::map<int, int>::iterator it_int = ((_STL::map<int, int> *)&m_map8c)->find(key);
	_STL::map<int, void *>::iterator it = *(_STL::map<int, void *>::iterator *)&it_int;
	if (it == m_map8c.end())
		return;
	obj->setStatus((ObjectStatusTypes)0x55, false);
	m_map8c.erase(it);
}
