// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00548117@Rva00548117@@QAEPBVArmorTemplate@@PAXPBV?$list@PAVCreateAHeroData@@V?$allocator@PAVCreateAHeroData@@@_STL@@@_STL@@@Z @0x00548117 108B
// Evidence: caller 0x0035545C; list at +4 with NameKey at +8; find 0x00355155 row; virtual [edx+0x24]; contains 0x00548800 row
#include <list>

enum NameKeyType { NAMEKEY_INVALID = 0 };

class ArmorTemplate
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7();
	virtual void d8();
	virtual bool check(void *) const;
};

class Rva00355B61
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
};
extern class Rva00355B61 *g_00E01E18;

class CreateAHeroData;
typedef _STL::list<CreateAHeroData *> ListHeroPtr;
class Rva00548800
{
public:
	bool rva00548800(const ListHeroPtr *list);
};

class Rva00548117
{
	char m_pad[4];
	_STL::list<NameKeyType> m_list;
public:
	const ArmorTemplate *rva00548117(void *a1, const ListHeroPtr *a2);
};

const ArmorTemplate *Rva00548117::rva00548117(void *a1, const ListHeroPtr *a2)
{
	typedef _STL::list<NameKeyType>::_Node Node;
	Node *cur = (Node *)((Node *)m_list._M_node._M_data)->_M_next;
	while (cur != (Node *)m_list._M_node._M_data) {
		const ArmorTemplate *armor2 = 0;
		const ArmorTemplate *armor1 = g_00E01E18->rva00355155((NameKeyType)cur->_M_data);
		if (armor1 && armor1->check(a1)) {
			Node *nxt = (Node *)cur->_M_next;
			if (nxt != (Node *)m_list._M_node._M_data) {
				armor2 = g_00E01E18->rva00355155((NameKeyType)nxt->_M_data);
				if (armor2 && ((Rva00548800 *)armor2)->rva00548800(a2))
					return armor2;
			}
		}
		cur = (Node *)cur->_M_next;
	}
	return 0;
}
