// cl: /O1 /MD /DNDEBUG
//
// Player's AI delegates, ported from Zero Hour's
// GameEngine/Source/Common/RTS/Player.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//   Player::computeSuperweaponTarget  0x002A9B92  43 bytes  (slot 4)
//   Player::checkBridges              0x002A9C0D  25 bytes  (slot 5)
//   Player::getAiBaseCenter           0x002A9C26  34 bytes  (slot 6)
//   Player::repairStructure           0x002A9C48  23 bytes  (slot 7)
// Identity: slots 4-7 of vtable 0x00BFDF3C, whose unique slot-2 name getter
// returns "Player" (slot 0 is the rowed ??_GPlayer). Zero Hour declares
// exactly these four virtuals, in this order, after Snapshot's three.
// Layout (target evidence): m_ai at Player +0x2DC; AIPlayer's
// computeSuperweaponTarget, checkBridges and repairStructure are its vtable
// slots 4, 13 and 14; its inline getBaseCenter reads m_baseCenter (+0x34)
// and m_baseCenterSet (+0x40).
// BFME 2 difference: computeSuperweaponTarget returns nothing (retail leaves
// EAX unset when there is no AI), so it is declared void here.

typedef bool Bool;
typedef int Int;
typedef float Real;
enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3D
{
	Real x, y, z;
};
class SpecialPowerTemplate;
class Object;
class Waypoint;

class AIPlayer
{
	friend class Player;
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *pos, Int playerNdx, Real weaponRadius);
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual Bool checkBridges(Object *unit, Waypoint *way);
	virtual void repairStructure(ObjectID structure);
	Bool getBaseCenter(Coord3D *pos) const {*pos = m_baseCenter; return m_baseCenterSet;}
protected:
	Bool rva004F2BEE(Int minimumCash);
private:
	unsigned char m_pad04[0x34 - 0x04];
	Coord3D m_baseCenter; // +0x34
	Bool m_baseCenterSet; // +0x40
};

class Player
{
public:
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius);
	virtual Bool checkBridges(Object *unit, Waypoint *way);
	virtual Bool getAiBaseCenter(Coord3D *pos);
	virtual void repairStructure(ObjectID structureID);
	Bool rva002A9CA4(Int minimumCash);
private:
	unsigned char m_pad04[0x2DC - 0x04];
	AIPlayer *m_ai; // +0x2DC
};

//----------------------------------------------------------------------------------------------------------
/**
 * Find a good spot to fire a superweapon.
 */
void Player::computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius)
{
	if (m_ai) {
		m_ai->computeSuperweaponTarget(power, retPos, playerNdx, weaponRadius);
	}
}

//-------------------------------------------------------------------------------------------------
/** Do any bridges need repair, and if so repair them. */
//-------------------------------------------------------------------------------------------------
Bool Player::checkBridges(Object *unit, Waypoint *way)
{
	return m_ai?m_ai->checkBridges(unit, way):false; 
}

//-------------------------------------------------------------------------------------------------
/** Do any bridges need repair, and if so repair them. */
//-------------------------------------------------------------------------------------------------
Bool Player::getAiBaseCenter(Coord3D *pos)
{
	return m_ai?m_ai->getBaseCenter(pos):false; 
}

//-------------------------------------------------------------------------------------------------
/** Repair bridge or structure. */
//-------------------------------------------------------------------------------------------------
void Player::repairStructure(ObjectID structureID)
{
	if (m_ai) 
	{
		m_ai->repairStructure(structureID); 
	}
}

// ?rva002A9CA4@Player@@QAE_NH@Z @ 0x002A9CA4 20B: Player AI delegate defaulting
// to true. Evidence: ecx is Player* from getEachPlayerFromMask in caller
// 0x003E4A63 which pushes [param+8] as int and tests al; m_ai at +0x2DC like
// siblings; tail-jmps to rowed ?rva004F2BEE@AIPlayer@@IAE_NH@Z when present.
Bool Player::rva002A9CA4(Int minimumCash)
{
	return m_ai ? m_ai->rva004F2BEE(minimumCash) : true;
}
