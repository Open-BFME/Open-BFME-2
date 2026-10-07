// ?rva003980BF@Rva003980BF@@QAEPAXPAXHH@Z
// partial score=0.94 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /MD
// stlport
#include <vector>
typedef std::vector<unsigned> Rva003980BFIds;
struct Rva003980BFFlags
{
 unsigned char pad[0x110];
 unsigned char flags;
};
void *__cdecl rva00397FEB(void *context, unsigned id, void *target, int mode);
class Rva003980BF
{
public:
 void *rva003980BF(void *target, int which, int mode);
 unsigned char pad0[0x38];
 void *context;
 unsigned char pad3C[0x50 - 0x3C];
 Rva003980BFIds normal;
 unsigned char pad5C[0x74 - 0x5C];
 Rva003980BFIds alternate;
};
void *Rva003980BF::rva003980BF(void *target, int which, int mode)
{
 if (!target) return target;
 Rva003980BFIds *ids = &normal;
 if ((((Rva003980BFFlags *)target)->flags & 1) && alternate.size() != 0)
  ids = &alternate;
 if (which == -2)
 {
  for (unsigned *p = ids->begin(); p != ids->end(); ++p)
  {
   unsigned id = *(const volatile unsigned *)p;
   void *result = rva00397FEB(context, id, target, mode);
   if (result) return result;
  }
 }
 else
 {
  unsigned count = ids->size();
  if (count)
  {
   if ((unsigned)which > count - 1) which = count - 1;
   else if (which < 0) which = 0;
   unsigned id = *(const volatile unsigned *)&(*ids)[which];
   void *result = rva00397FEB(context, id, target, mode);
   if (result) return result;
  }
 }
 return 0;
}
