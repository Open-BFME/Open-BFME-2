// ?rva000C19C3@Rva000C19C3@@QAEXPAVAssetList@@PAX@Z
// partial score=0.96125 date=2026-10-10
// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
template<class T> struct StringInlineData {int m_refCount,m_length;T m_text[1];};
#include "ascii_string.h"
namespace _STL {template<class T,class L,class R> static inline bool operator!=(const _Rb_tree_iterator<T,L>&a,const _Rb_tree_iterator<T,R>&b){return a._M_node!=b._M_node;}}
struct AsciiStringRef{const AsciiString*m_string;};
class Rva000B3F84Pair{public:Rva000B3F84Pair(){}const char*m_ptr;int m_len;};
struct AsciiStringPlusText:AsciiStringRef{operator AsciiString();Rva000B3F84Pair m_right;};
AsciiStringPlusText operator+(const AsciiString&,const char*);
struct Rva001408C0Target;
class AssetList{public:AssetList&operator<<(const AssetList&);AssetList&operator<<(const AsciiString&);bool empty()const{return prototypes.empty();}private:_STL::set<Rva001408C0Target*>prototypes;int pad;bool changed;};
struct AssetList00208F90{};
class ModelSMConditionInfo{public:void GetAssetList(AssetList00208F90*,int,int,bool);};
class Rva0006C995{public:Rva0006C995*rva0006C995(Rva001408C0Target*);};
class Rva000BC874{public:void rva000BC874(AssetList*,int,const AsciiString&);};
class ParticleSystemTemplate;
class ParticleSystemManager{public:ParticleSystemTemplate*rva001F9343(const AsciiString&,int)const;};
extern ParticleSystemManager*TheParticleSystemManager;
class GameLODManager;extern GameLODManager*TheGameLODManager;
struct LodView{char pad[0x1774];int value;};
struct Pair8{AsciiString name;int extra;};
struct RecordB4{char pad[0x10];Pair8*begin,*end;char tail[0xb4-0x18];};
struct StateFC{char pad[0x58];AsciiString name;char tail[0xfc-0x5c];};
struct TransitionF8{char pad[0xf8];};
struct Record14{int word;AsciiString*begin,*end;char tail[8];};
struct Record2C{Rva001408C0Target*value;char tail[0x28];};
class Rva000C19C3{public:void rva000C19C3(AssetList*,void*);
char pad0[8];RecordB4*parts,*partsEnd;int cap;AsciiString particle;
StateFC*states,*statesEnd;int stateCap;TransitionF8*transitions,*transitionsEnd;int transCap;char pad30[0xc];AsciiString texture;
char pad40[0x30];Record2C*handles,*handlesEnd;int handleCap;Record14*extra,*extraEnd;int extraCap;char pad88[4];Rva001408C0Target*handle;
char pad90[0x137-0x90];bool variants;char pad138[0x28];AssetList caches[2];};
void Rva000C19C3::rva000C19C3(AssetList*out,void*context){
int index=*(bool*)context?1:0;
if(!caches[index].empty()){*out<<caches[index];return;}
int lod=((LodView*)TheGameLODManager)->value;
if(*(bool*)context)lod=0;
for(RecordB4*p=parts;p!=partsEnd;++p)for(Pair8*n=p->begin;n!=p->end;++n)caches[index]<<n->name;
if(!((StringBase<char>*)&particle)->isEmpty())TheParticleSystemManager->rva001F9343(particle,(int)&caches[index]);
if(!((StringBase<char>*)&texture)->isEmpty())caches[index]<<(texture+".tga");
_STL::set<AsciiString>seen;
StateFC*s=states;
if(s!=statesEnd){
AsciiString*name=&((StateFC*)*(StateFC*volatile*)&s)->name;
do{
 ((ModelSMConditionInfo*)s)->GetAssetList((AssetList00208F90*)&caches[index],(int)context,lod,variants);
 if(seen.find(*name)==seen.end()){
  seen.insert(*name);
  for(TransitionF8*t=transitions;t!=transitionsEnd;++t)((Rva000BC874*)t)->rva000BC874(&caches[index],(int)context,*name);
 }
++s;name=(AsciiString*)((char*)name+0xfc);
}while(s!=statesEnd);
}
for(Record14*p=extra;p!=extraEnd;++p)for(AsciiString*n=p->begin;n!=p->end;++n)caches[index]<<*n;
for(Record2C*p=handles;p!=handlesEnd;++p)((Rva0006C995*)&caches[index])->rva0006C995(p->value);
Rva001408C0Target*last=handle;AssetList*lastCache=&caches[index];
((Rva0006C995*)lastCache)->rva0006C995(last);
*out<<*lastCache;
}
