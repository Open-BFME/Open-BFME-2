// ?SpawnOneDelayedCarryoverUnit@ArmySummary@@QAE?AW4ObjectID@@PAVRva00376A62@@@Z
// partial score=0.94 date=2026-10-08
// WorldBuilder 0x010893B0 names ArmySummary::RemoveEntry at ArmySummary.cpp:573.
// Native Ghidra boundary 0x0040DD3A / 156 B and calls prove the listener list
// at +4, 8-byte key/reference entries in the vector at +0x40, and returned
// 4-byte reference handle. Its target's count is +0xB0 and release base +0xAC.
// Target identity and the original handle template spelling remain unproven;
// use the same address-derived target view as the established entry destructor.
// Native listener member pointers are the compiler's virtual-slot 4 / 3 thunks.
// The output retains the target before the local handle releases it; erase
// uses the independently verified Rva004F69C3 vector provider at 0x0040DC1F.
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG
// stlport
#include <vector>
struct TargetRef00217D4C { void* vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva004F69C3Target { unsigned char opaque[0xAC]; TargetRef00217D4C ref; };
struct Rva004F69C3 { int key; Rva004F69C3Target* value; ~Rva004F69C3(); };
namespace _STL { template<> vector<Rva004F69C3>::iterator vector<Rva004F69C3>::erase(iterator); }
class Rva0040D8D6Listener {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void removed(void*,int); virtual void removing(void*,int);
};
class Rva0040D8D6List {
public: void forEach(void(Rva0040D8D6Listener::*)(void*,int),void*,int);
private: unsigned char opaque[0x10];
};
struct Rva0040DD3ARef {
 Rva004F69C3Target* value;
 Rva0040DD3ARef():value(0){}
 Rva0040DD3ARef(Rva004F69C3Target* p):value(p){if(value)++value->ref.references;}
 Rva0040DD3ARef(const Rva0040DD3ARef& x):value(x.value){if(value)++value->ref.references;}
 ~Rva0040DD3ARef(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
template<class T> class StringBase { public: void* buffer; };
class Rva00376A62 {
public: bool rva00376A62(const StringBase<char>&);
    unsigned char opaque[8]; _STL::vector<StringBase<char> > types;
};
struct SpawnTargetView { unsigned char opaque[4]; StringBase<char> name; unsigned char gap[0x90-8]; int count; };
struct ArmySummaryEntryRef { Rva0040DD3ARef holder; };
class Rva001EB984Member { public: void* init(void*); };
class Rva001EB769 { public: void rva001EB769() throw(); };
class Object { public: unsigned char opaque[0x74]; unsigned id; };
struct OutputNode { OutputNode* next; OutputNode* prev; Object* value; };
namespace _STL {
template<class T,class A=allocator<T> > class list {
public:
    OutputNode* head;
    list() { allocator<T> alloc; reinterpret_cast<Rva001EB984Member*>(this)->init(&alloc); }
    ~list() { reinterpret_cast<Rva001EB769*>(this)->rva001EB769(); }
};
}
class Rva0040C495;
struct Rva0040E534Input { Rva0040C495* value; };
enum ObjectID { INVALID_ID=0 };
namespace _STL { template<> vector<ObjectID>::iterator vector<ObjectID>::erase(iterator); }
class ArmySummary {
public: Rva0040DD3ARef RemoveEntry(int);
    ArmySummaryEntryRef GetEntry(int);
    void LoadArmyEntry(Rva0040E534Input*,int,_STL::list<Object*>*,int);
    ObjectID SpawnOneDelayedCarryoverUnit(Rva00376A62*);
private: unsigned char unknown0[4]; Rva0040D8D6List listeners; unsigned char gap[0x40-0x14]; _STL::vector<Rva004F69C3> entries; _STL::vector<ObjectID> pending;
};
Rva0040DD3ARef ArmySummary::RemoveEntry(int index) {
 Rva004F69C3* entry=entries.begin()+index;
 listeners.forEach(&Rva0040D8D6Listener::removing,this,entry->key);
 Rva0040DD3ARef value(entry->value);
 entries.erase(entry);
 listeners.forEach(&Rva0040D8D6Listener::removed,this,(int)value.value);
 return value;
}

ObjectID ArmySummary::SpawnOneDelayedCarryoverUnit(Rva00376A62* filter) {
    if (filter->types.size()==0) return INVALID_ID;
    const _STL::vector<ObjectID>::iterator last=pending.end();
    for (_STL::vector<ObjectID>::iterator i=pending.begin(); i!=last;) {
        ArmySummaryEntryRef value=GetEntry((int)*i);
        Rva004F69C3Target* held=value.holder.value;
        if (held && filter->rva00376A62(reinterpret_cast<SpawnTargetView*>(held)->name)) {
            pending.erase(i);
            ObjectID result=INVALID_ID;
            _STL::list<Object*> spawned;
            LoadArmyEntry(reinterpret_cast<Rva0040E534Input*>(&value),reinterpret_cast<SpawnTargetView*>(held)->count,&spawned,0);
            if (spawned.head->next!=spawned.head && spawned.head->next->value)
                result=(ObjectID)spawned.head->next->value->id;
            return result;
        }
        ++i;
    }
    return INVALID_ID;
}
