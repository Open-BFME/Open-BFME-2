// ?rva00467AB8@Rva00467AB8@@QAEXPAVObject@@@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
// Clean reference transfer: BFME1 9cbfb551fe20,
// game/GameEngine/Source/GameLogic/Object/Contain/TransportContainOnRemoving.cpp.
// WB01159EA0 names TransportContain::onRemoving. Native00467AB8..00467D8E
// proves the secondary contain receiver, owner-18, data-1C, virtual calls,
// exit placement, condition bits87..89, AI state and passenger fade.
// Keep the admitted neutral binding until the complete class ABI is reconciled.
// The local one-word STLport list is a pointer-payload ABI view through the
// existing integer-list providers; its original element constness is unknown.
#include <list>
#include <bitset>
namespace _STL { template<> _List_base<int,allocator<int> >::~_List_base(); }
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
class Matrix3D;
class Player;
extern GameLogic *TheGameLogic;
extern float g_00DBA500; // Existing writable frames-per-millisecond scalar.
enum DisabledType { DISABLED_HELD=3 };
class Drawable {
public:
    int getPristineBonePositions(const char *,int,Coord3D *,Matrix3D *,int,int) const;
    void rva00274445(float);
    void fadeIn(unsigned);
};
class Thing {
public:
    void convertBonePosToWorldPos(const Coord3D *,const Matrix3D *,Coord3D *,Matrix3D *) const;
    void setPosition(const Coord3D *);
    void setOrientation(float);
    float getOrientation() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this)+0x44); }
};
class AIUpdateInterface { public: void rva0026DE3B(int); void rva00262FFF(); };
class Object {
public:
    char unknown00[0x10C]; unsigned conditions[10];
    char unknown134[0x258-0x134]; AIUpdateInterface *ai;
    bool clearDisabled(DisabledType);
    void rva0028AE6D();
    int rva0028FBBE();
    void *rva0028C197() const;
    Drawable *getDrawable() const;
    __forceinline void clearCondition(unsigned bit) {
        unsigned *words=conditions;
        if (reinterpret_cast<const unsigned char *>(words)[bit/8] & (1U<<(bit%8))) {
            words[bit/32] &= ~(1U<<(bit%32));
            rva0028AE6D();
        }
    }
};
class Rva002716Holder { public: void Rva002716D3Broadcast(int); };
class Rva0055A88BDwordField { public: int get() const; };
class Rva2225E0Filter { public: bool accepts(Object *,Player *); };
class Rva00464B96 { public: void rva00464B96(Object *); };
class OpenContain { public: virtual void onRemoving(Object *); };
template<int N> class Rva00467AB8Slots:public Rva00467AB8Slots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00467AB8Slots<0> {};
// Slot B0 returns sixteen bytes: retail462CE1 copies them through2CF108.
// WB removeFromContain witnesses the101-bit status mask and test61.
struct Rva00467AB8ModelFlags { _STL::bitset<101> bits; };
class Rva00467AB8First44:public Rva00467AB8Slots<44> {
public: virtual Rva00467AB8ModelFlags flags(Object *);
};
template<int N> class Rva00467AB8After45:public Rva00467AB8After45<N-1> { public: virtual void gap(char (*)[N+45]); };
template<> class Rva00467AB8After45<0>:public Rva00467AB8First44 {};
class Rva00467AB8First60:public Rva00467AB8After45<15> { public: virtual void refresh(); };
template<int N> class Rva00467AB8After61:public Rva00467AB8After61<N-1> { public: virtual void gap(char (*)[N+61]); };
template<> class Rva00467AB8After61<0>:public Rva00467AB8First60 {};
class Rva00467AB8Provider:public Rva00467AB8Slots<67> { public: virtual void fill(_STL::list<int> *); };
struct Rva00467AB8Data {
    char unknown00[0xAC]; unsigned exitDelay;
    const AsciiString &exitBone() const { return *reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(this)+0xA0); }
    bool orient() const { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this)+0x13F); }
    bool attitude() const { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this)+0x140); }
    bool mood() const { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this)+0x141); }
    bool fade() const { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this)+0x16D); }
    float fadeTime() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this)+0x174); }
    float drawableValue() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this)+0x17C); }
    Rva2225E0Filter *filter() const { return reinterpret_cast<Rva2225E0Filter *>(const_cast<char *>(reinterpret_cast<const char *>(this))+0x168); }
};
class Rva00467AB8:public Rva00467AB8After61<8> {
public:
    virtual int count(int) const;
    void rva00467AB8(Object *);
    Rva00467AB8Data *data() const { return *reinterpret_cast<Rva00467AB8Data *const *>(reinterpret_cast<const char *>(this)-0x1C); }
    Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x18); }
private:
    char unknown04[0xE0-4]; unsigned extraSlots; unsigned exitFrame;
};
void Rva00467AB8::rva00467AB8(Object *rider)
{
    reinterpret_cast<OpenContain *>(this)->OpenContain::onRemoving(rider);
    rider->clearDisabled(DISABLED_HELD);
    rider->clearCondition(89);
    const Rva00467AB8Data *module=data();
    Object *owner=object();
    Drawable *ownerDrawable=owner->getDrawable();
    const AsciiString &bone=module->exitBone();
    if (!reinterpret_cast<const StringBase<char> &>(bone).isEmpty()) {
        Drawable *draw=object()->getDrawable();
        if (draw) {
            Coord3D bonePosition,worldPosition;
            if (draw->getPristineBonePositions(bone.str(),0,&bonePosition,0,1,0)==1) {
                reinterpret_cast<Thing *>(object())->convertBonePosToWorldPos(&bonePosition,0,&worldPosition,0);
                reinterpret_cast<Thing *>(rider)->setPosition(&worldPosition);
            }
        }
    }
    if (module->orient()) reinterpret_cast<Thing *>(rider)->setOrientation(reinterpret_cast<Thing *>(object())->getOrientation());
    extraSlots -= rider->rva0028FBBE()-1;
    if (count(0)==0) owner->clearCondition(87);
    rider->clearCondition(88);
    AIUpdateInterface *ai=rider->ai;
    if (module->attitude() && ai) ai->rva0026DE3B(2);
    if ((reinterpret_cast<const unsigned char *>(object())[0x438]&1) && !(reinterpret_cast<const unsigned char *>(rider)[0x438]&1))
        reinterpret_cast<Rva00464B96 *>(reinterpret_cast<char *>(this)-0x20)->rva00464B96(rider);
    if (module->mood() && ai) ai->rva00262FFF();
    exitFrame=TheGameLogic->getFrame()+module->exitDelay;
    Drawable *riderDrawable=rider->getDrawable();
    if (!flags(0).bits.test(61) && ownerDrawable && riderDrawable) {
        reinterpret_cast<Rva002716Holder *>(ownerDrawable)->Rva002716D3Broadcast(reinterpret_cast<Rva0055A88BDwordField *>(riderDrawable)->get());
        riderDrawable->rva00274445(module->drawableValue());
    }
    refresh();
    if (module->fade() && riderDrawable && module->fadeTime()!=0.0f && module->filter()->accepts(rider,0)) {
        const unsigned char *templateBytes=*reinterpret_cast<const unsigned char *const *>(reinterpret_cast<const char *>(rider)+4);
        if ((templateBytes[0x115]&0x20) && rider->rva0028C197()) {
            _STL::list<int> objects;
            reinterpret_cast<Rva00467AB8Provider *>(rider->rva0028C197())->fill(&objects);
            for (_STL::list<int>::iterator it=objects.begin();it._M_node!=objects.end()._M_node;++it) {
                Object *o=reinterpret_cast<Object *>(*it);
                if (o) { Drawable *draw=o->getDrawable(); if (draw) draw->fadeIn(static_cast<unsigned>(g_00DBA500*module->fadeTime())); }
            }
        } else riderDrawable->fadeIn(static_cast<unsigned>(g_00DBA500*module->fadeTime()));
    }
}
