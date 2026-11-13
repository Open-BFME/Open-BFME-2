// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva000C19C3@Rva000C19C3@@QAEXPAXPB_N@Z, retail 0x000C19C3 (542B, EH frame, RET 8).
// Asset-list collector of a model draw-module data object (WB twin 0x0094A4E0, unnamed; reached through the
// cdecl callback 0x000C32C7). The byte behind the flag argument picks one of two 0x14-byte cached asset lists
// at +0x160; a filled cache is appended to the output list directly. Otherwise the cache collects: the names
// of the 0xB4-byte part records at +8 (their name vectors at +0x10), the particle system at +0x14 (looked up
// through 0x001F9343), the texture at +0x3C with ".tga", each 0xFC-byte condition state at +0x18 (its asset
// list 0x000BCA71 and, once per distinct state name at +0x58, every 0xF8-byte transition at +0x24 through
// 0x000BC874), the name vectors of the 0x14-byte records at +0x7C, the handles of the 0x2C-byte records at
// +0x70 and the handle at +0x8C, and the cache is then appended to the output. Evidence: target bytes and
// the WB twin's traversal; original names are not established, field names are structural. The record
// arrays are real STLport vectors and the cache is re-indexed at each use, as retail recomputes it.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <vector>
template<class T> struct StringInlineData {int m_refCount,m_length;T m_text[1];};
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_Rb_tree(less<AsciiString> const &, allocator<AsciiString> const &); }
namespace _STL { template <> _Rb_tree_base<AsciiString, allocator<AsciiString> >::_Rb_tree_base(allocator<AsciiString> const &); }
namespace _STL { template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_create_node(AsciiString const &); }
namespace _STL { template <> void _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_erase(_Rb_tree_node<AsciiString> *); }
namespace _STL { template <> pair<_Rb_tree_iterator<AsciiString, _Nonconst_traits<AsciiString> >, bool> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::insert_unique(AsciiString const &); }
namespace _STL { template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??R?$less@VAsciiString@@@_STL@@QBE_NABVAsciiString@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
#include "../../Include/Common/AsciiStringRef.h"
#include "../../Include/Common/Rva000B3F84Pair.h"
#include "../../Include/Common/AsciiStringPlusText.h"
AsciiStringPlusText operator+(const AsciiString&,const char*);
struct Rva001408C0Target;
class AssetList{public:AssetList&operator<<(const AssetList&);AssetList&operator<<(const AsciiString&);bool empty()const{return prototypes.empty();}private:_STL::set<Rva001408C0Target*>prototypes;int pad;bool changed;};
struct AssetList00208F90{};
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/ModelSMConditionInfo.h"
class Rva0006C995{public:Rva0006C995*rva0006C995(Rva001408C0Target*);};
class Rva000BC874{public:void rva000BC874(AssetList*,int,const AsciiString&);};
class ParticleSystemTemplate;
#include "../../Include/GameClient/ParticleSys.h"
extern ParticleSystemManager*TheParticleSystemManager;
class GameLODManager;extern GameLODManager*TheGameLODManager;
struct LodView{char pad[0x1774];int value;};
struct Pair8{AsciiString name;int extra;};
struct RecordB4{char pad[0x10];_STL::vector<Pair8> names;char tail[0xb4-0x1c];};
struct StateFC{char pad[0x58];AsciiString name;char tail[0xfc-0x5c];};
struct TransitionF8{char pad[0xf8];};
struct Record14{int word;_STL::vector<AsciiString> names;char tail[4];};
struct Record2C{Rva001408C0Target*value;char tail[0x28];};
class Rva000C19C3{public:void rva000C19C3(void*,const bool*);
char pad0[8];_STL::vector<RecordB4> parts;AsciiString particle;
_STL::vector<StateFC> states;_STL::vector<TransitionF8> transitions;char pad30[0xc];AsciiString texture;
char pad40[0x30];_STL::vector<Record2C> handles;_STL::vector<Record14> extra;char pad88[4];Rva001408C0Target*handle;
char pad90[0x137-0x90];bool variants;char pad138[0x28];AssetList caches[2];};
void Rva000C19C3::rva000C19C3(void*outList,const bool*context){
AssetList*out=(AssetList*)outList;
int index=*context?1:0;
if(!caches[index].empty()){*out<<caches[index];return;}
int lod=((LodView*)TheGameLODManager)->value;
if(*context)lod=0;
for(_STL::vector<RecordB4>::iterator p=parts.begin();p!=parts.end();++p)
 for(_STL::vector<Pair8>::iterator n=p->names.begin();n!=p->names.end();++n)
  caches[index]<<n->name;
if(!particle.isEmpty())TheParticleSystemManager->rva001F9343(particle,(int)&caches[index]);
if(!texture.isEmpty())caches[index]<<(texture+".tga");
_STL::set<AsciiString>seen;
for(_STL::vector<StateFC>::iterator s=states.begin();s!=states.end();++s){
 ((ModelSMConditionInfo*)&*s)->GetAssetList((AssetList00208F90*)&caches[index],(int)context,lod,variants);
 if(seen.find(s->name)==seen.end()){
  seen.insert(s->name);
  for(_STL::vector<TransitionF8>::iterator t=transitions.begin();t!=transitions.end();++t)
   ((Rva000BC874*)&*t)->rva000BC874(&caches[index],(int)context,s->name);
 }
}
for(_STL::vector<Record14>::iterator e=extra.begin();e!=extra.end();++e)
 for(_STL::vector<AsciiString>::iterator n=e->names.begin();n!=e->names.end();++n)
  caches[index]<<*n;
for(_STL::vector<Record2C>::iterator h=handles.begin();h!=handles.end();++h)
 ((Rva0006C995*)&caches[index])->rva0006C995(h->value);
Rva001408C0Target*last=handle;
AssetList&result=caches[index];
((Rva0006C995*)&result)->rva0006C995(last);
*out<<result;
}
