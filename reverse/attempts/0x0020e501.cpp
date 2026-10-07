// ?rva0020E501@Rva0020E5BB@@QAEPAXH@Z
// partial score=0.75 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
struct Rva0020EQueryEntry { char pad[0x24]; void *word24; char gap[8]; int word30; };
class Rva0020E5BB {
public:
 void *rva0020E501(int key);
 void *rva0020E57F(void *key);
 __forceinline unsigned count() const {
  int bytes=(int)((const volatile Rva0020E5BB *)this)->last;
  bytes-=(int)((const volatile Rva0020E5BB *)this)->first;
  return (unsigned)(bytes>>2);
 }
 char pad[0x14]; Rva0020EQueryEntry **first,**last;
};
void *Rva0020E5BB::rva0020E501(int key)
{
 unsigned index=0;
 if (index<count()) {
  Rva0020EQueryEntry **base=first;
  Rva0020EQueryEntry **cursor=base;
  do {
   if (((const volatile Rva0020EQueryEntry *)*cursor)->word30 == key) return base[index];
   ++index;
   ++cursor;
  } while(index<count());
 }
 return 0;
}
void *Rva0020E5BB::rva0020E57F(void * key)
{
 unsigned index=0;
 if (index<count()) {
  Rva0020EQueryEntry **base=first;
  Rva0020EQueryEntry **cursor=base;
  do {
   if (((const volatile Rva0020EQueryEntry *)*cursor)->word24 == key) return base[index];
   ++index;
   ++cursor;
  } while(index<count());
 }
 return 0;
}
