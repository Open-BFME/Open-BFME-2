// ?appendPayloadRva003F6DF9@Rva003F6D35Owner@@QAEXPAXPAURva003F6DF9Payload@@@Z
// partial score=0.75 date=2026-10-05
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// BANKED NONMATCHING reconstruction of Ghidra [3F6DF9,3F6EA1),168B.
// Current /O1 /G7 body172B; typed const pointers163B; typed local170B.
// Target instructions prove payload78 data pointer; data2C reset;
// pointer vector4 and104B vector10 in the48B inner; entry-vector40/44
// stride8; returned child98 word andA8 byte cleared; listener registration
// consumes a null-preserving owner+4 adjustment. Original type identities
// are unknown. The two-base owner is a structural inference modeling that
// adjustment; no original vtable or inheritance identity is asserted.
// STLport supplies vector/search semantics; target instructions supply the
// offsets and behavior. Full196B lookup3F6D35 is recovered and stays exact
// under this trial layout. Full providers27Bfind20E873;49Bpush4DFCB0;
// 55Bpush3B9369;14Bget40CB2C;22Bappend5A0B4C are rowed and verified.
// Remaining wall: compiler caches the finish pointer across find and
// schedules pointer conversions/loop index differently. Native reloads
// finish after find and reuses dead input-argument storage for temporaries
// and the loop index. No speculative pins or Code changes were retained.
// Original provider ModuleData/CreateAHeroData spellings are ABI links
// rather than target application-name claims at this caller.
// stlport
// Target Ghidra [3F6D35,3F6DF9),196B; thiscall RET4 returning an inner.
// Target finds an outer by input using full70B3F4752; missing (-1) creates
// a temporary28B record with full124B3F64B2 and pushes it at owner18.
// It then finds an inner via full19B3F4FAA; missing creates and appends a
// temporary48B element. Native reserve constants are2 and6. Return is
// the selected inner address; target arithmetic proves strides28/48.
// The record28/48 fields and owner18 vector are structural target facts;
// original application/input identities and unused fields remain unproved.
// Clean STLport vector accessors preserve the target base-load ordering;
// a flat pointer emitter folded that load and was194B. All full providers
// below are independently rowed and verified; aliases only bind consumed
// ABIs and do not claim original names. Input address bits are preserved
// by the inner provider's established four-byte constructor argument.
#include <vector>
struct Rva003F6DF9Child {char pad98[0x98];unsigned field98;char pad9c[0xc];bool flaga8;};
struct Rva003F6DF9Entry {unsigned word;Rva003F6DF9Child *child;};
struct Rva003F6DF9Data {char pad2c[0x2c];unsigned dirty;char pad30[0x10];_STL::vector<Rva003F6DF9Entry> entries;char pad4c[0x1c];Rva003F6DF9Child *get(int)const;};
struct Rva003F6DF9Listener {char opaque[4];};
struct Rva003F6DF9OwnerBase {virtual void interface0()=0;};
class Rva003F6DF9ListenerList {public:void append(Rva003F6DF9Listener*);private:void*words[3];};
struct Rva003F6DF9Payload {char pad8[8];Rva003F6DF9ListenerList listeners;char pad14[0x64];Rva003F6DF9Data *data;};
const void **Rva003F6DF9Find(const void**,const void**,const void*const&);
namespace _STL {
template<> void vector<const void*>::push_back(const void*const&);
template<> void vector<Rva003F6DF9Data>::push_back(const Rva003F6DF9Data&);
}
struct Rva003F6D35Inner {
 unsigned word;_STL::vector<const void*> payloads;_STL::vector<Rva003F6DF9Data> data;unsigned tail[5];Rva003F6D35Inner(int);~Rva003F6D35Inner();
};
struct Rva003F6D35Outer {
 int key;_STL::vector<Rva003F6D35Inner> inners;void*words[3];
 Rva003F6D35Outer(void*);~Rva003F6D35Outer();
};
namespace _STL {
template<> void vector<Rva003F6D35Inner>::reserve(unsigned);
template<> void vector<Rva003F6D35Inner>::push_back(const Rva003F6D35Inner&);
template<> void vector<Rva003F6D35Outer>::reserve(unsigned);
template<> void vector<Rva003F6D35Outer>::push_back(const Rva003F6D35Outer&);
}
class Rva003F6D35Owner:public Rva003F6DF9OwnerBase,public Rva003F6DF9Listener {public:
 __declspec(noinline) Rva003F6D35Inner *findOrCreateRva003F6D35(void*);
 void appendPayloadRva003F6DF9(void*,Rva003F6DF9Payload*);
 int findOuter(void*);int findInner(int,void*);
private:char pad[0x10];_STL::vector<Rva003F6D35Outer> outers;
};
Rva003F6D35Inner *Rva003F6D35Owner::findOrCreateRva003F6D35(void *p){
 int o=findOuter(p);
 if(o==-1){
  outers.reserve(2);
  outers.push_back(Rva003F6D35Outer(p));
  o=outers.size()-1;
 }
 Rva003F6D35Outer &outer=outers[o];
 int i=findInner(o,p);
 if(i==-1){
  outer.inners.reserve(6);
  outer.inners.push_back(Rva003F6D35Inner(reinterpret_cast<int>(p)));
  i=outer.inners.size()-1;
 }
 return &outer.inners[i];
}

#pragma comment(linker, "/alternatename:??0Rva003F6D35Inner@@QAE@H@Z=??0Rva003F610FElement@@QAE@H@Z")

#pragma comment(linker, "/alternatename:??0Rva003F6D35Outer@@QAE@PAX@Z=??0Rva003F64B2Outer@@QAE@PAURva003F64B2Input@@@Z")

#pragma comment(linker, "/alternatename:??1Rva003F6D35Inner@@QAE@XZ=??1Rva003F610FElement@@QAE@XZ")

#pragma comment(linker, "/alternatename:??1Rva003F6D35Outer@@QAE@XZ=??1BfmeStringRecord00111ACF@@QAE@XZ")

#pragma comment(linker, "/alternatename:?findInner@Rva003F6D35Owner@@QAEHHPAX@Z=?rva003F4FAA@Rva003F498A@@QAEHHPAX@Z")

#pragma comment(linker, "/alternatename:?findOuter@Rva003F6D35Owner@@QAEHPAX@Z=?rva003F4752@Rva003F498A@@QAEHPAX@Z")

#pragma comment(linker, "/alternatename:?push_back@?$vector@URva003F6D35Inner@@V?$allocator@URva003F6D35Inner@@@_STL@@@_STL@@QAEXABURva003F6D35Inner@@@Z=?push_back@?$vector@UBfmePod48@@V?$allocator@UBfmePod48@@@_STL@@@_STL@@QAEXABUBfmePod48@@@Z")

#pragma comment(linker, "/alternatename:?push_back@?$vector@URva003F6D35Outer@@V?$allocator@URva003F6D35Outer@@@_STL@@@_STL@@QAEXABURva003F6D35Outer@@@Z=?push_back@?$vector@UBfmeStringRecord00111ACF@@V?$allocator@UBfmeStringRecord00111ACF@@@_STL@@@_STL@@QAEXABUBfmeStringRecord00111ACF@@@Z")

#pragma comment(linker, "/alternatename:?reserve@?$vector@URva003F6D35Inner@@V?$allocator@URva003F6D35Inner@@@_STL@@@_STL@@QAEXI@Z=?reserve@?$vector@URva003F610FElement@@V?$allocator@URva003F610FElement@@@_STL@@@_STL@@QAEXI@Z")

#pragma comment(linker, "/alternatename:?reserve@?$vector@URva003F6D35Outer@@V?$allocator@URva003F6D35Outer@@@_STL@@@_STL@@QAEXI@Z=?reserve@?$vector@UBfmeStringRecord00111ACF@@V?$allocator@UBfmeStringRecord00111ACF@@@_STL@@@_STL@@QAEXI@Z")

void Rva003F6D35Owner::appendPayloadRva003F6DF9(void *input,Rva003F6DF9Payload *payload){
 Rva003F6D35Inner *inner=findOrCreateRva003F6D35(input);
 Rva003F6DF9Data *data=payload->data;
 if(data)data->dirty=0;
 if(Rva003F6DF9Find(inner->payloads.begin(),inner->payloads.end(),payload)==inner->payloads.end()){
  inner->payloads.push_back(payload);
  inner->data.push_back(*data);
  if(data){
   int count=data->entries.size();
   for(int i=0;i<count;++i){
    Rva003F6DF9Child *child=data->get(i);
    child->field98=0;child->flaga8=false;
   }
  }
  payload->listeners.append(static_cast<Rva003F6DF9Listener*>(this));
 }
}
