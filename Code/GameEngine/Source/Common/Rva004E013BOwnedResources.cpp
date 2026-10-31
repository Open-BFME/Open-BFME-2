// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport
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
#include <vector>
// The C++-linkage game free at 0x00030830: retail's unwind state stays live across each call.
void __cdecl Rva00030830GameFree(void *);
struct Rva004DFC20Node {Rva004DFC20Node *next;};
struct Rva004DFC20Buckets {
 Rva004DFC20Node **begin,**end,**storage;
 __forceinline ~Rva004DFC20Buckets(){if(begin)Rva00030830GameFree(begin);}
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
  while(n){Rva004DFC20Node *next=n->next;Rva00030830GameFree(n);n=next;}
  buckets.begin[i]=0;
 }
 count=0;
}
Rva004DFC20::~Rva004DFC20(){clear();}
class Rva004E013BResource {public:virtual ~Rva004E013BResource();};
struct Rva004DFED8Entry4;
struct Rva004DFED8Entry10;
class Rva004DFED8
{
public:
	virtual ~Rva004DFED8();
private:
	_STL::vector<Rva004DFED8Entry4 *, _STL::allocator<Rva004DFED8Entry4 *> > m_vec4;
	_STL::vector<Rva004DFED8Entry10 *, _STL::allocator<Rva004DFED8Entry10 *> > m_vec10;
};
class Rva004DFCE1 : public Rva004DFC20 {
public: __forceinline ~Rva004DFCE1() {}
};
struct Rva004E013BBuffer {void *buffer,*finish,*storage;__forceinline ~Rva004E013BBuffer(){if(buffer)Rva00030830GameFree(buffer);}};
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

// Native 0x00791841 is the complete 11-byte table-member cleanup at +0x14.
// The exact 168-byte parent and EH graph select the rowed five-byte wrapper
// and complete 57-byte bucket-table destructor; original type identities stay unknown.
