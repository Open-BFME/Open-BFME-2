// cl: /O1 /Oy- /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii
// Target BCA71..BCDBF846B; WB94AAB0 explicit ModelSMConditionInfo::GetAssetList.
// Reference-first pass: no same-class clean BF1/ZH body; established
// string/asset source providers are reused with native whole-byte verification.
// Original parameter spelling/class kind are unproven: pointer plus opaque
// int context/int LOD/bool is the native ret16 ABI view. No full class-layout
// or inheritance assertion is made; every accessed field below comes from
// native bytes and aligned WB list/record/texture traversal.
// String suffixes L M _n _nr _ne _nd _r _e _d and .tga are complete native literals.
// Fields are scoped native ABI views; context remains opaque32-bit.
template<class T> struct StringInlineData {int m_refCount,m_length;T m_text[1];};
#include "ascii_string.h"
struct AsciiStringRef {const AsciiString* m_string;};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){}const char* m_ptr;int m_len;};
struct AsciiStringPlusText:AsciiStringRef {operator AsciiString();Rva000B3F84Pair m_right;};
AsciiStringPlusText operator+(const AsciiString&,const char*);
struct AssetList00208F90 {AssetList00208F90& operator<<(const AsciiString&);};
bool Render_Obj_Exists(const char*);
class Rva000B2D4D {public:void rva000B2D4D(int,int);};
class Rva001E11F8 {public:void rva001E11F8(int,int);};
struct BfmeModelAssetNode {BfmeModelAssetNode* next;BfmeModelAssetNode* prev;char value[0x14];};
struct BfmeModelEffectRecord {char pad[0x14];Rva001E11F8* value;};
struct BfmeModelNamedRecord {int key;AsciiString value;};
class ModelSMConditionInfo {
 char pad00[0x4c];AsciiString* models;AsciiString* modelsEnd;void* modelsCapacity;
 AsciiString name58;char pad5c[8];BfmeModelNamedRecord* names;BfmeModelNamedRecord* namesEnd;void* namesCapacity;
 char pad70[0xb4-0x70];BfmeModelAssetNode* node;
 BfmeModelEffectRecord* effects;BfmeModelEffectRecord* effectsEnd;void* effectsCapacity;
 BfmeModelEffectRecord* extraEffects;BfmeModelEffectRecord* extraEffectsEnd;void* extraEffectsCapacity;
 char padD0[0xdc-0xd0];AsciiString* texture;
 public:void GetAssetList(AssetList00208F90*,int context,int lod,bool variants);
};
void ModelSMConditionInfo::GetAssetList(AssetList00208F90* assets,int context,int lod,bool variants) {
 AsciiString* end=modelsEnd;
 AsciiString* it=models;
 if(it!=end)do {
  AsciiString name(*it);
  switch(lod){case 0: ((StringBase<char>*)&name)->concat("L");break;case 1:((StringBase<char>*)&name)->concat("M");break;}
  if(!Render_Obj_Exists(name.str()))name=*it;
  if(variants){
   *assets<<name;
   *assets<<(name+"_n");
   *assets<<(name+"_nr");
   *assets<<(name+"_ne");
   *assets<<(name+"_nd");
   *assets<<(name+"_r");
   *assets<<(name+"_e");
   *assets<<(name+"_d");
  }else *assets<<name;
 }while(++it!=modelsEnd);
 if(!((StringBase<char>*)&name58)->isEmpty())*assets<<name58;
 for(BfmeModelAssetNode* it=node->next;it!=node;it=it->next) ((Rva000B2D4D*)it->value)->rva000B2D4D((int)assets,context);
 BfmeModelEffectRecord* fx=effects;
 BfmeModelEffectRecord* fxEnd=effectsEnd;
 if(fx!=fxEnd)do{if(fx->value)fx->value->rva001E11F8((int)assets,context);}while(++fx!=effectsEnd);
 for(BfmeModelEffectRecord* it=extraEffects;it!=extraEffectsEnd;++it) if(it->value)it->value->rva001E11F8((int)assets,context);
 AsciiString* tex=texture;
 if(tex && !((StringBase<char>*)tex)->isEmpty())*assets<<(*tex+".tga");
 for(BfmeModelNamedRecord* it=names;it!=namesEnd;++it)*assets<<it->value;
}
