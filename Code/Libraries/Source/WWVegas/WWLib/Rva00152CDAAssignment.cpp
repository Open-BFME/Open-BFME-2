// cl: /O1 /MD
struct Rva00152CDACall {virtual void* get();};
struct Rva00152CDAHeader {unsigned refs,length;};
extern char g_Rva007BAC1CEmpty;
class Rva00152CDA {unsigned prefix[2];Rva00152CDACall *handle;unsigned values[3];Rva00152CDAHeader *text;public:Rva00152CDA& operator=(const Rva00152CDA&);void apply(void*,const char*,const void*,unsigned);};
Rva00152CDA& Rva00152CDA::operator=(const Rva00152CDA& source) {
 if(this!=&source) {
  const char *name=source.text?(const char*)(source.text+1):&g_Rva007BAC1CEmpty;
  Rva00152CDACall *object=source.handle;
  void *value=object?object->get():0;
  apply(value,name,source.values,4);
 }
 return *this;
}

// Target facts: Ghidra 00152CDA..00152D1C and native ret4, 66B;
// self-assignment guard; handle+8 with virtual slot0, text header+24
// yielding data+8 or the canonical null character, values+12 and count4.
// Four-argument thiscall helper 0015288F is decoded from native REL32.
// No original class or field identity is asserted by these address names.
#pragma comment(linker, "/alternatename:?g_Rva007BAC1CEmpty@@3DA=?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB")
