// cl: /O1 /Oy- /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// Native gap-filler context cleanup family. Existing DX8Wrapper::Shutdown
// 125DC0 and deleting destructor11CC10 independently call174753; constructor
// allocation and TheMeshGapFillerContext already establish the opaque owner.
// Native vectors occupy0/C/18 and use owned32B BfmeAssignRecord32 providers.
// 174350 clears the pointee at first-pointer+310, then erases vectorC;
// 17437D erases vector18. No original helper names are claimed.
// Destructor185 erases vector0, invokes both helpers, releases and clears
// globals DF36B4 and DFCEB8, then frees pointer24 and destroys all vectors.
// g_gapFillerAuxiliarySource is a provisional symbol for the unowned DFCEB8
// pointer; its source identity and concrete dynamic type remain unresolved.
// The release view establishes only native slot0(flags0)->pointer ABI.
// The existing allocator declaration preserves the retail EH-state2 store.
#include <vector>
struct Rva00087A93 { void *m_data; };
struct BfmeAssignRecord32 {
 BfmeAssignRecord32(const BfmeAssignRecord32 &);
 BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &);
 ~BfmeAssignRecord32();
 Rva00087A93 s; int x; Rva00087A93 arr[6];
};
struct Rva00174350MeshView { char opaque00[0x310]; unsigned *slot310; };
void __cdecl Rva00030830FreeAllocation(void *);
void __cdecl operator delete(void *);
struct Rva00174753Allocation { void *pointer; ~Rva00174753Allocation(){if(pointer)Rva00030830FreeAllocation(pointer);} };
struct Rva00174753ReleaseView { virtual void *releaseInstance(unsigned)=0; };
class FXShaderParameterSourceNamespaceSAS;
extern FXShaderParameterSourceNamespaceSAS *g_00DF36B4;
// Native 9FCEB8 starts at zero; preparation and cleanup share this provider.
Rva00174753ReleaseView *g_gapFillerAuxiliarySource = 0;
class Rva00DF6F94GapFillerContext {
 _STL::vector<BfmeAssignRecord32> records;
 _STL::vector<BfmeAssignRecord32> active;
 _STL::vector<BfmeAssignRecord32> pending;
 Rva00174753Allocation allocation;
public:
 ~Rva00DF6F94GapFillerContext();
 void rva00174350();
 void rva0017437D();
};
void Rva00DF6F94GapFillerContext::rva00174350() {
 _STL::vector<BfmeAssignRecord32> *v=&active;for(BfmeAssignRecord32 *record=v->begin();record!=active.end();++record){
  unsigned *slot=static_cast<Rva00174350MeshView *>(record->s.m_data)->slot310;
  if(slot)*slot=0;
 }
 v->erase(v->begin(),v->end());
}
void Rva00DF6F94GapFillerContext::rva0017437D() {_STL::vector<BfmeAssignRecord32> *v=&pending;v->erase(v->begin(),v->end());}

Rva00DF6F94GapFillerContext::~Rva00DF6F94GapFillerContext(){
 _STL::vector<BfmeAssignRecord32> *v=&records;v->erase(v->begin(),v->end());
 rva00174350();
 rva0017437D();
 Rva00174753ReleaseView *source=reinterpret_cast<Rva00174753ReleaseView *>(g_00DF36B4);
 operator delete(source?source->releaseInstance(0):0);
 g_00DF36B4=0;
 operator delete(g_gapFillerAuxiliarySource?g_gapFillerAuxiliarySource->releaseInstance(0):0);
 g_gapFillerAuxiliarySource=0;
}
