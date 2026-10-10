// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
class Matrix3D;
class Object {public:bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;};
class Rva002CAAFA {
public:bool rva002CAAFA(Object *victim,Coord3D *out);
private:char unknown00[0x90];AsciiString bone;
};
// Target002CAAFA..002CAB3A: the WeaponTemplate caller supplies this and
// victim/output; native +90 StringBase and logical-bone query fix the layout.
// The old neutral ABI view name is preserved; original helper name unknown.
// ?rva002CAAFA@Rva002CAAFA@@QAE_NPAVObject@@PAUCoord3D@@@Z
bool Rva002CAAFA::rva002CAAFA(Object *victim,Coord3D *out)
{
 if(!bone.isEmpty()){
  if(victim->getSingleLogicalBonePosition(bone.str(),out,0))return true;
 }
 return false;
}
