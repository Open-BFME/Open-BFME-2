// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native3FC149..3FC291 RET4,328B; WB10705B0 has the same transform
// copy, Set_Rotation711EF0, scale and virtual21 calls. Sole known direct
// native caller is the existing guarded wrapper3F935A,20B. Retain its
// established neutral U4Target0060C2C0::hand(void*) ABI/name; original class
// and method identity remain unknown. Payload is read as the evidenced
// Matrix3 reference; render-object views use target slots20/21 and offsets.
// Genuine row/transform copy and column Scale structure are shared with
// the verified LivingWorldVisual transform-family source. Scalar factor
// by value reproduces full328B including retail's first MOVSS/MULSS pair.
// No aliases, extra pins, canonical math definitions or assembly added.
typedef float Real;

class Matrix3D;

#include "../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"





class U4Target0060C2C0
{
public:
	void hand( void *payload );
private:
 unsigned char unknown0[8]; RenderObjClass *primary; unsigned char unknownC[8]; RenderObjClass *secondary;
};

#include "../../Include/Common/LivingWorldEyeTower.h"

// Both retail callers reload ECX with the eye tower, then pass target and payload.
// The receiver is unused; native3F935A..3F936E remains20B RET8.
void LivingWorldEyeTower::rva003F935A(U4Target0060C2C0 *target, void *payload)
{
	if ( target != 0 )
		target->hand( payload );
}

void U4Target0060C2C0::hand(void *payload) {
 if(primary){
 Matrix3D tm=primary->Get_Transform();
 tm.Set_Rotation(*static_cast<const Matrix3*>(payload));
 // The public scale accessor supplies the factor for the transform's columns.
 Real factor=primary->Get_ObjectScale();
 tm.Scale(factor);
 primary->Set_Transform(tm);
 if(secondary)secondary->Set_Transform(tm);
 }
}
