// ?rva0020E90F@Rva0020E90FView@@QAEPAVRva0020E89C@@H@Z
// partial score=0.8 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ob1 /EHsc /MD
class Rva0020E89C { public: char pad[0x12c]; int key; };
class Rva0020E90FView {
public:
 Rva0020E89C *rva0020E90F(int key);
 __forceinline unsigned count() const {
  int bytes=(int)((const volatile Rva0020E90FView *)this)->last;
  bytes-=(int)((const volatile Rva0020E90FView *)this)->first;
  return (unsigned)(bytes>>2);
 }
 char pad[0x2c]; Rva0020E89C **first,**last;
};
Rva0020E89C *Rva0020E90FView::rva0020E90F(int key)
{
 if (key == -1) return 0;
 int start=key;
 if ((unsigned)key >= count() || key < 0) start=0;
 for (unsigned index=start; index<count(); ++index)
  if (first[index]->key == key) return first[index];
 for (int index=0; index<start; ++index)
  if (first[index]->key == key) return first[index];
 return 0;
}
