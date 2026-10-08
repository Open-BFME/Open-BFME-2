// ?rva005ABCFE@AIStructureCreepTactic@@QAE_NPAUCoord3DBase@@ABVAsciiString@@@Z
// partial score=0.69 date=2026-10-09
// Bank: AIStructureCreepTactic::getBuildPos (WB 0x015215B0), retail 0x005ABCFE 420B.
// Append to Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/
// TargetlessTactics/AIStructureCreepTactic.cpp (declared there as rva005ABCFE).
// Logic and callees match (record 0x2A8AB1, getMyZone, 0x4EBF4B centre, inline Vector3
// Normalize via WWMath::Inv_Sqrt, TerrainLogic slot 6, ThingFactory lookup, BuildAssistant
// slot 16 with options 0x85 and the owner). Remaining: SSE register numbering of the
// centre/base vectors, retail keeps Inv_Sqrt's result on the x87 stack for all three
// multiplies (fstp st(0) after), and the owner is loaded into ebx before the template lookup.
// Best similarity 0.69.
// TheTerrainLogic slot 6 and TheBuildAssistant slot 16 views (as in
// AIBuildableStructure.cpp).
class TerrainLogic {
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5();
	virtual float groundHeight(float x, float y, int normal);
};
extern TerrainLogic *TheTerrainLogic;
class ThingTemplate;
class BuildAssistantCallView {
public:
#define SLOT(n) virtual void s##n();
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
	virtual int checkPosition(const Coord3D *pos, const ThingTemplate *thing, float angle, int options, Object *builder, Player *player);
};
class BuildAssistant;
extern BuildAssistant *TheBuildAssistant;

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float value);
};

// WWMath's inline Vector3 operations (Length2, Normalize via Inv_Sqrt).
struct BfmeVector3
{
	BfmeVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	BfmeVector3(const Coord3DBase &c) : X(c.x), Y(c.y), Z(c.z) {}
	BfmeVector3 operator-(const BfmeVector3 &b) const { return BfmeVector3(X - b.X, Y - b.Y, Z - b.Z); }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f) {
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	float X, Y, Z;
};



// Native 005ABCFE..005ABEA2, RET8 (WorldBuilder twin 0x015215B0 names it
// AIStructureCreepTactic::getBuildPos). The candidate is the creep zone's
// centre moved half the zone radius toward the record's reference point
// (0x004EBF4B), dropped to the ground; it is accepted when the build
// assistant's slot 16 check passes for the named template.
bool AIStructureCreepTactic::rva005ABCFE(Coord3DBase *out, const AsciiString &name)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	Player *zoneOwner = m_owner;
	Rva005ABEA2Site *site = getMyZone(zoneOwner, m_68);
	BfmeVector3 center = ((Rva004EBF4B *)record)->rva004EBF4B();
	BfmeVector3 base = site->m_pos;
	BfmeVector3 dir = center - base;
	dir.Normalize();
	float half = site->m_radius * 0.5f;
	dir.X *= half;
	dir.Y *= half;
	dir.Z *= half;
	Coord3D pos;
	pos.x = site->m_pos.x + dir.X;
	pos.y = site->m_pos.y + dir.Y;
	pos.z = site->m_pos.z + dir.Z;
	pos.z = TheTerrainLogic->groundHeight(pos.x, pos.y, 0);
	Player *owner = m_owner;
	const ThingTemplate *thing = (const ThingTemplate *)TheThingFactory->rva002D06CA(&name);
	if (((BuildAssistantCallView *)TheBuildAssistant)->checkPosition(&pos, thing, 0.0f, 0x85,
			TheGameLogic->findObjectByID(m_58), owner) == 0) {
		*out = pos;
		return true;
	}
	return false;
}
