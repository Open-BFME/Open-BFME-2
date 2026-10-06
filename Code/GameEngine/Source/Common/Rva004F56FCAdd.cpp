// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// ?rva004F56FC@Rva004F56FC@@QAEXPAVObject@@@Z, retail 0x004F56FC, 31 bytes.
// List-add with count: inc +0x1C then push Object+0x74 ID into list<int> at +0x08
// via rowed push_back 0x0005548F. Evidence: unlock packet; 4 callers including
// 0x0047DE30 passing Object* with manager from Player+0x2E8; same _M_create_node
// inline requirement as 0x004F5C64 so same /O1 + _STLP_NO_EXCEPTIONS + shims.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int ObjectID;

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_objectPad[0x74];
	ObjectID m_id;
};

class Rva004F56FC
{
public:
	void rva004F56FC(Object *obj);
private:
	char m_pad0[8];
	_STL::list<ObjectID> m_list;
	char m_pad1[16];
	int m_count;
};

void Rva004F56FC::rva004F56FC(Object *obj)
{
	Object *o = obj;
	++m_count;
	m_list.push_back(o->getID());
}
