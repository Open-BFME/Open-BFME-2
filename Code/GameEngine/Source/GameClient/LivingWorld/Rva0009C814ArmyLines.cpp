// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0009C814@Rva0009C983@@QAEXHPAVRva002E2903Player@@@Z retail
// 0x0009C814..0x0009C983 (367 bytes ret 8). Called only by 0x0009C983 (same
// this; arguments its own argument and the player from
// Rva002BA8F1Logic::rva002B52A8 0x002B52A8) which walks the living-world
// player list. For each army in the player's +0x1B8 vector that
// TheLivingWorldLogic accepts (0x002B269E on army +0x54) and that passes
// 0x00318F42 with an owner from 0x00318FA1 it colours the segmented army
// line at this+0x108 -> +0x1CC: the no-owner colour (owner +0x13C == -1)
// the own colour when the player owns that index (0x002E0BC0) or else the
// other colour (three RGB triples of TheLivingWorldManager's +0x14 block at
// +0xFC/+0x108/+0xF0) via SegmentedLineClass::Set_Color 0x0015E2F0 then
// Set_Points 0x0015F100 with the army's LivingWorldArmyLine (+0x90: count
// and points) and vtable +0x30 with the first argument. No donor or
// WorldBuilder twin; names are address-derived (class from the caller).
#include <vector>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

// The colour temporaries: one stack copy per branch, passed by reference.
struct Rva0009C814Color : Vector3
{
	Rva0009C814Color(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};

class SegmentedLineClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(Int arg); // +0x30
	void Set_Color(const Vector3 &color);
	void Set_Points(UnsignedInt numpoints, Vector3 *locs);
};

class Rva002B269E
{
public:
	bool rva002B269E(Int id);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva0009C814Colors
{
	char m_pad[0xF0];
	Vector3 m_otherColor; // +0xF0 (manager +0x104)
	Vector3 m_noOwnerColor; // +0xFC (manager +0x110)
	Vector3 m_ownColor; // +0x108 (manager +0x11C)
};
struct Rva0009C814ManagerView
{
	char m_pad[0x14];
	Rva0009C814Colors m_colors; // +0x14
};
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva00318F42
{
public:
	bool rva00318F42();
};

class Rva00318FA1MainOwner
{
public:
	Int rva00318FA1();
};

struct Rva0009C814Owner
{
	char m_pad[0x13C];
	Int m_13C; // +0x13C
};

class Rva002E0BC0Helper
{
public:
	unsigned char rva002E0BC0(Int index);
};

struct Rva0009C814ArmyLine
{
	UnsignedInt m_count;
	Vector3 *m_points;
};

struct Rva0009C814Army
{
	char m_pad00[0x54];
	Int m_54; // +0x54
	char m_pad58[0x90 - 0x58];
	Rva0009C814ArmyLine m_line; // +0x90

	const Rva0009C814ArmyLine &getLine() const { return m_line; }
};

class Rva002E2903Player
{
public:
	char m_pad[0x1B8];
	_STL::vector<Rva0009C814Army *> m_armies; // +0x1B8
};

struct Rva0009C814Render
{
	char m_pad[0x1CC];
	SegmentedLineClass *m_line; // +0x1CC
};

class Rva0009C983
{
public:
	void rva0009C814(Int arg, Rva002E2903Player *player);

private:
	char m_pad[0x108];
	Rva0009C814Render *m_108; // +0x108
};

void Rva0009C983::rva0009C814(Int arg, Rva002E2903Player *player)
{
	const _STL::vector<Rva0009C814Army *> &armies = player->m_armies;
	for (UnsignedInt i = 0; i < armies.size(); ++i)
	{
		Rva0009C814Army *army = armies[i];
		if (!reinterpret_cast<Rva002B269E *>(TheLivingWorldLogic)->rva002B269E(army->m_54))
			continue;
		if (!reinterpret_cast<Rva00318F42 *>(army)->rva00318F42())
			continue;
		Rva0009C814Owner *owner = reinterpret_cast<Rva0009C814Owner *>(
			reinterpret_cast<Rva00318FA1MainOwner *>(army)->rva00318FA1());
		if (owner == 0)
			continue;

		const Rva0009C814Colors &colors = reinterpret_cast<Rva0009C814ManagerView *>(TheLivingWorldManager)->m_colors;
		m_108->m_line->Set_Color(owner->m_13C == -1 ? Rva0009C814Color(colors.m_noOwnerColor.X, colors.m_noOwnerColor.Y, colors.m_noOwnerColor.Z)
			: reinterpret_cast<Rva002E0BC0Helper *>(player)->rva002E0BC0(owner->m_13C) ? Rva0009C814Color(colors.m_ownColor.X, colors.m_ownColor.Y, colors.m_ownColor.Z)
			: Rva0009C814Color(colors.m_otherColor.X, colors.m_otherColor.Y, colors.m_otherColor.Z));
		const Rva0009C814ArmyLine &line = army->getLine();
		m_108->m_line->Set_Points(line.m_count, line.m_points);
		m_108->m_line->slot12(arg);
	}
}
