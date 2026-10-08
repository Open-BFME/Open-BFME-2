// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native598052..5980F3 is161B, RET0; WB152E690 has the same seven calls.
// The independently rowed AIUnitBuilder598D7A tail-calls this body with
// this unchanged, establishing the receiver. The original method name
// remains unknown. Retail proves owner30/playerId3AC and metadata78,
// state2C/id1C; their wider layouts and original identities are unresolved.
// Traverses the current battle's nested collection and forwards ids whose
// metadata word2C is3. Mode114 suppresses traversal when it is3.
// The canonical GameLogic view and existing named living-world singleton
// preserve their providers; no new globals, pins or aliases are introduced.
#include <list>
struct Rva00598052Owner {char unknown00[0x3AC];int playerId;};
class Rva002E2903Player;
class Rva002BA8F1Logic {public: Rva002E2903Player *find(int,unsigned int *);};
class Rva003F468D;
class Rva0020E6B7RegionManager {public: Rva003F468D *rva0020E6B7();};
class LivingWorldLogic {public: char unknown00[0xB0]; Rva0020E6B7RegionManager *manager;};
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class LivingWorldBattle {
public:
    int rva003F4752(void *);
    int rva003F4FAA(int,void *);
    int rva003F48FE(int,int,int);
};
class Rva003F4DCA {public: int rva003F4DCA(int,int);};
struct Rva00598052Metadata {char unknown00[0x1C];int id;char unknown20[12];int state;};
struct Rva00598052Entry {char unknown00[0x78]; Rva00598052Metadata *metadata;};

class Rva00598C3AItem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6(int value, int flags);
};

class AIUnitBuilder
{
public:
	void Rva00598A3D();
	void Rva00598961();
	void build();
	void Rva00598052();
	void Rva00598D7A();
	Rva00598C3AItem *createBestHeroToBuild();
	Rva00598C3AItem *createBestUnitToMake();

private:
	unsigned char m_pad00[0x14];
	_STL::list<Rva00598C3AItem *> m_items; // +0x14
	unsigned char m_pad18[0x2C - 0x18];
	bool m_2C; // +0x2C, read and cleared by target bytes
	unsigned char m_pad2D[0x30 - 0x2D];
	Rva00598052Owner *m_30; // +0x30
	bool m_34; // +0x34
};

void AIUnitBuilder::Rva00598052()
{
    if (TheGameLogic->m_114 != 3) {
        int playerId=m_30->playerId;
        Rva002E2903Player *player=((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId,0);
        LivingWorldBattle *battle=(LivingWorldBattle *)TheLivingWorldLogic->manager->rva0020E6B7();
        int outer=battle->rva003F4752(player);
        int middle=battle->rva003F4FAA(outer,player);
        int count=((Rva003F4DCA *)battle)->rva003F4DCA(outer,middle);
        for (int i=0;i<count;++i) {
            Rva00598052Metadata *metadata=((Rva00598052Entry *)battle->rva003F48FE(outer,middle,i))->metadata;
            if(metadata->state==3)
                TheGameLogic->rva0023D08B(metadata->id);
        }
    }
}

// Native598D7A..598DA2: flag2C update, build, then tail to598052.
void AIUnitBuilder::Rva00598D7A()
{
	if (m_2C)
	{
		Rva00598A3D();
		m_2C = false;
	}
	Rva00598961();
	build();
	return Rva00598052();
}
