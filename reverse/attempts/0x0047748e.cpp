// ?rva0047748E@HordeTransportContain@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
typedef _STL::list<int> IntList;
namespace _STL {template<> _List_base<int,allocator<int> >::~_List_base();}
class Rva0036AE51ListView { public:void *a,*b;IntList rva0036AE51(); };
struct Rva0046247DPair {void *a; IntList *objects;};
class Rva0046247D {public:void rva0046247D(Rva0046247DPair &);};
class Rva0047A040Base9E0 {public:void *rva00588B8A(void *);};
class Rva00270260 {public:bool rva00270260();};
class Rva002716Holder {public:void rva00271601(unsigned char);};
enum DamageType { DeathDamage=8 }; enum DeathType { NormalDeath=0 };
class Drawable;
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
class HordeTransportContain {public:
    virtual void x00()=0;virtual void x01()=0;virtual void x02()=0;virtual void x03()=0;
    virtual void x04()=0;virtual void x05()=0;virtual void x06()=0;virtual void x07()=0;
    virtual void x08()=0;virtual void x09()=0;virtual void x10()=0;virtual void x11()=0;
    virtual void x12()=0;virtual void x13()=0;virtual void x14()=0;
    virtual void x3C(RiderContain *,Object *)=0;
    void rva004779F9(); void rva0047748E();
};
void HordeTransportContain::rva004779F9()
{
    Rva0046247DPair outer;
    ((Rva0046247D*)this)->rva0046247D(outer);
    for (IntList::iterator i=outer.objects->begin();i!=outer.objects->end();++i) {
        RiderContain *contain=(RiderContain*)((Rva0047A040Base9E0*)((char*)this+0x11D))->rva00588B8A((void*)*i);
        if (!contain) continue;
        IntList nested=contain->s108().rva0036AE51();
        for(IntList::iterator j=nested.begin();j!=nested.end();++j) {
            Object *object=(Object*)*j;
            Drawable *drawable=object->getDrawable();
            if(!drawable || ((Rva00270260*)drawable)->rva00270260()) {
                contain->sA8(object);
                ((RemovalNotice*)((char*)this+0x20))->sA4(object,0);
                object->kill(DeathDamage,NormalDeath);
                if(drawable) ((Rva002716Holder*)drawable)->rva00271601(1);
            }
        }
    }
}

void HordeTransportContain::rva0047748E()
{
    Rva0046247DPair outer;
    ((Rva0046247D*)this)->rva0046247D(outer);
    for(IntList::iterator i=outer.objects->begin();i!=outer.objects->end();++i) {
        RiderContain *contain=(RiderContain*)((Rva0047A040Base9E0*)((char*)this+0x11D))->rva00588B8A((void*)*i);
        if(!contain)continue;
        Rva0036AE51ListView nested=contain->s108();
        IntList *objects=(IntList*)nested.b;
        if(objects->empty()) continue;
        Object *object=(Object*)*objects->begin();
        Drawable *drawable=object->getDrawable();
        if(drawable && !((Rva00270260*)drawable)->rva00270260())
        {
            nested.a=0;
            x3C(contain,object);
        }
    }
}
