// ?rva00337555UnguardedInsertLoop@@YAXPAURva00337555Record@@00H@Z
// partial score=1.0 date=2026-10-04
// Full46 bytes equal after native constructor3371B1 and insert337424 bindings.
// Never publish as matched without repairing real selected copy67 -> vector96
// -> count-taking vectorbase5C8C37 closure; current kept BfmeStringRecord base
// is wrong. Required native ABI-view pins:
// ??0Rva00337555Record@@QAE@ABU0@@Z ->0x003371B1
// ?rva00337424InsertView@@YAXPAURva00337555Record@@U1@H@Z ->0x00337424
// Original payload/comparator identities remain unknown.
// cl: /O1 /MD /DNDEBUG /EHsc
// Banked whole stlport_unguarded_insertion_sort_s4sortelem20.cpp donor
// at1281192; native0x337555 transfers a20B value copied by native3371B1 to
// native337424, then advances iterator20B. Original record name unknown.
struct Rva00337555Record {
 int opaque[5];
 Rva00337555Record(const Rva00337555Record&);
 ~Rva00337555Record();
};
void rva00337424InsertView(Rva00337555Record*,Rva00337555Record,int);
void rva00337555UnguardedInsertLoop(Rva00337555Record *first,
 Rva00337555Record *last, Rva00337555Record *,int slot) {
 for(Rva00337555Record *i=first;i!=last;++i)
  rva00337424InsertView(i,*i,slot);
}
#pragma comment(linker,"/alternatename:??0Rva00337555Record@@QAE@ABU0@@Z=??0Rva003371B1@@QAE@ABV0@@Z")
#pragma comment(linker,"/alternatename:?rva00337424InsertView@@YAXPAURva00337555Record@@U1@H@Z=?Rva00337424Insert@@YAXPAVRva002E9E70@@VRva003371B1@@H@Z")
