// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?bfmeCalcScatterTargetPos@WeaponTemplate@@QAE?AUCoord3D@@PBVObject@@0U2@@Z
// retail 0x002CB679, 582 bytes (ret 0x18: hidden result, source, victim and a
// Coord3D by value). The name is invented; the body is BFME 2 only.
//
// Target evidence: the scatter radius at this+0x34 is widened by the infantry
// inaccuracy distance at this+0x14C for a KindOf bit 8 (INFANTRY) victim, as
// Zero Hour's fireWeaponTemplate does, and randomized between it and the
// victim's bounding circle radius (Object +0xB8) plus 5.0 through
// GetGameLogicRandomValueReal (Weapon.cpp line 0x659). A STRUCTURE victim is
// aimed at through the rowed getAimPosition (0x002CAB3A, slot 1). With a
// victim the angle is the normalized source-minus-victim direction (a z-less
// Vector3 through WWMath Inv_Sqrt, whose 12-byte frame slot it shares with the
// aim position and the Coord3D offset; atan2f) +- pi/2 (line 0x667), without
// one 0..2pi (line 0x66B); the result is pos + radius * (Cos, Sin). The z then comes from the victim's
// position for KindOf bit 55, else from TheTerrainLogic->getLayerHeight
// (vtable +0x1C) on the layer from the rowed Object getter 0x0028B511 (or
// TheTerrainLogic->getLayerForDestination without a victim) when the victim's
// AI reports isDoingGroundMovement (slot 137, +0x224).

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's user copy constructor; retail returns pos into the hidden result with three movss pairs and both callers (0x002CC0E6 and 0x002CC16A) copy-construct the by-value argument and record its address for unwinding; same three floats
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
	Real x, y, z;
};

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real val);
};

class Vector3
{
public:
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline void Normalize()
	{
		Real len2 = X * X + Y * Y + Z * Z;
		if (len2 != 0.0f)
		{
			Real oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	Real X, Y, Z;
};

extern "C" float __cdecl atan2f(float y, float x);
Real Cos(Real x);
Real Sin(Real x);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

#define WEAPON_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp"

class Object;

class TerrainLogic
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

class AIUpdateInterface
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007();
	virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027();
	virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031();
	virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043();
	virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051();
	virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055();
	virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063();
	virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067();
	virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071();
	virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075();
	virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083();
	virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087();
	virtual void s088(); virtual void s089(); virtual void s090(); virtual void s091();
	virtual void s092(); virtual void s093(); virtual void s094(); virtual void s095();
	virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111();
	virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115();
	virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123();
	virtual void s124(); virtual void s125(); virtual void s126(); virtual void s127();
	virtual void s128(); virtual void s129(); virtual void s130(); virtual void s131();
	virtual void s132(); virtual void s133(); virtual void s134(); virtual void s135();
	virtual void s136();
	virtual Bool isDoingGroundMovement() const; // +0x224
};

class ThingTemplate
{
public:
	// KindOf words: 0x80 STRUCTURE in word 0; 0x100 INFANTRY in word 0;
	// 0x800000 (bit 55) in word 1.
	UnsignedInt testKindOf(Int word, UnsignedInt mask) const { return m_kindOf[word] & mask; }
private:
	char m_pad000[0x108];
	UnsignedInt m_kindOf[4]; // +0x108
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Int rva0028B511() const;
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +4
	char m_pad008[0x38 - 0x08];
	Coord3D m_cachedPos; // +0x38
	char m_pad044[0xB8 - 0x44];
	Real m_boundingCircleRadius; // +0xB8 (geometry info)
	char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *result, const Object *source, const Object *victim, Int weaponSlot);
	Coord3D bfmeCalcScatterTargetPos(const Object *source, const Object *victim, Coord3D pos);
private:
	char m_pad000[0x34];
	Real m_scatterRadius; // +0x34
	char m_pad038[0x14C - 0x38];
	Real m_infantryInaccuracyDist; // +0x14C
};

//-------------------------------------------------------------------------------------------------
Coord3D WeaponTemplate::bfmeCalcScatterTargetPos(const Object *source, const Object *victim, Coord3D pos)
{
	Real minRadius = victim ? victim->getBoundingCircleRadius() + 5.0f : 0.0f;
	Real scatterRadius = m_scatterRadius;
	PathfindLayerEnum layer;

	if (victim)
	{
		if (victim->getTemplate()->testKindOf(0, 0x80))
		{
			Coord3D aim;
			pos = *getAimPosition(&aim, source, victim, 1);
		}
		if (m_infantryInaccuracyDist > 0.0f && victim->getTemplate()->testKindOf(0, 0x100))
			scatterRadius += m_infantryInaccuracyDist;
		layer = (PathfindLayerEnum)victim->rva0028B511();
	}
	else
	{
		layer = TheTerrainLogic->getLayerForDestination(0, &pos);
	}

	Real radius;
	if (scatterRadius > minRadius)
		radius = GetGameLogicRandomValueReal(minRadius, scatterRadius, WEAPON_CPP, 0x659);
	else
		radius = scatterRadius;

	Real angle;
	if (victim)
	{
		Vector3 dir(source->getPosition()->x - victim->getPosition()->x,
			source->getPosition()->y - victim->getPosition()->y, 0.0f);
		dir.Normalize();
		Real dirAngle = atan2f(dir.Y, dir.X);
		angle = GetGameLogicRandomValueReal(dirAngle - 1.5707964f, dirAngle + 1.5707964f, WEAPON_CPP, 0x667);
	}
	else
	{
		angle = GetGameLogicRandomValueReal(0.0f, 6.2831855f, WEAPON_CPP, 0x66B);
	}

	Coord3D offset;
	offset.x = radius * Cos(angle);
	offset.y = radius * Sin(angle);
	pos.x += offset.x;
	pos.y += offset.y;

	if (victim)
	{
		if (victim->getTemplate()->testKindOf(1, 0x800000))
		{
			pos.z = victim->getPosition()->z;
		}
		else
		{
			AIUpdateInterface *ai = victim->getAI();
			if (ai && ai->isDoingGroundMovement())
				pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
		}
	}

	return pos;
}
