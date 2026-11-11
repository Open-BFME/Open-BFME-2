// WeaponTemplateTargetPositions.cpp -- WeaponTemplate target-position helpers.
// ?adjustTargetPositionOnVictim@WeaponTemplate@@QAE?AUTargetCoord@@PAVObject@@0_N@Z @0x002CAB3A 308B;
// WB 0xBB2780 supplies the branch order, the clamp temporary and the argument
// evaluation order: the jitter call is an ARGUMENT of getWorldspaceBestContactPoint
// (inline form), which is what makes cl push the trailing false before it, and the
// outer no-clamp arm reads pos.z through a volatile cast to keep its own add path
// (retail 0x2CAC43: movss pos.z / addss offset) instead of merging with the clamp arm.
// Landed byte-exact 308/308 in the owner TU; the Rva002CAAFA helper row is unchanged.
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Matrix3D;
struct ThingKindBytes;
enum ObjectStatusTypes { OBJECT_STATUS_PLACEHOLDER = 0 };
typedef bool Bool;
typedef float Real;
class Object {
public:
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
 bool testStatus(ObjectStatusTypes) const;
 bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
 char m_pad[4];
 ThingKindBytes *m_template; // +0x04
 char m_pad08[0x38-0x08];
 Coord3D m_position; // +0x38
};
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

// ---- caller 0x002CAB3A: ?adjustTargetPositionOnVictim@WeaponTemplate@@QAEXPAUCoord3D@@PAVObject@@0_N@Z
// Retail 0x2CAB3A..0x2CAC6B RET0x10; WB 0xBB2780 gives the branch order.
// victim==0 -> out (0,0,0); else the logical-bone helper fills pos; else the
// flagged path asks the victim for its worldspace best contact point with a
// GetGameLogicRandomValue jitter, and the plain path copies the victim's
// position and clamps a +0xA8 float offset by GlobalData::m_clampedLOSHeightForCastleStructures when the
// victim template is structure-kind, the source template lacks kind byte
// +0x109 bit 8 and neither object carries status 0x55.
struct ThingKindBytes
{
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];	// template +0x108; [0] bit 0x80 STRUCTURE, [1] bit 0x08
};

int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

#include "../../../Include/GameLogic/Module/Rva0073A1C0FloatField.h"

#include "../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

struct TargetCoord
{
public:
	TargetCoord() {}
	TargetCoord(float a,float b,float c):x(a),y(b),z(c){}
	TargetCoord(const Coord3D &p):x(p.x),y(p.y),z(p.z){}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};

#include "../../../Include/GameLogic/WeaponTemplate.h"

TargetCoord WeaponTemplate::adjustTargetPositionOnVictim(Object *source, Object *victim, Bool flag)
{
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	if (victim == 0)
		return TargetCoord(0.0f, 0.0f, 0.0f);

	if (((Rva002CAAFA *)this)->rva002CAAFA(victim, &pos))
		return pos;

	if (flag)
	{
		victim->getWorldspaceBestContactPoint(&pos, &source->m_position, 0, 3,
			GetGameLogicRandomValue(0, 12345678,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp",
			0x6D5), false);
	}
	else
	{
		pos = victim->m_position;
		Real offset = ((Rva0073A1C0FloatField *)((char *)victim + 0xa8))->get();
		if ((victim->m_template->m_kindOf[0] & 0x80) != 0 &&
			(source->m_template->m_kindOf[1] & 0x08) == 0 &&
			!source->testStatus((ObjectStatusTypes)0x55) &&
			victim->testStatus((ObjectStatusTypes)0x55))
		{
			if (offset > TheWritableGlobalData->m_clampedLOSHeightForCastleStructures)
				pos.z = TheWritableGlobalData->m_clampedLOSHeightForCastleStructures + pos.z;
			else
				pos.z = pos.z + offset;
		}
		else
		{
			pos.z = *(volatile Real*)&pos.z + offset;
		}
	}

	return pos;
}
