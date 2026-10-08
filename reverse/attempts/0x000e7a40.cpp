// ?rva000E7A40@Rva000E7A40@@QAEXH@Z
// partial score=0.96 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native Ghidra 0xE7A40..0xEB3D1 RET4. Receiver/index view remains opaque.
// Native stride A0, descriptor stride5C, unsigned counters and opacity calls
// establish the accessed fields; no donor identity is asserted.
void rva0010E87A(int, float);
struct Rva000E7A40RecordView {
 char pad00[0x1998]; int descriptor;
 char pad199c[0x19e8-0x199c]; unsigned frames;
 int oldObject, newObject;
};
struct Rva000E7A40Descriptor {char pad[0x4c];unsigned duration;};
struct Rva000E7A40DescriptorSlot { Rva000E7A40Descriptor *value; char pad[0x5c-4];};
class Rva000E7A40 {
public:
 void rva000E7A40(int index);
 void rva000E75F5(int index);
private:
 char pad[0x4fb58];int count;char pad4fb5c[0x4fb90-0x4fb5c];
 Rva000E7A40DescriptorSlot descriptors[1];
};
void Rva000E7A40::rva000E7A40(int index) {
 Rva000E7A40RecordView *r=reinterpret_cast<Rva000E7A40RecordView *>(reinterpret_cast<char *>(this)+index*0xa0);
 int descriptor=r->descriptor;
 if(index<count) {
  if(descriptor>=0) {
   {
    --r->frames;
    float alpha=static_cast<float>(r->frames)/static_cast<float>(descriptors[descriptor].value->duration);
    if(r->oldObject)rva0010E87A(r->oldObject,alpha);
    if(r->newObject)rva0010E87A(r->newObject,1.0f-alpha);
    if(r->frames==0)rva000E75F5(index);
   }
  }
 }
}
