// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0046E8EE@HordeContain@@UAEXXZ @ 0x0046E8EE (422B).
// HordeContain slot 28 override of TransportContain slot 28: payload trim plus
// producer fixup. Evidence: vtable slot 28 of 0x00845050/0x00845C38/0x00846D28;
// early Object+0x78 producer guard; TransportContain 0x004670D6; +0x11C slot04
// false (0x10); +0x0C getContain twice plus +0x7C horde check; Rva0046247D pair
// plus ListView 0x0036AE51 list copy; (100-m_2A8)*0.01*count via __ftol2;
// destroyMember (0x34) plus GameLogic destroyObject; +0x244 module fixup;
// +0x11C finish (0x1E4). Donor: BFME1 HordeContainCreatePayload.cpp
// createPayload (100-m_damagePercent)*0.01 count destroy loop.
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}


// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef ContainmentList IntList;

struct Rva0046247DPair
{
	void *m00;
	void *m04;
};

class Rva0046247D
{
public:
	void *rva0046247D(Rva0046247DPair &p);
};


class Object;

class ModIface
{
public:
	virtual void f00();
	virtual void setOwner(int id);
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual ModIface *check();
};

struct ModElem
{
	char m_pad[0x0C];
};

class ContainIface
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
	virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
	virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
	virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
	virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
	virtual void c28(); virtual void c29(); virtual void c30();
	virtual void *c31();
};

class Iface0C
{
public:
	virtual void g00();
	virtual void g01();
	virtual ContainIface *getContain();
};

class Iface11C
{
public:
	virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
	virtual void slot04(bool v);
	virtual void h05(); virtual void h06(); virtual void h07(); virtual void h08();
	virtual void h09(); virtual void h10(); virtual void h11(); virtual void h12();
	virtual void destroyMember(Object *obj);
	virtual void g14(); virtual void g15(); virtual void g16(); virtual void g17();
	virtual void g18(); virtual void g19(); virtual void g20(); virtual void g21();
	virtual void g22(); virtual void g23(); virtual void g24(); virtual void g25();
	virtual void g26(); virtual void g27(); virtual void g28(); virtual void g29();
	virtual void g30(); virtual void g31(); virtual void g32(); virtual void g33();
	virtual void g34(); virtual void g35(); virtual void g36(); virtual void g37();
	virtual void g38(); virtual void g39(); virtual void g40(); virtual void g41();
	virtual void g42(); virtual void g43(); virtual void g44(); virtual void g45();
	virtual void g46(); virtual void g47(); virtual void g48(); virtual void g49();
	virtual void g50(); virtual void g51(); virtual void g52(); virtual void g53();
	virtual void g54(); virtual void g55(); virtual void g56(); virtual void g57();
	virtual void g58(); virtual void g59(); virtual void g60(); virtual void g61();
	virtual void g62(); virtual void g63(); virtual void g64(); virtual void g65();
	virtual void g66(); virtual void g67(); virtual void g68(); virtual void g69();
	virtual void g70(); virtual void g71(); virtual void g72(); virtual void g73();
	virtual void g74(); virtual void g75(); virtual void g76(); virtual void g77();
	virtual void g78(); virtual void g79(); virtual void g80(); virtual void g81();
	virtual void g82(); virtual void g83(); virtual void g84(); virtual void g85();
	virtual void g86(); virtual void g87(); virtual void g88(); virtual void g89();
	virtual void g90(); virtual void g91(); virtual void g92(); virtual void g93();
	virtual void g94(); virtual void g95(); virtual void g96(); virtual void g97();
	virtual void g98(); virtual void g99(); virtual void g100(); virtual void g101();
	virtual void g102(); virtual void g103(); virtual void g104(); virtual void g105();
	virtual void g106(); virtual void g107(); virtual void g108(); virtual void g109();
	virtual void g110(); virtual void g111(); virtual void g112(); virtual void g113();
	virtual void g114(); virtual void g115(); virtual void g116(); virtual void g117();
	virtual void g118(); virtual void g119(); virtual void g120();
	virtual void finish();
};

class Object
{
public:
	int getID() const { return m_74; }
	unsigned int getProducerID() const { return m_producerID; }
	void *getBodyModule() const { return m_254; }
public:
	char m_pad00[0x74];
	int m_74;
	unsigned int m_producerID;
	char m_pad7C[0x244 - 0x7C];
	void **m_244;
	char m_pad248[0x254 - 0x248];
	void *m_254;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class TransportContain
{
public:
	void createPayload();
};

class HordeContain
{
public:
	virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
	virtual void h04(); virtual void h05(); virtual void h06(); virtual void h07();
	virtual void h08(); virtual void h09(); virtual void h10(); virtual void h11();
	virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
	virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
	virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23();
	virtual void h24(); virtual void h25(); virtual void h26(); virtual void h27();
	virtual void rva0046E8EE();
private:
	char m_pad04[0x08 - 0x04];
	Object *m_object;
	char m_pad0C[0x2A8 - 0x0C];
	int m_2A8;
};

void HordeContain::rva0046E8EE()
{
	if (m_object->getProducerID())
		return;
	((TransportContain *)this)->createPayload();
	Iface11C *horde = (Iface11C *)((char *)this + 0x11C);
	horde->slot04(false);
	Iface0C *c = (Iface0C *)((char *)this + 0x0C);
	void *hordeInfo = c->getContain() ? c->getContain()->c31() : (void *)0;
	if (hordeInfo)
	{
		Rva0046247DPair p;
		IntList members = ((Rva0036AE51ListView *)((Rva0046247D *)this)->rva0046247D(p))->rva0036AE51();
		unsigned int count = members.size();
		int toDestroy = (int)(((double)(100 - m_2A8) * 0.01) * count);
		if (toDestroy < members.size() && toDestroy > 0)
		{
			IntList::iterator it = members.begin();
			while (it != members.end())
			{
				Object *member = (Object *)containmentFirstWord(*it);
				if (member->getBodyModule() && toDestroy)
				{
					horde->destroyMember(member);
					TheGameLogic->destroyObject(member);
					--toDestroy;
				}
				++it;
			}
		}
		Object *owner = m_object;
		if (owner)
		{
			void **mods = owner->m_244;
			for (; *mods; ++mods)
			{
				ModIface *mi = (ModIface *)((char *)*mods + 0x0C);
				ModIface *t = mi->check();
				if (t)
					goto found;
			}
			goto done;
found:
			for (IntList::iterator jt = members.begin(); jt != members.end(); ++jt)
			{
				Object *mem = (Object *)containmentFirstWord(*jt);
				void **m2 = mem->m_244;
				for (; *m2; ++m2)
				{
					ModIface *mi2 = (ModIface *)((char *)*m2 + 0x0C);
					ModIface *tgt = mi2->check();
					if (tgt)
						tgt->setOwner(owner->getID());
				}
			}
done:;
		}
	}
	horde->finish();
}
