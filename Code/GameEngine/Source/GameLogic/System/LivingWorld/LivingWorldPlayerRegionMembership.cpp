// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native002E0B76..002E0BC0 RET4,74B: scans LivingWorldPlayer's army
// vector1B8, as independently identified in neighboring70B predicate
// 002E0B30 and named RemoveArmy2E10FE. Native compares each pointer
// returned by318C32 with the input. That provider ABI and the repaired
// 87B pointer-return20FAEA agree. Original method spelling remains unknown.
// The home unit is held by another seat; this declaration-only layout view
// adds no constructor, inline helper, vtable or by-value ABI.
#include <vector>
class Rva00318C32Ret;
class Rva00318C79Owner { public: Rva00318C32Ret *rva00318C32(); };
class LivingWorldPlayer {
public:
 bool rva002E0B76(Rva00318C32Ret *region);
private:
 char unknown00[0x1B8];
 _STL::vector<void *> m_armyVec;
};
bool LivingWorldPlayer::rva002E0B76(Rva00318C32Ret *region)
{
 for(unsigned int i=0;i<m_armyVec.size();++i) {
  if(reinterpret_cast<Rva00318C79Owner *>(m_armyVec[i])->rva00318C32()==region)
   return true;
 }
 return false;
}
