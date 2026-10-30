// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2
// ?getSingleLogicalBonePositionOnTurret@Object@@QBE_NW4WhichTurretType@@PBDPAUCoord3D@@PAVMatrix3D@@@Z
// Retail 0x0028E1AC..0x0028E58E (994 bytes), complete RET 16 body.
// ZH GeneralsMD Object.cpp getSingleLogicalBonePositionOnTurret (lines 6035-6081)
// is the semantic guide; reference/open-bfme-1 at cee35b7d8 supplies WWMath.
// Target calls its pristine-bone/launch-offset queries, turret rotation query,
// and Thing's world transform converter, independently supporting identity.
// Retail reads Drawable +0x84 and AI +0x258 before the guard (existing Object
// views agree); matrix/vector arithmetic and all four direct callbacks agree.
// The launch-offset callback uses its byte-verified typed Drawable owner.
// Native and WB independently establish its six-argument pointer/enum ABI.
// A const-reference Vector3 temporary preserves native Y/Z register allocation;
// constructing the output Coord3D within its guard preserves target copy order.

#include "Lib/Coord3D.h"
#include "matrix3d.h"
enum WhichTurretType {TURRET_PRIMARY=0};
enum WeaponSlotType {PRIMARY_WEAPON=0};
#include "../../../Include/GameClient/DrawableBFME2.h"
class AIUpdateInterface {public:bool getTurretRotAndPitch(WhichTurretType,float*,float*)const;};
class Object {public:
 char pad00[0x84];Drawable*draw;char pad88[0x258-0x88];AIUpdateInterface*ai;
 bool getSingleLogicalBonePositionOnTurret(WhichTurretType,const char*,Coord3D*,Matrix3D*)const;
};
bool Object::getSingleLogicalBonePositionOnTurret(WhichTurretType which,const char*name,Coord3D*position,Matrix3D*transform)const {
 Coord3D turretPosition,bonePosition;
 AIUpdateInterface *aiLocal=ai;Drawable *drawable=draw;
 if(!drawable || !aiLocal)return false;
 drawable->getProjectileLaunchOffset(PRIMARY_WEAPON,1,0,which,&turretPosition,0);
 if(drawable->getPristineBonePositions(name,0,&bonePosition,0,1,0)!=1)return false;
 float rotation;
 aiLocal->getTurretRotAndPitch(which,&rotation,0);
 Matrix3D boneOffset(true);
 const Vector3&boneVector=Vector3(bonePosition.x,bonePosition.y,bonePosition.z);
 boneOffset.Translate(boneVector);
 Matrix3D turn(true);
 turn.Translate(turretPosition.x,turretPosition.y,turretPosition.z);
 turn.In_Place_Pre_Rotate_Z(rotation);
 turn.Translate(-turretPosition.x,-turretPosition.y,-turretPosition.z);
 Matrix3D logic;logic.mul(turn,boneOffset);
 Matrix3D world;
 ((const Thing*)this)->convertBonePosToWorldPos(0,&logic,0,&world);
 Vector3 tmp=world.Get_Translation();
 if(position){Coord3D worldPos;worldPos.x=tmp.X;worldPos.y=tmp.Y;worldPos.z=tmp.Z;*position=worldPos;}
 if(transform)*transform=world;
 return true;
}
