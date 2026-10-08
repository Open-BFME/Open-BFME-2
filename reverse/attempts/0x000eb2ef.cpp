// ?rva000EB2EF@Rva000EB2EF@@QAEXH@Z
// partial score=0.96 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native Ghidra 0xEB2EF..0xEB3D1 RET4. Receiver/index view remains opaque.
// Native stride E8, descriptor stride5C, unsigned counters and opacity calls
// establish the accessed fields; no donor identity is asserted.
void rva0010E87A(int, float);
struct Rva000EB2EFRecordView {
 char pad00[0x600]; int descriptor;
 char pad604[0x640-0x604]; int immediate;
 char pad644[0x684-0x644]; bool stopped;
 char pad685[0x694-0x685]; unsigned frames;
 int oldObject, newObject;
};
struct Rva000EB2EFDescriptor {char pad[0x4c];unsigned duration;};
struct Rva000EB2EFDescriptorSlot { Rva000EB2EFDescriptor *value; char pad[0x5c-4];};
class Rva000EB2EF {
public:
 void rva000EB2EF(int index);
 void rva000EB0E6(int index);
private:
 char pad[0x44540];int count;char pad44544[0x44578-0x44544];
 Rva000EB2EFDescriptorSlot descriptors[1];
};
void Rva000EB2EF::rva000EB2EF(int index) {
 if(index<count) {
  Rva000EB2EFRecordView *r=reinterpret_cast<Rva000EB2EFRecordView *>(reinterpret_cast<char *>(this)+index*0xe8);
  if(r->descriptor>=0) {
   if(r->stopped || r->immediate) rva000EB0E6(index);
   else {
    --r->frames;
    float alpha=static_cast<float>(r->frames)/static_cast<float>(descriptors[r->descriptor].value->duration);
    if(r->oldObject)rva0010E87A(r->oldObject,alpha);
    if(r->newObject)rva0010E87A(r->newObject,1.0f-alpha);
    if(r->frames==0)rva000EB0E6(index);
   }
  }
 }
}
