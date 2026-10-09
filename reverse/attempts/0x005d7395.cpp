// ?rva005D7395@Rva005D736E@@QAE_NPAVObject@@@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /ICode/Libraries/Include /Ireference/shims/bfmealloc
// stlport
// Native5D7395..5D751F carries the full AISpellBookCitadel.cpp path.
// Existing AOe picker siblings supply the target acceptance ABI; native
// calls establish owner-base centre, primary-target player and ObjectID
// list, fortress flag120.4, and the perpendicular random displacement.
#include <hash_map>
namespace _STL { template<> unsigned hash_map<int,int>::bucket_count() const; }
#include "Lib/Coord3D.h"
class Player;
struct CitadelTemplateView { char unknown00[0x120]; unsigned char kinds120; };
class Object {
public:
    Player *getControllingPlayer() const;
    char unknown00[4];
    CitadelTemplateView *type4;
    char unknown08[0x30];
    Coord3D position38;
};
class Rva0025BFF8 { public: Object *rva0025BFF8(int); };
struct CitadelPlayerData { char unknown0[8]; Rva0025BFF8 *objects8; };
struct Rva002A8AB1Record { void *rva002C6ACB(); };
class Rva002A8F24 {
public:
    Rva002A8AB1Record *rva002A8AB1(void *);
    void *rva002A8F24(Player *);
};
extern Rva002A8F24 *g_00DFEEF8;
class Rva004EBF4B { public: void rva004EBF4B(Coord3D *); };
class Rva005EE816 { public: bool rva005EE8DD(const Coord3D *,Object *); };
float GetGameLogicRandomValueReal(float,float,char *,int);
class Rva005D736E { public: bool rva005D7395(Object *); };
bool Rva005D736E::rva005D7395(Object *source)
{
    Rva002A8AB1Record *owner=g_00DFEEF8->rva002A8AB1(source->getControllingPlayer());
    Coord3D own;
    reinterpret_cast<Rva004EBF4B *>(owner)->rva004EBF4B(&own);
    Player *enemy=static_cast<Player *>(owner->rva002C6ACB());
    Object *obj;
    if(enemy) {
        CitadelPlayerData *target=static_cast<CitadelPlayerData *>(g_00DFEEF8->rva002A8F24(enemy));
        Rva0025BFF8 *objects=target->objects8;
        unsigned count=reinterpret_cast<_STL::hash_map<int,int> *>(objects)->bucket_count();
        for(unsigned i=0;i<count;++i) {
            obj=objects->rva0025BFF8(i);
            if(obj->type4->kinds120&4) goto found;
        }
    }
    return false;
found:
        Coord3D enemyPosition=obj->position38;
        float fraction=GetGameLogicRandomValueReal(0.0f,1.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookCitadel.cpp",73);
        Coord3D delta;
        delta.x=enemyPosition.x-own.x;
        delta.y=enemyPosition.y-own.y;
        delta.z=enemyPosition.z-own.z;
        Coord3D location;
        location.x=own.x+delta.x*fraction;
        location.y=own.y+delta.y*fraction;
        location.z=own.z+delta.z*fraction;
        Coord3D normal;
        normal.x=0.0f;
        normal.y=0.0f;
        normal.z=GetGameLogicRandomValueReal(-1.0f,1.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookCitadel.cpp",81);
        Coord3D offset;
        offset.x=delta.y*normal.z-delta.z*normal.y;
        offset.y=delta.z*normal.x-delta.x*normal.z;
        offset.z=delta.x*normal.y-delta.y*normal.x;
        location.x+=offset.x;
        location.y+=offset.y;
        location.z+=offset.z;
        return reinterpret_cast<Rva005EE816 *>(this)->rva005EE8DD(&location,source);
}
