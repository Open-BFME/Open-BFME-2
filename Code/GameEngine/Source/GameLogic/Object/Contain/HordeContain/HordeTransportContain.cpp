// BFME1 ba7ddda7 Rva0024CAE0MaintainNestedRiders.cpp supplies the nested
// rider-maintenance algorithm. BFME2's update at477AF3 calls4779F9 first;
// its ctor and interface wrappers establish the primary receiver, +11D
// helper, and +20 removal-notification view. Native body4779F9..477AF3
// establishes list-descriptor slot108, removal slotsA8/A4, and owned
// Object::kill/GetDrawable calls. The original method name is unresolved.
// Both lists use the shared four-byte opaque element whose insertion chain
// is independently recovered. Declared virtual slots are ABI views only;
// this unit creates no interface objects or invented vtable data.
// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>
extern "C" void *__cdecl memcpy(void *,const void *,unsigned int);
#pragma intrinsic(memcpy)
#include "../../../../../Include/GameLogic/ContainmentListView.h"
typedef ContainmentList IntList;
// Local comparison keeps this consumer from emitting a competing iterator.
namespace _STL {
template<class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>&a,const _List_iterator<T, Traits>&b)
{ return a._M_node != b._M_node; }
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

struct Rva0046247DPair {void *a; IntList *objects;};
class Rva0046247D {public:void rva0046247D(Rva0046247DPair &);};
class Rva0047A040Base9E0 {public:void *rva00588B8A(void *);};
class Rva00270260 {public:bool rva00270260();};
enum DamageType { DeathDamage=8 }; enum DeathType { NormalDeath=0 };
class Drawable {public:void setDrawableHidden(bool hidden);};
class Object {public:Drawable *getDrawable() const;void kill(DamageType,DeathType);};
#define V(n) virtual void s##n()=0;
class RiderContain {public:
V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41)
virtual void sA8(Object *)=0;
V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52)
V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65)
virtual Rva0036AE51ListView s108()=0;
};
class RemovalNotice {public:
V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40)
virtual void sA4(Object *,int)=0;
};
#undef V
class Thing;
struct Rva0047727EObjectPositionView;
class HordeTransportContain {
public:
    void rva004779F9();
    void rva004776E7(const struct Rva004776E7UpgradeMask *,bool);
    void rva0047727E(Thing *object);
private:
    unsigned char prefix00[8];
    Rva0047727EObjectPositionView *m_object;
};
void HordeTransportContain::rva004779F9()
{
    Rva0046247DPair outer;
    ((Rva0046247D*)this)->rva0046247D(outer);
    for (IntList::iterator i=outer.objects->begin();i!=outer.objects->end();++i) {
        void *outerObject;
        memcpy(&outerObject,&*i,4);
        RiderContain *contain=(RiderContain*)((Rva0047A040Base9E0*)((char*)this+0x11D))->rva00588B8A(outerObject);
        if (!contain) continue;
        IntList nested=contain->s108().rva0036AE51();
        for(IntList::iterator j=nested.begin();j!=nested.end();++j) {
            Object *object;
            memcpy(&object,&*j,4);
            Drawable *drawable=object->getDrawable();
            if(!drawable || ((Rva00270260*)drawable)->rva00270260()) {
                contain->sA8(object);
                ((RemovalNotice*)((char*)this+0x20))->sA4(object,0);
                object->kill(DeathDamage,NormalDeath);
                if(drawable) drawable->setDrawableHidden(true);
            }
        }
    }
}

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
class Thing { public: void setPosition(const Coord3D *position); };

// Whole clean BF1 f98983a7 Object/Contain/HordeContainExitPosition.cpp
// supplies the copy-and-extract pattern. Native47727E..4772B8 is complete
// RET4, called at477572 by this subsystem's update. It reads receiver+8,
// then the float words at pointee14/24/34, and calls genuine Thing::setPosition
// at30AA80. WB11A00E0 independently carries the same transform-translation
// extraction and named callee. Original helper name and complete object and
// matrix layouts remain unknown; these views model only accessed prefixes.
// The explicit copy preserves the independently observed out-of-line-call
// preparation, including the temporary source-subobject address calculation.
struct Rva0047727ETransformView {
    unsigned char prefix00[12];
    float x;
    unsigned char gap10[12];
    float y;
    unsigned char gap20[12];
    float z;
    __forceinline Rva0047727ETransformView(const Rva0047727ETransformView &other)
        : x(other.x), y(other.y), z(other.z) {}
    __forceinline void getTranslation(Coord3D *position) const {
        position->x=x;
        position->y=y;
        position->z=z;
    }
};
struct Rva0047727EObjectPositionView {
    unsigned char prefix00[8];
    Rva0047727ETransformView transform;
};
void HordeTransportContain::rva0047727E(Thing *object) {
    Coord3D position;
    Rva0047727ETransformView transform(m_object->transform);
    transform.getTranslation(&position);
    object->setPosition(&position);
}

// Native4776E7..47778B RET8, +20-interface slot174 in the independently
// identified HordeTransportContain table. The 1024-bit mask is scanned in
// index order; the owned UpgradeCenter accessor26EEA0 supplies pointers for
// callback4772D1, whose body tests/applies each UpgradeTemplate to an Object.
// Interface-relative slot110 visits Objects with this temporary range.
// This entry receives the +20 interface pointer, and accesses no primary
// fields; its CallView explicitly models that entry receiver, not the primary
// layout used by the other methods above.
// These offsets, iteration limit, callbacks and unwind state are target facts.
// The original method/mask/visitor names and the unused boolean's purpose
// remain unresolved. ModuleData is the existing library instantiation's
// spelling at211E58/4DFCB0, not a claim that these are ModuleData objects:
// only opaque pointers are stored, and callback4772D1 interprets the range.
// EHs and non-imported CRT free reproduce the native cleanup state/direct
// call; the adjacent bodies remain verified with those shared settings.
class ModuleData; class UpgradeTemplate;
class UpgradeCenter { public: const UpgradeTemplate *rva0026EEA0(int index) const; };
extern UpgradeCenter *TheUpgradeCenter;
struct Rva004772D1RangePrefix;
void rva004772D1(Object *,const Rva004772D1RangePrefix &);
struct Rva004776E7UpgradeMask { unsigned int bits[32]; __forceinline bool test(unsigned int i) const { return (bits[i>>5] & (1u<<(i&31)))!=0; } };
template<int N> class Rva004776E7Slots : public Rva004776E7Slots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class Rva004776E7Slots<0> {};
typedef void (__cdecl *Rva004776E7Callback)(Object *,void *);
class Rva004776E7CallView : public Rva004776E7Slots<68> { public: virtual void iterate(Rva004776E7Callback,void *,int)=0; };
namespace _STL { template<> void vector<const ModuleData *>::push_back(const ModuleData *const &); }
void HordeTransportContain::rva004776E7(const Rva004776E7UpgradeMask *mask,bool)
{
    _STL::vector<const ModuleData *> upgrades;
    for(int i=0;i<1024;++i)
    {
        if(mask->test(i))
        {
            const ModuleData *value=(const ModuleData *)TheUpgradeCenter->rva0026EEA0(i);
            upgrades.push_back(value);
        }
    }
    ((Rva004776E7CallView *)this)->iterate((Rva004776E7Callback)&rva004772D1,&upgrades,1);
    ((_STL::vector<void *> *)&upgrades)->clear();
}
