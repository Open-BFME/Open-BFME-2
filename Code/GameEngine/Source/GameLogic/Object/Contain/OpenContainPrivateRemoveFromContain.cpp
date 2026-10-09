// cl: /O1 /G7 /MD /DNDEBUG /ICode/GameEngine/Source/Common
// BFME1 9cbfb551fe20 OpenContain.cpp removeFromContainViaIterator and
// BFME2's reference home supply the removal, stealth and callback semantics.
// WB01194EF0 names privateRemoveFromContain; native00462FB3..00463097 RET8
// proves the primary receiver, fields8/68, kind flag10C:2, statuses66/63,
// secondary interface20 status-mask61, layer propagation and both callbacks.
// Preserve the existing address-derived binding until class reconciliation.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum ObjectStatusTypes { OBJECT_STATUS_63=63,OBJECT_STATUS_66=66 };
enum PathfindLayerEnum { PATHFIND_LAYER_0=0 };
class Rva00373EC6;
class Object {
public:
    bool testStatus(ObjectStatusTypes) const;
    void setStatus(ObjectStatusTypes,bool);
    Rva00373EC6 *rva0028F4BC();
    int rva0028B511() const;
    void rva0028B4CE(PathfindLayerEnum);
    void rva0028FB6F(void *);
};
class StealthUpdate { public: void markAsDetected(unsigned,int,Object *,bool); };
class Rva00439E0C { public: void rva00439E0C(Object *,int,int,int); };
template<int N> class Rva00462FB3Slots:public Rva00462FB3Slots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00462FB3Slots<0> {};
struct Rva00462FB3Flags {
    unsigned words[4];
    __forceinline bool test(unsigned bit) const { return (words[bit/32]>>(bit%32))&1; }
};
class Rva00462FB3FlagsView:public Rva00462FB3Slots<44> { public: virtual Rva00462FB3Flags flags(Object *); };
class Rva00462FB3OwnerContain:public Rva00462FB3Slots<23> { public: virtual void onRemoving(Object *); };
class OpenContain:public Rva00462FB3Slots<13> {
public:
    virtual void slot13(Object *);
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
    virtual void slot22(); virtual void slot23();
    virtual void slot24(Object *,bool,bool);
    void rva00462FB3(Object *,bool);
    void *moduleData; Object *owner;
    char unknown0C[0x68-0x0C]; int count68;
};
void OpenContain::rva00462FB3(Object *rider,bool expose)
{
    if (rider->testStatus(OBJECT_STATUS_66)) owner->setStatus(OBJECT_STATUS_66,false);
    slot13(rider);
    const unsigned char *templateBytes=*reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(rider)+4);
    if (templateBytes[0x10C]&2) {
        --count68;
        if (expose) {
            Rva00373EC6 *stealth=rider->rva0028F4BC();
            if (stealth) reinterpret_cast<StealthUpdate *>(stealth)->markAsDetected(0,1,0,true);
            TheGameLogic->getManager178()->rva00439E0C(rider,0,0,1);
        }
    }
    rider->setStatus(OBJECT_STATUS_63,false);
    Rva00462FB3FlagsView *interface20=reinterpret_cast<Rva00462FB3FlagsView *>(reinterpret_cast<char *>(this)+0x20);
    if (interface20->flags(0).test(61)) slot24(rider,true,false);
    if (!(reinterpret_cast<const unsigned char *>(rider)[0x438]&1)) rider->rva0028B4CE(static_cast<PathfindLayerEnum>(owner->rva0028B511()));
    slot22();
    Rva00462FB3OwnerContain *contained=*reinterpret_cast<Rva00462FB3OwnerContain **>(reinterpret_cast<char *>(owner)+0x250);
    if (contained) contained->onRemoving(rider);
    rider->rva0028FB6F(owner);
}
