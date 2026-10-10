// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00423A68@Rva00423A68@@QAEXPBVModuleData@@@Z retail 0x00423A68 13B
// Thin push_back forwarder over a vector<ModuleData*> at +0: lea the stack
// arg and tail-call the rowed push_back at 0x004DFCB0. Evidence: 3 callers
// plus STLport neighbours with same bfmealloc flags.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData;

class Rva00423A68
{
public:
	void rva00423A68(const ModuleData *p);
private:
	_STL::vector<const ModuleData *> m_vec;
};

void Rva00423A68::rva00423A68(const ModuleData *p)
{
	m_vec.push_back(p);
}

// ?getValidObjectList@FormationAssistant@@QAE_NPAVRva001EB130Holder@@PAVPlayer@@0@Z
// retail 0x00423A75, 119 bytes.
#include <list>

class Object;
class Player;
class BfmeTab1026;
class Rva001EB130Holder;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
};

// 0x00362437 is rowed as Rva2225E0Filter::accepts(Object *, Player *); the old
// ?bfmeHas1026@BfmeTab1026@@QAEDHH@Z pin names the same body.
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
class BfmeTab1026 : public Rva2225E0Filter
{
public:
};

class Rva001EB130Holder
{
public:
	void rva001EB130();
	void *m_head;
};

struct RvaListNode
{
	RvaListNode *m_next;
	RvaListNode *m_prev;
	Object *m_obj;
};

class FormationAssistant
{
public:
	bool getValidObjectList(Rva001EB130Holder *input, Player *player, Rva001EB130Holder *output);
private:
	char m_pad[0x20];
	BfmeTab1026 m_tab;
};

bool FormationAssistant::getValidObjectList(Rva001EB130Holder *input, Player *player, Rva001EB130Holder *output)
{
	output->rva001EB130();
	if (!player)
		return false;
	RvaListNode *sentinel = (RvaListNode *)input->m_head;
	RvaListNode *cur = sentinel->m_next;
	if (cur == sentinel)
		goto empty;
	{
		RvaListNode *head = sentinel;
		do {
			Object *obj = cur->m_obj;
			Object *slot = obj;
			if (slot) {
				if (slot->getControllingPlayer() == player) {
					if (m_tab.accepts(slot, player)) {
						((_STL::list<Object *> *)output)->push_back(slot);
					}
				}
			}
			cur = cur->m_next;
		} while (cur != (RvaListNode *)input->m_head);
	}
empty:
	{
		RvaListNode *outSent = (RvaListNode *)output->m_head;
		return outSent->m_next != outSent;
	}
}
