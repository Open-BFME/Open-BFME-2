// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
struct Coord3D
{
	float x;
	float y;
	float z;
};

// The same complete victim pointer is passed to Weapon as Object and to
// native getter 0x28B511. The verified const getter reads flag +0x48C and
// layer word +0x40C; its purpose and declaration follow that existing owner.
class Object
{
public:
	int rva0028B511() const;
};

class Weapon
{
public:
	Coord3D bfmeGetLOSVictimPos(const Object *shooter, const Object *victim, int mode) const;
};

class BfmeHolderNS;

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0AAE();
	virtual void bfmeSlot1AAE();
	virtual void bfmeSlot2AAE();
	virtual void bfmeSlot3AAE();
	virtual void bfmeSlot4AAE();
	virtual void bfmeSlot5AAE();
	virtual void bfmeSlot6AAE();
	virtual float bfmeHeightAAE(float x, float y, int layer, int a, int b);
};

// Retail 0x012EF4CC is EA's singleton; only its type spelling matters for the
// mangled name, so this TU declares it canonically and keeps its own TU-local
// view of the vtable for the members it touches.
class TerrainLogic;

extern TerrainLogic *TheTerrainLogic;

class BfmeAimAAE
{
public:
	virtual void bfmeSlotA0AAE();
	virtual void bfmeSlotA1AAE();
	virtual void bfmeSlotA2AAE();
	virtual void bfmeSlotA3AAE();
	virtual void bfmeSlotA4AAE();
	virtual void bfmeSlotA5AAE();
	virtual void bfmeAimAtAAE(Weapon *weapon, const Coord3D *pos);

	void bfmeFireAAE(Weapon *weapon, BfmeHolderNS *victim);
};

void BfmeAimAAE::bfmeFireAAE(Weapon *weapon, BfmeHolderNS *victim)
{
	Coord3D pos = weapon->bfmeGetLOSVictimPos(0, (const Object *)victim, 1);

	pos.z = ((Rva003FD060TerrainLogic *)TheTerrainLogic)->bfmeHeightAAE(pos.x, pos.y, reinterpret_cast<const Object *>(victim)->rva0028B511(), 0, 1);

	bfmeAimAtAAE(weapon, &pos);
}
