// cl: /MD /EHsc /GR-
#include "AptScriptFunction.h"
// Native constructor tags43/44 and field+30 agree with original PDB classes.

AptScriptFunction1::AptScriptFunction1(AptScriptFunctionBase *creator,const AptAction_DefineFunction *definition,AptCIH *cih)
    : AptScriptFunctionBase((AptVirtualFunctionTable_Indices)43,creator,cih,true),mpFunction(definition) {}
AptScriptFunction2::AptScriptFunction2(AptScriptFunctionBase *creator,const AptAction_DefineFunction2 *definition,AptCIH *cih)
    : AptScriptFunctionBase((AptVirtualFunctionTable_Indices)44,creator,cih,true),mpFunction(definition) {}

// PC vtables8EE938/8EE9A0 slots16..20 identify these getter bodies. Bind
// canonical virtual spellings to existing byte-verified providers; this adds
// no body or coverage claim. Their older opaque/donor labels are preserved,
// including MeshGeometryClass at709BE0: that label is not APT identity evidence.
// GetConstantPool1's hidden output-pointer ABI equals the existing21-byte
// ret4 copier, which returns the output pointer in EAX exactly as required.
#pragma comment(linker, "/alternatename:?GetName@AptScriptFunction1@@UBEPBDXZ=?rva00709BC0@Rva00709BC0@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetNumArguments@AptScriptFunction1@@UAEIXZ=?get@Rva00709D00PtrChaseField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetByteCodeBase@AptScriptFunction1@@UAEPBEXZ=?get@Rva00709BD0AddDwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetByteCodeSize@AptScriptFunction1@@UAEIXZ=?Get_Vertex_Array@MeshGeometryClass@@QAEPAVVector3@@XZ")
#pragma comment(linker, "/alternatename:?GetConstantPool@AptScriptFunction1@@UAE?AUAptConstantPool@@XZ=?rva00709BF0@Rva00709BF0@@QAEXPAURva00709BF0Pair@@@Z")
#pragma comment(linker, "/alternatename:?GetName@AptScriptFunction2@@UBEPBDXZ=?rva00709BC0@Rva00709BC0@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetNumArguments@AptScriptFunction2@@UAEIXZ=?get@Rva00709D00PtrChaseField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetByteCodeBase@AptScriptFunction2@@UAEPBEXZ=?get@Rva00709D10AddDwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetByteCodeSize@AptScriptFunction2@@UAEIXZ=?get@Rva00709D20PtrChaseField@@QBEHXZ")

// Native vtable slots and52-byte allocations establish Duplicate for both
// original PDB classes. The clone copies the +30 record pointer after the
// newly verified three-argument base clone, with type43/44 respectively.
// Allocation helpers are the same proven definitions used by DefineFunction.
class Rva006D2A60 {
public:
  void *allocBlock(int);
  void freeBlock(void *, int);
};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
// Native unwind passes both pointer and52B size; class-sized delete is required.
// Its emitted pool forwarder is a byte-and-relocation twin of6F12F0Free.
__forceinline void *AptScriptFunction1::operator new(unsigned int n) {
  return g_pChainBlockAllocatorF4->allocBlock(n);
}
__forceinline void AptScriptFunction1::operator delete(void *p, unsigned int n) {
  g_pChainBlockAllocatorF4->freeBlock(p, n);
}
__forceinline void *AptScriptFunction2::operator new(unsigned int n) {
  return g_pChainBlockAllocatorF4->allocBlock(n);
}
__forceinline void AptScriptFunction2::operator delete(void *p, unsigned int n) {
  g_pChainBlockAllocatorF4->freeBlock(p, n);
}
AptScriptFunctionBase *AptScriptFunction1::Duplicate(AptCIH *cih) {
  return new AptScriptFunction1(this, cih);
}
AptScriptFunctionBase *AptScriptFunction2::Duplicate(AptCIH *cih) {
  return new AptScriptFunction2(this, cih);
}
