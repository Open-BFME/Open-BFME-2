// cl: /O1 /G7 /Oy- /MD /EHsc /DNDEBUG
// Fresh file drain: registration180CCB..180D4A(127B) and lazy loader
// 180D4A..180E38(238B). Existing neighboring prototype ctor establishes size24,
// definition14/name18/file-range1C/20; native calls establish both contracts.
// ZH agg_def.h/cpp and BF1 575ba2's owned AggregateDefClass and ChunkLoadClass
// providers guide resource ownership. BFME2 chunk extentC18 and low-byte virtual
// load result are measured from this body; do not transfer the donor Load_W3D
// name or enum semantics onto its unknown slot. The loader's original name is
// likewise unknown. Explicit global delete preserves destructor flag0 followed
// by global deallocation, unlike an ordinary delete expression.
bool __cdecl Render_Obj_Exists(const char*);
void *__cdecl operator new(unsigned int)throw();
void __cdecl operator delete(void*);
void __cdecl Add_Prototype(void*);
class StringClass {
 char *buffer;void Free_String();
public:StringClass(const StringClass&,bool=false);__forceinline ~StringClass(){Free_String();}
 const StringClass &operator+=(const char*);__forceinline const char*str()const{return buffer;}
};
class Rva00180B94_Prototype {char pad[0x14];void *definition;StringClass name;int start,size;
public:Rva00180B94_Prototype(const char*,void*);void rva00180D4A();};
class AggregatePayload {public:virtual ~AggregatePayload();};
void __cdecl Rva00180CCBRegister(const char *name,AggregatePayload *payload) {
 if(name&&payload) {
  if(Render_Obj_Exists(name))::delete payload;
  else Add_Prototype(new Rva00180B94_Prototype(name,payload));
 } else ::delete payload;
}

class BFMEChunkInput;
class ChunkLoadClass {char buffer[0xC18];public:ChunkLoadClass(BFMEChunkInput*);bool Open_Chunk();unsigned long Cur_Chunk_ID();};
class File {public:virtual void slot0();virtual void slot1();virtual void close();};
File * __cdecl GetGameFilePart(const char*,int,int);
class AggregateDefClass {
 char pad[0x58];
public:AggregateDefClass();virtual ~AggregateDefClass();
 virtual bool slotLoad(ChunkLoadClass*);
};
void Rva00180B94_Prototype::rva00180D4A() {
 StringClass filename(name,false);filename+=".w3d";
 File *file=GetGameFilePart(filename.str(),start,size);
 if(file) {
  ChunkLoadClass chunk((BFMEChunkInput*)file);
  if(chunk.Open_Chunk()&&chunk.Cur_Chunk_ID()==0x600) {
   definition=new AggregateDefClass;
   if(!((AggregateDefClass*)definition)->slotLoad(&chunk)) {
    ::delete (AggregateDefClass*)definition;definition=0;
   }
  }
  file->close();
 }
}
