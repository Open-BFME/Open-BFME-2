// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001EC63D@Rva001EC63DNullTarget@@QAEXXZ retail 0x001EC63D..0x001EC859 540 B.
// Null-checked target of forwarder 0x001EC98E. WorldBuilder twin 0x00AF7270
// is LinearCampaign::addCarryoverStuffToMap (LinearCampaignManager.cpp) at
// match score 1.0: look the mission template up (0x001EB3A6 on +4 with +0xC)
// clear the used-unit vector at +0xB4 then take the first human player from
// ThePlayerList's mask (0x002A7D30 / getEachPlayerFromMask) with +0x5C clear;
// with TheGameLogic+0x98 cleared reset it (slot 3 on +8 / 0x002AE252 /
// 0x003805BB with +0x10 / 0x002E6A93) re-purchase the sciences at +0x14 and
// grant the 1024 carryover upgrade bits at +0x20 (status 2) then set +0xA0.
// Every carryover unit record (172 B at +0xA4) the template accepts spawns
// its +0x90 objects (0x0037DCE8; status bit 0x10 at +0x438) into a local
// object list; spawned records move to +0xB4 and are erased (0x001EBCD8).
// The list goes to the army placer (0x0037F4C0 / 0x0037FE3D / 0x0037F4C9).
// Native fields/calls establish layout and behavior. WB AF7270 supplies a
// LinearCampaign carryover semantic lead; the owner keeps its existing
// address-derived identity because the original class is not proved.
// Reuse the verified DB8FEC Object-list policy from ArmySummaryLoad. The
// generic Object-list cleanup4EC395 differs from pooled cleanup1EB769.
// A nonemitting barrier in the first receiver expression preserves native
// argument/receiver-load ordering and saved-register scheduling.

class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva001EC63DGameLogic { char pad00[0x98]; bool m_98; };

class Object;
struct Rva001EC63DObjectView { char pad000[0x438]; unsigned char m_statusBits; };

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>
#include <vector>
class Rva001EB984Member { public: void *init(void *context); };
class Rva001EB769 { public: void rva001EB769() throw(); };
template<class T>class Rva001EB984PoolAllocator {};
class FreelistProxyHead {public:void setup(const void*,void*);};
class FreelistPool {public:void*pop();};
extern FreelistPool g_freelistPool00DB8FEC;
// The visible constructor preserves the native unused-allocator argument
// placement. Its /Oy- COMDAT copy loses to the exact strong /O1 provider
// in StlportObjectFreelistListBaseCtor.cpp; no alternate body is called.
namespace _STL {
template<class T,class A>class _List_base;
template<>class _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:
 _List_base(const Rva001EB984PoolAllocator<Object*>&);
 __forceinline ~_List_base() throw(){((Rva001EB769*)this)->rva001EB769();}
 void*head;
};
__declspec(noinline) inline _List_base<Object*,Rva001EB984PoolAllocator<Object*> >::_List_base(const Rva001EB984PoolAllocator<Object*>&a)
{
 char dummy;((FreelistProxyHead*)this)->setup(&dummy,0);
 void*n=g_freelistPool00DB8FEC.pop();((void**)n)[0]=n;((void**)n)[1]=n;head=n;
}

// The existing circular-header policy owns native Object node allocation.
// Keep stock append visible here: native inlines it through insert37B.
template<>class list<Object*,Rva001EB984PoolAllocator<Object*> > : public _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:
 list(const Rva001EB984PoolAllocator<Object*>&a=Rva001EB984PoolAllocator<Object*>()):_List_base<Object*,Rva001EB984PoolAllocator<Object*> >(a){}
 __forceinline void push_back(Object*const&v){((list<Object*,allocator<Object*> >*)this)->push_back(v);}
 bool empty()const{return *(void**)head==head;}
};
}

typedef _STL::list<Object*,Rva001EB984PoolAllocator<Object*> > CarryoverObjectList;


class Rva003805BB
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	bool rva003805BB(float value, bool flag);
	void rva002E6A93(int value);
};

enum ScienceType { SCIENCE_INVALID = -1 };
class UpgradeTemplate;
class Upgrade;
enum UpgradeStatusType { UPGRADE_STATUS_2 = 2 };

class Player
{
public:
	void rva002AE252();
	bool forcePurchaseScience(ScienceType science);
	Upgrade *rva002AE329(const UpgradeTemplate *tmpl, UpgradeStatusType status, int flag);
	void rva002A9E25(float value);
	char pad00[8];
	Rva003805BB m_08;
	char pad0C[0x1c - 0xc];
	int m_1C;
	char pad20[0x5c - 0x20];
	int m_5C;
};

class PlayerList
{
public:
	int rva002A7D30();
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class UpgradeCenter { public: const UpgradeTemplate *rva0026EEA0(int key) const; };
extern UpgradeCenter *TheUpgradeCenter;

class CarryoverUnit
{
public:
	Object *createSingleObject(Player *player);
	char pad00[0x90];
	int m_quantity;
	char pad94[0xac - 0x94];
};

struct BfmeAssignRecord36;
struct BfmeAssignRecord172 { int a[43]; };
struct BfmePod172 { int a[43]; };
struct Rva001EB8A4Elem;
class Rva001EB8A4 { public: bool rva001EB8A4(const Rva001EB8A4Elem &e); };
class Rva001EB3A6 { public: BfmeAssignRecord36 *rva001EB3A6(int index); };
class Rva001EBCD8 { public: void *rva001EBCD8(void *record); };

class Rva0037F57E
{
public:
	Rva0037F57E();
	virtual ~Rva0037F57E();
};
struct Rva0037FE3DList;
class Rva0037FE3D { public: void rva0037FE3D(const Rva0037FE3DList &list, int value); };

class Rva001EC63DNullTarget
{
public:
	void rva001EC63D();

	char pad00[4];
	Rva001EB3A6 *m_missions;
	char pad08[4];
	int m_missionIndex;
	float m_10;
	ScienceType *m_sciencesBegin;
	ScienceType *m_sciencesEnd;
	char pad1C[4];
	unsigned int m_upgrades[32];
	float m_A0;
	CarryoverUnit *m_unitsBegin;
	CarryoverUnit *m_unitsEnd;
	char padAC[0xb4 - 0xac];
	_STL::vector<BfmeAssignRecord172> m_used;
};

void Rva001EC63DNullTarget::rva001EC63D()
{
	BfmeAssignRecord36 *mission = (_ReadWriteBarrier(),m_missions)->rva001EB3A6(m_missionIndex);
	if (mission) {
		m_used.clear();
		if (ThePlayerList) {
			Player *player = 0;
			int mask = ThePlayerList->rva002A7D30();
			while (!player && mask) {
				Player *p = ThePlayerList->getEachPlayerFromMask(mask);
				if (p && p->m_5C == 0)
					player = p;
			}
			if (player) {
				{
				bool *flag = &reinterpret_cast<Rva001EC63DGameLogic *>(TheGameLogic)->m_98;
				bool saved = *flag;
				*flag = false;

				player->m_08.slot3();
				player->rva002AE252();
				player->m_08.rva003805BB(m_10, false);
				player->m_08.rva002E6A93(player->m_1C);

				ScienceType *end = m_sciencesEnd;
				for (ScienceType *it = m_sciencesBegin; it != end; ++it)
					player->forcePurchaseScience(*it);

				for (int i = 0; i < 1024; ++i) {
					if (m_upgrades[(unsigned int)i >> 5] & (1 << (i & 0x1f))) {
						const UpgradeTemplate *tmpl = TheUpgradeCenter->rva0026EEA0(i);
						if (tmpl)
							player->rva002AE329(tmpl, UPGRADE_STATUS_2, 1);
					}
				}
				player->rva002A9E25(m_A0);

				reinterpret_cast<Rva001EC63DGameLogic *>(TheGameLogic)->m_98 = saved;
				}

				CarryoverObjectList objects;
				CarryoverUnit *unit = m_unitsBegin;
				while (unit != m_unitsEnd) {
					bool added = false;
					bool missing = !reinterpret_cast<Rva001EB8A4 *>(mission)->rva001EB8A4(
						*reinterpret_cast<const Rva001EB8A4Elem *>(unit));
					if (missing) {
						for (int n = unit->m_quantity; n > 0; --n) {
							Object *obj = unit->createSingleObject(player);
							if (obj) {
								reinterpret_cast<Rva001EC63DObjectView *>(obj)->m_statusBits |= 0x10;
								objects.push_back(obj);
								added = true;
							}
						}
					}
					if (added) {
						reinterpret_cast<_STL::vector<BfmePod172> *>(&m_used)->push_back(
							*reinterpret_cast<const BfmePod172 *>(unit));
						unit = static_cast<CarryoverUnit *>(
							reinterpret_cast<Rva001EBCD8 *>(&m_unitsBegin)->rva001EBCD8(unit));
					} else {
						++unit;
					}
				}

				Rva0037F57E placer;
				reinterpret_cast<Rva0037FE3D *>(&placer)->rva0037FE3D(
					*reinterpret_cast<const Rva0037FE3DList *>(&objects), (int)player);
			}
		}
	}
}
