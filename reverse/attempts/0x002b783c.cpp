// ?rva002B783C@LivingWorldLogic@@QAEHPAULivingWorldArmy@@PAVRva003F287F@@1PAVCoord2D@@@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Integrate into LivingWorldLogic.cpp. Add the member declaration and extend
// Rva003F287F after owner +13C with padding to14C and three Int fields.
// Use existing provider declarations from Rva002B26D0.cpp for the ABI view.
struct RvaFloatPair { float f0, f1; };
struct Rva002B4F6CVector { int *begin, *end, *storageEnd; };
class Rva002B26D0 {
public:
 void rva002B4F6C(Rva002B4F6CVector *ids, RvaFloatPair *out);
};
Int LivingWorldLogic::rva002B783C(LivingWorldArmy *army, Rva003F287F *from, Rva003F287F *to, Coord2D *direction)
{
 if (to != 0 && army != 0) {
  if (from != to) {
   Int steps;
   {
    _STL::vector<Int> path;
    Int result = m_field0B0->ValidateArmyRegionEntry(army,
     (Rva00318C32Ret *)to, (Rva00318C32Ret *)from, (Int)&path, 0);
    if (result < 0 || result > 1) return -1;
    steps = path.size() - 1;
    ((Rva002B26D0 *)this)->rva002B4F6C((Rva002B4F6CVector *)&path, (RvaFloatPair *)direction);
   }
   if (steps <= 1) return from->m_field14C;
   if (steps == 2) return from->m_field150;
   return from->m_field154;
  }
  return from->m_field14C;
 }
 direction->x = 1.0f;
 direction->y = 0.0f;
 return from->m_field154;
}
