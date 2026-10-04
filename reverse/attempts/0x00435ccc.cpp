// Rva00435CCC
// partial score=0.4666666667 date=2026-10-04
// Whole BFME1 source lead: revision 5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv435.cpp, compiled essentially as-is.
// Native wrapper435CCC/15 calls the no-stack-argument cdecl low-byte predicate
// 4354F3/375; on false tail-forwards to434EFA/525, otherwise returns.
// Both callees are unconverted. These declarations preserve observed call ABI
// only: their original identities and full return semantics remain unknown.
extern "C" unsigned char __cdecl Rva004354F3();
extern "C" void __cdecl Rva00434EFA();
extern "C" void __cdecl Rva00435CCC() {
    if (!Rva004354F3()) Rva00434EFA();
}
