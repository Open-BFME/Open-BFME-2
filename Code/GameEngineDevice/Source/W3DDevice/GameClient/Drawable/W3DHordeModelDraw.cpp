// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail0007A54B..0007A706 RET0: process compatible handle ranges by manager.
// WB918FA0 (W3DHordeModelDraw.cpp) contains the same manager cleanup/sort,
// RB traversal, inlined PartOfSameGroup and named ProcessGroup918370 call.
// The WB lead calls the entire manager body PartOfSameGroup: that is an
// inlined helper, so the manager entry keeps an address-derived method name.
// Target facts: manager header/count00/04; nodes module10/vector14..1C;
// handles model00/name04; model object08/animations110/12C, 28B records;
// object scale200. LOD level1788 and provider188..194 are existing row facts.
// All condition branches, float unordered comparison behavior, both fabs
// checks, group count and iterator advancement follow the complete target.
// Four LOD accessors and their index helper retain existing names/layouts;
// compiling them in this TU is necessary: caller keeps EDX across79176.
// This is clean retail reconstruction; no donor body establishes new names.
// Standard math.h float overload preserves native stack-pop/x87 scheduling.

#include <map>
#include <vector>
#include <list>
#include <string>
#include <math.h>
struct Rva00DFE144Globals
{
	char m_pad[0x1788];
	int m_1788;
};

extern class GameLODManager *TheGameLODManager;

__declspec(noinline) int Rva0007912DGet(void)
{
	int v = (*(Rva00DFE144Globals **)&TheGameLODManager)->m_1788 - 1;
	if (v < 0)
		return 0;
	if (v > 2)
		return 2;
	return v;
}

struct HordeLodEntry
{
	bool m_allow;
	char m_pad189[3];
	int m_maxTex;
	int m_maxAnim;
	float m_delta;
	int m_start;
};

class W3DHordeModelDrawModuleData
{
public:
	__declspec(noinline) bool rva00079147();
	__declspec(noinline) int rva00079157();
	__declspec(noinline) int rva00079167();
	__declspec(noinline) float rva00079176();
	char m_pad[0x188];
	HordeLodEntry m_lods[3];
};

__declspec(noinline) bool W3DHordeModelDrawModuleData::rva00079147()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_allow;
}

__declspec(noinline) int W3DHordeModelDrawModuleData::rva00079157()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_maxTex;
}

__declspec(noinline) int W3DHordeModelDrawModuleData::rva00079167()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_maxAnim;
}

__declspec(noinline) float W3DHordeModelDrawModuleData::rva00079176()
{
	int idx = Rva0007912DGet();
	return m_lods[idx].m_delta;
}

class Rva00079911 {public: void rva00079911();};
class Rva007A41E {public: void rva007A41E();};
class Rva00078C10 {public: bool rva00078C10(const Rva00078C10*,int*,int*);};
struct HordeModelObject {char p[0x200]; float scale;};
struct HordeAnimation {void *animation;float frame;char p[8];int mode;int direction;int tail;};
struct HordeModelDraw {char p[8];HordeModelObject *object;char q[0x110-12];HordeAnimation animations[2];};
struct W3DHordeModelDrawHandle {HordeModelDraw *model; int nameKey;
 __forceinline bool PartOfSameGroup(const W3DHordeModelDrawHandle& first,float delta) const;
};
struct HordeGroupNode: _STL::_Rb_tree_node_base {W3DHordeModelDrawModuleData *data;W3DHordeModelDrawHandle **begin;W3DHordeModelDrawHandle **end;W3DHordeModelDrawHandle **capacity;};
class W3DHordeModelDrawManager {public:
 int rva0007A54B();
 void ProcessGroup(W3DHordeModelDrawHandle **begin,W3DHordeModelDrawHandle **end);
 HordeGroupNode *header;int count;
};
// ?W3DHordeModelDrawHandle::PartOfSameGroup present-unmatched
__forceinline bool W3DHordeModelDrawHandle::PartOfSameGroup(const W3DHordeModelDrawHandle& first,float delta) const {
 if((*(Rva00DFE144Globals **)&TheGameLODManager)->m_1788==4) return false;
 if(nameKey!=first.nameKey) return false;
 if(model->object->scale!=first.model->object->scale) return false;
 int a,b;
 if(model && first.model && ((Rva00078C10*)model)->rva00078C10((Rva00078C10*)first.model,&a,&b) && a!=b) return false;
 for(int i=0;i<=1;++i) {
  const HordeAnimation& mine=model->animations[i];const HordeAnimation& theirs=first.model->animations[i];
  if(mine.animation!=theirs.animation) return false;
  if(!mine.animation) continue;
  if(mine.direction!=theirs.direction) return false;
  if(mine.mode!=theirs.mode) return false;
 }
 if(fabs(model->animations[0].frame-first.model->animations[0].frame)>delta) return false;
 if(model->animations[1].animation && fabs(model->animations[1].frame-first.model->animations[1].frame)>delta) return false;
 return true;
}
int W3DHordeModelDrawManager::rva0007A54B() {
 int groups=0;
 ((Rva00079911*)this)->rva00079911();
 ((Rva007A41E*)this)->rva007A41E();
 if(!count) return 0;
 for(HordeGroupNode *node=(HordeGroupNode*)header->_M_left;node!=header;node=(HordeGroupNode*)_STL::_Rb_global<bool>::_M_increment(node)) {
  W3DHordeModelDrawHandle **first=node->begin,**end=node->end;
  for(W3DHordeModelDrawHandle **p=first;p!=end;) {
   ++p;
   float delta;
   if(p==end) goto process;
   delta=node->data->rva00079176();
   { W3DHordeModelDrawHandle *a=*first,*b=*p;
   if(b->PartOfSameGroup(*a,delta)) goto next; }
process: {
    ProcessGroup(first,p);++groups;first=p;
   }
next:;
  }
 }
 return groups;
}

// Native7A706..7A75E RET4, WB919920. Existing bfmeAttachYS pin is a
// provisional BFME1 helper spelling, not an established original method name.
// Target owns an 8-byte draw/key handle, inserts it into the unsigned-keyed
// vector map at manager00 and stores the handle at draw2E8. All dependencies
// are independently rowed: map7A26E, vector4DFCB0, nameToKey148E1A, new2FDA0.
// Existing attachment source lead retained; no attachment body is claimed here.
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public: NameKeyType nameToKey(const char *name);};
extern NameKeyGenerator *TheNameKeyGenerator;
typedef _STL::vector<unsigned int> HordeHandleWordVector;
typedef _STL::map<unsigned int,HordeHandleWordVector> HordeHandleWordMap;
namespace _STL {
template <> HordeHandleWordVector &HordeHandleWordMap::operator[](const unsigned int &);
template <> void HordeHandleWordVector::push_back(const unsigned int &);
}
class Gen_00755E70 {
public:
 void *vtable;
 unsigned int moduleKey;
 char pad[0x2E8-8];
 W3DHordeModelDrawHandle *handle;
};
class BfmeHelperYS {
public:
 BfmeHelperYS();
 void bfmeAttachYS(Gen_00755E70 *owner);
 HordeHandleWordMap handles;
 _STL::list<HordeHandleWordVector> groups;
 HordeHandleWordVector refs,models;
};

BfmeHelperYS::BfmeHelperYS():handles(),groups(),refs(),models() {}

// Constructor native7A498..7A4E6 RET0:40-byte manager owns map00, opaque08,
// list of 12-byte slot vectors0C and pointer-word vectors10/1C. Layout is
// independently supported by rowed teardown7A4E6 and ProcessGroup79FBC.
// bfme helper name is retained from its existing verified caller pin;
// original constructor class name is not newly asserted by this recovery.
