// ?bind@Rva00150E54@@QAEXPBD0PAURva00150E54Context@@@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /MD
// stlport
#include <vector>
struct Rva001530E9Parts { char name[64];bool star,bracket;char pad[2];int index;const char *ext; };
void __cdecl Rva001530E9Parse(const char*,void*volatile);
struct Rva00150E54Descriptor { char prefix[24];unsigned count;char tail[16]; };
struct Rva00150E54Com {
 virtual void __stdcall slot00();virtual void __stdcall slot04();virtual void __stdcall slot08();virtual void __stdcall slot0C();
 virtual void __stdcall describe(const char*,Rva00150E54Descriptor*);
 virtual void __stdcall slot14();virtual void __stdcall slot18();virtual void __stdcall slot1C();virtual void __stdcall slot20();virtual void __stdcall slot24();virtual void __stdcall slot28();
 virtual void* __stdcall at(const char*,unsigned);
};
struct Rva00150E54Context {Rva00150E54Com *com;void prepare(const char*);void finish();};
struct Rva00150E54Entry { virtual ~Rva00150E54Entry(); virtual void bind(const char*,void*,Rva00150E54Context*);int index; };
class Rva00150E54 {unsigned vptr;_STL::vector<Rva00150E54Entry> values;Rva00150E54Entry fallback;public:void bind(const char*,const char*,Rva00150E54Context*);};
void Rva00150E54::bind(const char* path,const char* name,Rva00150E54Context*context) {
 Rva001530E9Parts parts;Rva00150E54Descriptor desc;
 Rva001530E9Parse(path,&parts);
 const char *original=name;
 context->prepare(original);
 Rva00150E54Com *com=context->com;
 if(parts.star) {
  com->describe(original,&desc);
  for(unsigned i=0;i<desc.count;++i) {
   void* handle=com->at(name,i);
   if(i<values.size()) values[i].bind(parts.ext,handle,context);
   else fallback.bind(parts.ext,handle,context);
  }
 } else if(parts.bracket) {
  Rva00150E54Entry *entry=parts.index>=0 && (unsigned)parts.index<values.size()?&values[parts.index]:&fallback;
  entry->bind(parts.ext,(void*)original,context);
 }
 context->finish();
}
