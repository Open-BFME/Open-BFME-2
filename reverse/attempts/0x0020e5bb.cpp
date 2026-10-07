// ?rva0020E5BB@Rva0020E5BB@@QAEPAXH@Z
// partial score=0.85 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
struct Rva0020E5BBEntry { unsigned char pad[0x34]; int key; };
class Rva0020E5BB {
public:
 void *rva0020E5BB(int key);
 __forceinline unsigned count() const {
  int bytes = (int)((const volatile Rva0020E5BB *)this)->last;
  bytes -= (int)((const volatile Rva0020E5BB *)this)->first;
  return (unsigned)(bytes >> 2);
 }
 unsigned char pad[0x14];
 Rva0020E5BBEntry **first;
 Rva0020E5BBEntry **last;
};
void *Rva0020E5BB::rva0020E5BB(int key)
{
 unsigned index = 0;
 if (key) {
  if (index < count()) {
   Rva0020E5BBEntry **base = first;
   Rva0020E5BBEntry **cursor = base;
   do {
    if ((*cursor)->key == key) return base[index];
    ++index;
    ++cursor;
   } while (index < count());
  }
 }
 return 0;
}
