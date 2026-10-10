// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Target facts: complete57B4DFC20..4DFC59 destructor and complete168B
// 4E013B..4E01E3 holder destructor. Native member cleanup receiver+14 calls
// 4DFC20; its EH state protects bucket storage at+4 while clear1DBCDC runs.
// The clear is STLport4.5.3 hashtable::clear's semantic/structural lead,
// independently measured as bucket pointers+4/+8 and count+10, linked
// next pointer+0, with no payload destructor. Payload type is unknown;
// the prior ArmorTemplate object-symbol alias established only byte equality.
// Holder resources0/4/8/C use global-qualified virtual deletion; concrete
// child+10 invokes the owned4DFED8 destructor directly before global delete.
// Hash-prefix20B at14 has a wrapper destructor4DFCE1 witnessed by EH;
// opaque word28 precedes a12B pointer header2C whose EH cleanup calls7FAB3.
// Word28 ownership and the original wrapper relationship remain uncertain.
// Original holder, table, resource and buffer class identities are unresolved.
namespace _STL { void __cdecl free(void*); }
struct Rva004DFC20Node {Rva004DFC20Node *next;};
struct Rva004DFC20Buckets {
 Rva004DFC20Node **begin,**end,**storage;
 __forceinline ~Rva004DFC20Buckets(){if(begin)_STL::free(begin);}
};
class Rva004DFC20 {
 unsigned unknown00; Rva004DFC20Buckets buckets; unsigned count;
public:
 ~Rva004DFC20();
 void clear();
};
void Rva004DFC20::clear() {
 for(unsigned i=0;i<(unsigned)(buckets.end-buckets.begin);++i){
  Rva004DFC20Node *n=buckets.begin[i];
  while(n){Rva004DFC20Node *next=n->next;_STL::free(n);n=next;}
  buckets.begin[i]=0;
 }
 count=0;
}
Rva004DFC20::~Rva004DFC20(){clear();}
class Rva004E013BResource {public:virtual ~Rva004E013BResource();};
class Rva004DFED8 {public:virtual ~Rva004DFED8();};
class Rva004DFCE1 : public Rva004DFC20 {
public: __forceinline ~Rva004DFCE1() {}
};
struct Rva004E013BBuffer {void *buffer,*finish,*storage;__forceinline ~Rva004E013BBuffer(){if(buffer)_STL::free(buffer);}};
class Rva004E013B {
 Rva004E013BResource *p0,*p4,*p8,*pC;
 Rva004DFED8 *p10;
 Rva004DFCE1 table;
 unsigned unknown28;
 Rva004E013BBuffer buffer;
public:
    ~Rva004E013B();
};
Rva004E013B::~Rva004E013B(){
    if (p0) ::delete p0;
    if (p4) ::delete p4;
    if (p8) ::delete p8;
    if (pC) ::delete pC;
    Rva004DFED8 *child = p10;
    if (child) {
        child->Rva004DFED8::~Rva004DFED8();
        ::operator delete(child);
    }
}
