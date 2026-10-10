// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii
// Full native AFD85..AFE9F CDECL writer and101F31..101F5C RET4 name getter.
// Native strings identify post-effect chunk output; actual101FD8 factory
// and102026 cleanup compare the same existing g_00DEC3B8 lookup-table key.
// 28B parameter records: float8 and AsciiString18 are proved by writer and
// existing111DB6 shader setup. Singleton20B layout uses existing1021F7 owner.
// NameProvider slot0 hidden-return ABI is native; its original name is unknown.
// Compatible BF1/ZH post-effect writer source was not available; retained
// canonical string/chunk output behavior and target-derived neutral names.
#include "ascii_string.h"
// Retail's key at VA 0x00DEC3B8 (defined once in Rva00101FD8Create.cpp as an
// AsciiString: StringBase's default ctor is private, its AsciiString spelling is
// public and the base subobject is at offset 0, so the address and the rowed
// compare at RVA 0x000069D6 are unchanged).
extern const AsciiString g_00DEC3B8;
class DataChunkOutput{public:void openDataChunk(char*,unsigned short);void writeByte(unsigned char);void writeReal(float);void writeAsciiString(const AsciiString&);void closeDataChunk();};
class Rva00101F31NameProvider{public:virtual AsciiString name();};
class Rva001021F7{public:AsciiString rva00101F31();Rva00101F31NameProvider*active;char rest[28];};
Rva001021F7*Rva00102215Get();
class Rva005C4AD1LeaField{public:void*get()const;};
struct Rva00111B25Record{AsciiString key;int word04;float value;char tail0C[12];AsciiString text;};
class Rva00111B5A{public:Rva00111B25Record*rva00111B5A(const char*);};
void __cdecl Rva000AFD85WriteChunk(DataChunkOutput*out){
 out->openDataChunk("PostEffectsChunk",1);
 Rva001021F7*state=Rva00102215Get();
 bool active=state->active!=0;
 out->writeByte(active);
 if(active){
  AsciiString name=state->rva00101F31();
  out->writeAsciiString(name);
  if(((StringBase<char>&)name).compare(*(const StringBase<char> *)&g_00DEC3B8)==0){
   Rva00111B5A*parameters=(Rva00111B5A*)((Rva005C4AD1LeaField*)state)->get();
   Rva00111B25Record*blend=parameters->rva00111B5A("BlendFactor");
   float factor=blend?blend->value:1.0f;
   out->writeReal(factor);
   Rva00111B25Record*texture=parameters->rva00111B5A("LookupTexture");
   out->writeAsciiString(texture?texture->text:AsciiString("Default_vol.tga"));
  }
 }
 out->closeDataChunk();
}

AsciiString Rva001021F7::rva00101F31(){if(active)return active->name();return AsciiString::TheEmptyString;}
