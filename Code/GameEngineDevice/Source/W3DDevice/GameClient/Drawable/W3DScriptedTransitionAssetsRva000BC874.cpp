// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// Native BC874..BC9B1 RET12 and WB923860 independently agree on model-vector,
// FX and node traversal. Parent C19C3 supplies cache AssetList/context/state name;
// records are scoped target ABI views, not a claim of original class/layout names.
// Reference-first: no clean same-class ZH/BF1 transition collector; existing
// BF1 AssetListCollect/ModelConditionInfoPreloadAssets guide subsystem behavior.
// Target native literals are complete "a*" and "."; fields/strides are native.
// Existing StringBase, pair materializer and effect delegates preserve semantics.
template<class T> struct StringInlineData{int m_refCount,m_length;T m_text[1];};
#include "ascii_string.h"
struct AsciiStringPlusString{const AsciiString*m_left,*m_right;operator AsciiString();};
class AssetList{public:AssetList&operator<<(const AsciiString&);};
class Rva001E11F8{public:void rva001E11F8(int,int);};
class Rva000B2D4D{public:void rva000B2D4D(int,int);};
struct TransitionModel40{AsciiString*begin,*end;char tail[0x38];};
struct TransitionFx18{char pad[0x14];Rva001E11F8*value;};
struct TransitionNode{TransitionNode*next,*prev;char value[0x14];};
class Rva000BC874{public:void rva000BC874(AssetList*,int,const AsciiString&);char pad0[0x50];TransitionModel40*models,*modelsEnd;char pad58[0x10];Rva001E11F8*fx;char pad6c[8];TransitionNode*nodes;TransitionFx18*effects,*effectsEnd;int cap;TransitionFx18*extra,*extraEnd;};
void Rva000BC874::rva000BC874(AssetList*assets,int context,const AsciiString&name){
TransitionModel40*m=models;TransitionModel40*end=modelsEnd;
if(m!=end)do{
 AsciiString prefix("a*");
 if(!((const StringBase<char>*)&name)->isEmpty()){
 ((StringBase<char>*)&prefix)->concat((const StringBase<char>&)name);
 ((StringBase<char>*)&prefix)->concat(".");
 }
 for(unsigned i=0;i<(unsigned)(m->end-m->begin);++i){AsciiStringPlusString pair;pair.m_left=&prefix;pair.m_right=&m->begin[i];*assets<<pair;}
}while(++m!=modelsEnd);
if(fx)fx->rva001E11F8((int)assets,context);
TransitionNode*n=nodes->next;if(n!=nodes)do{((Rva000B2D4D*)n->value)->rva000B2D4D((int)assets,context);}while((n=n->next)!=nodes);
for(TransitionFx18*p=effects;p!=effectsEnd;++p)if(p->value)p->value->rva001E11F8((int)assets,context);
for(TransitionFx18*p=extra;p!=extraEnd;++p)if(p->value)p->value->rva001E11F8((int)assets,context);
}
