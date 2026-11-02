// cl: /GX /MD /DNDEBUG
// TU Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior.cpp:
// native seed of retail's SlowDeathBehavior.cpp (approved rows 0x0045D3C5..
// 0x0045E93F and their funclets in tu_map.csv). The approved bodies still
// live in one-function donors; tools/tu_skeleton.py --merge brings them in.
//
// The Zero Hour port that used to seed this unit is gone. None of its
// unrowed bodies matched retail:
// - ~SlowDeathBehavior: retail's destructor is rowed at 0x0045D39E, its
//   deleting destructor at 0x0045D5BE (slot 0 of the primary table 0x00C42040
//   that the rowed ctor 0x0045D4B4 installs), both in
//   Common/Rva0024A797Grandchildren.cpp;
// - crc and loadPostProcess: slot 1 of 0x00C42040 is the shared 0x00497805
//   body, slots 2-4 are the rowed GetSnapshotName 0x0045D3C5, xfer 0x0045D3CB
//   and getModuleNameKey 0x0045D459; nothing in this TU's range is a
//   SlowDeathBehavior crc or loadPostProcess;
// - parseFX/parseOCL/parseWeapon and calcRandomForce: rowed at 0x0045E533,
//   0x0045E5A4, 0x0045E618 (SlowDeathBehaviorParsers.cpp) and 0x0045D636
//   (SlowDeathRandomForceRva0045D636.cpp).

typedef float Real;

// PhysicsBehavior's two extra-damping setters are out-of-line COMDATs this
// unit has always emitted (rows 0x000EFB3E and 0x000EFB5A, 14 B each:
// movss xmm0,[esp+4]; movss [ecx+0x74]/[ecx+0x78],xmm0; ret 4). They have no
// approved TU (tu_map: displaced) and no direct retail callers, so they stay
// with their file. Only the two members they write are modelled.
class PhysicsBehavior
{
public:
	void setExtraBounciness(Real bounciness) { m_extraBounciness = bounciness; }
	void setExtraFriction(Real friction) { m_extraFriction = friction; }

private:
	unsigned char m_pad00[0x74];
	Real m_extraBounciness; // +0x74
	Real m_extraFriction; // +0x78
};

// Taking the setters' addresses keeps their out-of-line copies.
void (PhysicsBehavior::*_bfmeInlineAnchor_SlowDeathBehavior_0)(Real) = &PhysicsBehavior::setExtraBounciness;
void (PhysicsBehavior::*_bfmeInlineAnchor_SlowDeathBehavior_1)(Real) = &PhysicsBehavior::setExtraFriction;
