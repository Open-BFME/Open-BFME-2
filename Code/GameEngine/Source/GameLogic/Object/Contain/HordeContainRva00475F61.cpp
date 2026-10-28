// cl: /Ireference/open-bfme-1/inputs/vendor /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
class FreelistPool;
extern FreelistPool g_freelistPool00DB8FEC;
// stlport
//
// HordeContain, +0x11C interface slot 126 (retail 0x00475F61, 1668 bytes, ret 4).
// Groups the contained members by equivalent template (and rank, when the module
// data's +0x24C flag is set), then walks the module data's name list at +0x1A4:
// each name's template, when it carries KindOf bit 0x6D, is created for the
// controlling player's default team, takes over a matching member group and is
// appended to the output vector; unused replacements are destroyed, and the
// horde object itself is destroyed at the end.
// Native RET4 requires an output vector; +0x60 is an ID/index map, and the
// temporary batches are vector<list<Object *> >. Both found arms index groups[i]
// directly (one compiler temporary for &groups[i]), and the +0xB8 float is read
// through an inline by-value getter, as the WorldBuilder twin shows.
// Allocation: the team is read through inline getObject() and
// Player::getDefaultTeam() accessors (Zero Hour's Player.h spelling). Their
// inline return temporaries give the team value the weight that keeps it in EBX
// across memset while the template is spilled, as retail does; the raw field
// reads keep the template in EBX instead.
// The batch lists allocate from the freelist pool at 0x00DB8FEC, retail's
// list<Object *> family at 0x001EB130..0x001EC03C. The allocator's declared
// copy constructor and destructor keep get_allocator() out of line (0x0021983A,
// called by the list copy constructor 0x004702FB); prev-first erase(iterator) is
// retail 0x0029DFC5; the vendor _algobase.h supplies the const& __copy_ptrs
// (0x00474125) that the batch vector's erase (0x004758F4) calls out of line.
template<class T> class Rva001EB984PoolAllocator;
namespace _STL {
template<class A,class B> Rva001EB984PoolAllocator<B> &__stl_alloc_rebind(Rva001EB984PoolAllocator<A> &,const B *);
template<class A,class B> Rva001EB984PoolAllocator<B> __stl_alloc_create(const Rva001EB984PoolAllocator<A> &,const B *);
}
// STLport's allocators reach the C++-linkage free (0x00030830), so container teardown may throw.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include "ascii_string.h"
#include "stlport/stl/_algobase.h"
#include <list>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
// Every use of less<int> here is inlined, yet /O1 /G7 would still emit an
// out-of-line copy that is not retail's (stlport_list_int.cpp's 0x00626F90).
// Import-inline: same inline body, no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &__x, const int &__y) const { return __x < __y; }
}
#undef free
#include <string.h>
#include "../../../Common/GameLogicObjectLookupView.h"
#include "Common/LatchRestore.h"

class ThingTemplate;
class Team;
class Player;
class Object;
class AICommandInterface;
class Rva00475F61Contain;
struct Rva0046E6EAObject;
struct Rva0046E6EACoord;
class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject *,const Rva0046E6EACoord *,Rva0046E6EACoord *,bool); };

#define COORD3D_INLINE_ASSIGN
#include "Lib/Coord3DInline.h"
class Matrix3D {
public:
    float m[3][4];
    __forceinline Matrix3D(const Matrix3D &other) {
        m[0][0]=other.m[0][0]; m[0][1]=other.m[0][1]; m[0][2]=other.m[0][2]; m[0][3]=other.m[0][3];
        m[1][0]=other.m[1][0]; m[1][1]=other.m[1][1]; m[1][2]=other.m[1][2]; m[1][3]=other.m[1][3];
        m[2][0]=other.m[2][0]; m[2][1]=other.m[2][1]; m[2][2]=other.m[2][2]; m[2][3]=other.m[2][3];
    }
};
class Thing {
public:
    const Coord3D *getUnitDirectionVector2D() const;
    void setPosition(const Coord3D *);
    void setTransformMatrix(const Matrix3D *);
    void *vtbl;
    const ThingTemplate *m_template;
    float m_transform[12];
    Coord3D m_position;
};
enum ObjectStatusTypes { OBJECT_STATUS_NONE=0 };
enum WeaponSetType { WEAPONSET_NONE=0 };
enum CommandSourceType { CMD_NONE=0 };
class AICommandInterface { public: virtual void aiCommandInterfaceAnchor(); void aiIdle(CommandSourceType); };
class Rva0028B7AELeaGetter { public: void *get() const; };
class Rva00475F61AIUpdate;
class Object : public Thing {
public:
    Player *getControllingPlayer() const;
    bool testStatus(ObjectStatusTypes) const;
    void bfmeTransferReplacementState(Object *);
    void *rva0028C197() const;
    void setWeaponSetFlag(WeaponSetType);
    char pad44[0x74-0x44];
    ObjectID m_id;
    char pad78[0xB8-0x78];
    float m_b8;
    char padBC[0x258-0xBC];
    Rva00475F61AIUpdate *m_ai;
    __forceinline ObjectID getID() const { return m_id; }
    __forceinline float getB8() const { return m_b8; }
    __forceinline const ThingTemplate *getTemplate() const { return m_template; }
    __forceinline Rva00475F61AIUpdate *getAI() const { return m_ai; }
    char pad25C[0x284-0x25C];
    unsigned int m_mask[32];
};
class ThingTemplate {
public:
    bool isEquivalentTo(const ThingTemplate *) const;
    char pad[0x115];
    unsigned char m_flags115;
};
class BfmeD975 { public: char bfmeGo975D(int); };
class Rva00475F61BaseBitset { public: void merge(const Rva00475F61BaseBitset &); };
struct Rva00475F61Result { char pad[0x2B4]; bool flag; };
struct Rva00475F61Rank { int key; char pad[0x18]; };
struct Rva00475F61Name { AsciiString name; AsciiString memberName; int key; };
struct Rva00475F61ModuleData {
    char pad[0x1A4];
    _STL::vector<Rva00475F61Name *> names;
    char pad1B0[0x24C-0x1B0];
    bool m_sameRank;
};
class Player { public: char pad[0x2EC]; Team *m_defaultTeam;
    Team *getDefaultTeam() { return m_defaultTeam; }
    const Team *getDefaultTeam() const { return m_defaultTeam; } };
struct CreateMask { unsigned int bits[4]; };
enum ObjectID; class ThingFactory { public:
    const ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *,Team *,const CreateMask *,ObjectID);
};
class Pathfinder { public: void AddObjectToPathfindMap(Object *); };
class AI { public: char pad[0x10]; Pathfinder *m_pathfinder; };
extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
typedef _STL::list<Object *> MemberList;

class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DB8FEC;
template<class T> class Rva001EB984PoolAllocator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef unsigned int size_type;
    typedef int difference_type;
    template<class U> struct rebind { typedef Rva001EB984PoolAllocator<U> other; };
    Rva001EB984PoolAllocator() {}
    template<class U> Rva001EB984PoolAllocator(const Rva001EB984PoolAllocator<U> &) {}
    Rva001EB984PoolAllocator(const Rva001EB984PoolAllocator &) {}
    ~Rva001EB984PoolAllocator() {}
    T *allocate(unsigned int, const void * = 0) { return (T *)g_freelistPool00DB8FEC.pop(); }
    void deallocate(T *p,unsigned int) { if(p) { *(void **)p=(*(void **)((char *)&::g_freelistPool00DB8FEC + 8)); (*(void **)((char *)&::g_freelistPool00DB8FEC + 8))=p; } }
    void construct(T *p,const T &v) { new(p) T(v); }
    void destroy(T *p) { p->~T(); }
    unsigned int max_size() const { return (unsigned int)-1/sizeof(T); }
};
namespace _STL {
// Convert the value allocator to the node allocator for pooled storage.
template<class T,class U> struct _Alloc_traits<T,Rva001EB984PoolAllocator<U> > {
    typedef Rva001EB984PoolAllocator<U> _Orig;
    typedef Rva001EB984PoolAllocator<T> allocator_type;
    static allocator_type create_allocator(const _Orig &a) { return allocator_type(a); }
};
template<class A,class B> inline Rva001EB984PoolAllocator<B> &__stl_alloc_rebind(Rva001EB984PoolAllocator<A> &a,const B *) {
    return (Rva001EB984PoolAllocator<B> &)a;
}
template<class A,class B> inline Rva001EB984PoolAllocator<B> __stl_alloc_create(const Rva001EB984PoolAllocator<A> &,const B *) {
    return Rva001EB984PoolAllocator<B>();
}
}
typedef _STL::list<Object *,Rva001EB984PoolAllocator<Object *> > PooledMemberList;
typedef char PoolListExtent[sizeof(PooledMemberList)==4 ? 1 : -1];
namespace _STL {
template <> PooledMemberList::iterator PooledMemberList::erase(iterator __position)
{
    _List_node_base *__prev_node = __position._M_node->_M_prev;
    _List_node_base *__next_node = __position._M_node->_M_next;
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    this->_M_node.deallocate((_List_node<Object *> *)__position._M_node, 1);
    return iterator((_List_node<Object *> *)__next_node);
}
}

class Rva00475F61AIModule {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142(int);
    char gap[0x20-4];
};
class Rva00475F61AIUpdate : public Rva00475F61AIModule, public AICommandInterface {};
class Rva00475F61Contain {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30(const PooledMemberList *);
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual Rva00475F61Result *slot134();
};
class Rva00475F61Iface {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42(Object *);
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67(MemberList *);
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void rva00475F61(_STL::vector<Object *> &out);
    char pad004[0x60-4];
    _STL::map<int,int> m_indices;
    _STL::vector<Rva00475F61Rank> m_ranks;
    char pad078[0x150-0x78];
    ObjectID m_held;
    Object *getObject() const { return *(Object **)((char *)this-0x114); }
};

namespace _STL {
template <> _List_base<Object *,allocator<Object *> >::~_List_base();
}
void Rva00475F61Iface::rva00475F61(_STL::vector<Object *> &out)
{
    out.erase(out.begin(),out.end());
    slot122();
    Object *self=getObject();
    Matrix3D transform(*(const Matrix3D *)self->m_transform);
    _STL::vector<PooledMemberList> groups;
    groups.erase(groups.begin(),groups.end());
    MemberList members;
    slot67(&members);
    Object *held=TheGameLogic->findObjectByID(m_held);
    if(held) {
        MemberList::iterator it=_STL::find(members.begin(),members.end(),held);
        if(it!=members.end()) members.erase(it);
        TheGameLogic->destroyObject(held);
    }
    Coord3D offset;
    offset=*getObject()->getUnitDirectionVector2D();
    offset.scale(getObject()->getB8()*0.5f);
    for(MemberList::iterator it=members.begin();it!=members.end();++it) {
        Object *obj=*it;
        if(obj->getAI()) obj->getAI()->slot142(0);
        bool found=false;
        for(unsigned i=0;i<groups.size();++i) {
            Object *first=groups[i].front();
            bool equal=first->getTemplate()->isEquivalentTo(obj->getTemplate());
            if(equal && (*(Rva00475F61ModuleData **)((char *)this-0x118))->m_sameRank) {
                int firstIndex=m_indices[first->getID()];
                int firstRank=m_ranks[firstIndex].key;
                int objIndex=m_indices[obj->getID()];
                int objRank=m_ranks[objIndex].key;
                if(firstRank!=objRank) equal=false;
            }
            if(equal) { groups[i].push_back(obj); found=true; break; }
        }
        if(!found) {
            PooledMemberList group;
            group.push_back(obj);
            groups.push_back(group);
        }
        slot42(obj);
    }
    _STL::vector<Rva00475F61Name *> &names=(*(Rva00475F61ModuleData **)((char *)this-0x118))->names;
    for(_STL::vector<Rva00475F61Name *>::iterator it=names.begin();it!=names.end();++it) {
        Rva00475F61Name *entry=*it;
        bool used=false;
        const ThingTemplate *tmpl=TheThingFactory->findTemplate(entry->name);
        Object *replacement=0;
        if(tmpl->m_flags115 & 0x20) {
            Team *team=getObject()->getControllingPlayer()->getDefaultTeam();
            CreateMask mask;
            memset(&mask,0,sizeof(mask));
            replacement=TheThingFactory->newObject(tmpl,team,&mask,(ObjectID)0);
        }
        if(replacement) {
            if(self->testStatus((ObjectStatusTypes)0x3E)) self->bfmeTransferReplacementState(replacement);
            Coord3D pos;
            pos=getObject()->m_position;
            pos.add(&offset);
            offset.scale(-1.0f);
            ((Rva0046E6EA *)((char *)this-0x11C))->rva0046E6EA((Rva0046E6EAObject *)replacement,
                (Rva0046E6EACoord *)&pos,(Rva0046E6EACoord *)getObject(),true);
            replacement->setPosition(&pos);
            transform.m[0][3]=pos.x;
            transform.m[1][3]=pos.y;
            transform.m[2][3]=pos.z;
        }
        bool weaponFlag=false;
        for(unsigned i=0;i<groups.size();++i) {
            Object *first=groups[i].front();
            char equal=((BfmeD975 *)first->getTemplate())->bfmeGo975D((int)&entry->memberName);
            if(equal && (*(Rva00475F61ModuleData **)((char *)this-0x118))->m_sameRank) {
                int index=m_indices[first->getID()];
                int rank=m_ranks[index].key;
                if(rank!=entry->key) equal=false;
            }
            if(equal) {
                Rva00475F61Contain *contain=replacement ? (Rva00475F61Contain *)replacement->rva0028C197() : 0;
                if(contain && replacement) {
                    Object *old=groups[i].front();
                    if(old) {
                        weaponFlag=(((unsigned char *)((const Rva0028B7AELeaGetter *)old)->get())[3]&1)!=0;
                        ((_STL::_Base_bitset<32> *)replacement->m_mask)->_M_do_or(*(const _STL::_Base_bitset<32> *)old->m_mask);
                    }
                    contain->slot30(&groups[i]);
                    used=true;
                    Rva00475F61Result *owner=contain->slot134();
                    LatchRestore<bool> restore(owner->flag,true);
                    if(weaponFlag) replacement->setWeaponSetFlag((WeaponSetType)0x18);
                } else {
                    for(PooledMemberList::iterator m=groups[i].begin();m!=groups[i].end();++m) {
                        Object *old=*m;
                        old->getAI()->aiIdle((CommandSourceType)2);
                        out.push_back(old);
                    }
                }
                break;
            }
        }
        if(used && replacement) {
            replacement->setTransformMatrix(&transform);
            replacement->getAI()->aiIdle((CommandSourceType)2);
            TheAI->m_pathfinder->AddObjectToPathfindMap(replacement);
            out.push_back(replacement);
        } else if(replacement) TheGameLogic->destroyObject(replacement);
    }
    TheGameLogic->destroyObject(getObject());
}
