// ?doSpecialPowerAtLocation@DevastateSpecialPower@@UAEXPBUCoord3D@@I@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004C82E5, 472B: DevastateSpecialPower::doSpecialPowerAtLocation,
// entered through the SpecialPowerModuleInterface at +0x10 (module data
// this-0x0C, object this-0x08).
// Native special-power secondary table C5E430 (ctor4C81E3) independently
// puts this override in slot12 at complete-object+10. The Money accessed
// extent is12 bytes from its own188B provider; the following Player gap is
// adjusted accordingly. The original tracker extent remains unknown.
// A same-valued target conditional on the selected bounty preserves the
// native LEA EAX / PUSH EAX at8466/846E without changing the value.
// Body: the BFME 1 port of the same override (reference/open-bfme-1/game/
// GameEngine/Source/GameLogic/Object/SpecialPower/
// DevastateSpecialPowerDoSpecialPowerAtLocation.cpp, retail 0x0025A9D0
// there): refuse while disabled (Object+0x1C8 BitFlags<11>::any) or without
// a location/player, chain to SpecialPowerModule::doSpecialPowerAtLocation,
// then drain the terrain query (0x0027F108 with the module data radius at
// +0x7C) with TheTerrainLogic+0x1918 set to 0.1: unblock (0x0028447F) unless
// the thing's +0x18 flag is set, play the FX (+0x80) at it, and turn its
// value (0x0027D378, limit 99999) times the player's supply value
// (0x002A9DAC) into a bounty, scaled in multiplayer by the per-player-count
// money multiplier and by Player::ScaleMoney, times +0x84. The total, capped
// at +0x88 by a reference min, is deposited (player +0x90 / +0x3BC); BFME 2
// drops the score-keeper add and instead fires the weapon named at +0x8C at
// the location. Three callees rowed as free functions are reached with ECX
// loaded (TheTerrainLogic / the player), so they are called through
// thiscall placeholder spellings pinned to the same bodies.

#include "ascii_string.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D;
class Object;
class WeaponTemplate;
class Matrix3D;

#include "../../../../Include/Common/BitFlagsTemplate.h"

class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx = 0, const Real primarySpeed = 0.0f,
		const Coord3D *secondary = 0 );
};

class BfmeX1035
{
public:
	unsigned char m_pad00[0x18];
	unsigned char m_flag18;
};

// The three TerrainLogic helpers this unit calls are rowed in their home
// units; declare those identities so the references resolve at link time.
// Rva0027D378Finish.cpp owns ?rva0027D378@Rva0027D378@@QAEHPAXH@Z,
// BfmeConv624.cpp owns ?rva0027F108@BfmeThingCME@@QAEHPAXMHH@Z.
class Rva0027D378
{
public:
	int rva0027D378( void *thing, int limit );
};

#include "../../../../Include/GameLogic/Module/BfmeThingCME.h"

// 0x0028447F's rowed body is the stdcall ?bfmeGo1035C@@YGXPAVBfmeX1035@@H@Z
// (BfmeConv1035.cpp); retail's call site here passes TerrainLogic in ecx
// which the body ignores, so bind this unit's member spelling to that body.
#pragma comment(linker, "/alternatename:?rva0028447F@Rva004C82E5Terrain@@QAEXPAVBfmeX1035@@PBUCoord3D@@@Z=?bfmeGo1035C@@YGXPAVBfmeX1035@@H@Z")

class Rva004C82E5Terrain
{
public:
	BfmeX1035 *rva0027F108( const Coord3D *target, Real radius, Int a, Int b );
	void rva0028447F( BfmeX1035 *thing, const Coord3D *target );
	Int rva0027D378( BfmeX1035 *thing, Int limit );
	unsigned char m_pad00[0x1918];
	Real m_queryScratch;
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

#include "../../../../Include/Common/Rva0039B7AD.h"

class Rva003B0D7C
{
public:
	void rva003B0D7C( int amount, Rva0039B7AD *score, bool flag );
	char m_pad[12];
};

#include "../../../../Include/Common/Player.h"

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[0x1C8];
	BitFlags<11> m_disabledMask;
};

#include "../../../../Include/Common/BfmeGlob939D.h"

class GameLogic;
extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

#include "../../../../Include/Common/MultiPlayMults.h"

class Rva004C82E5GlobalData
{
public:
	char m_pad000[0xEC4];
	MultiPlayMults m_multiPlayMults;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

#include "../../../../Include/GameLogic/WeaponStore.h"

extern WeaponStore *TheWeaponStore;

class DevastateSpecialPowerModuleData
{
public:
	unsigned char m_pad00[0x7C];
	Real m_radius;
	const FXList *m_fx;
	Real m_bountyScale;
	Real m_bountyCap;
	AsciiString m_weaponName;
};

template <class T> inline const T &devastateMin( const T &a, const T &b )
{
	return b < a ? b : a;
}

#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class BehaviorModuleView
{
public:
	virtual ~BehaviorModuleView();
protected:
	const DevastateSpecialPowerModuleData *getDevastateSpecialPowerModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const DevastateSpecialPowerModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x10 - 0x0C];
};

class SpecialPowerModule : public BehaviorModuleView, public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtLocation( const Coord3D *loc, UnsignedInt commandOptions );
};

static __forceinline UnsignedInt devastateMoneyAmount(Real value) {return (UnsignedInt)value;}

class DevastateSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtLocation( const Coord3D *loc, UnsignedInt commandOptions );
};

void DevastateSpecialPower::doSpecialPowerAtLocation( const Coord3D *target, UnsignedInt commandOptions )
{
	Real money;
	Object *owner = getObject();
	Player *player;

	if( owner->m_disabledMask.any() )
		return;

	if( target == 0 )
		return;

	player = owner->getControllingPlayer();
	if( player == 0 )
		return;

	SpecialPowerModule::doSpecialPowerAtLocation( target, commandOptions );

	const DevastateSpecialPowerModuleData *data = getDevastateSpecialPowerModuleData();
	reinterpret_cast<Rva004C82E5Terrain *>(TheTerrainLogic)->m_queryScratch = 0.1f;
	money = 0.0f;

	BfmeX1035 *thing;
	while( ( thing = (BfmeX1035 *)reinterpret_cast<BfmeThingCME *>(TheTerrainLogic)->rva0027F108( (void *)target, data->m_radius, 0, 2 ) ) != 0 )
	{
		if( thing->m_flag18 == 0 )
			reinterpret_cast<Rva004C82E5Terrain *>(TheTerrainLogic)->rva0028447F( thing, target );

		if( data->m_fx )
			FXList::doFXPos( data->m_fx, (const Coord3D *)thing );

		UnsignedInt amount = (UnsignedInt)reinterpret_cast<Rva0027D378 *>(TheTerrainLogic)->rva0027D378( thing, 99999 );
		UnsignedInt scale = (UnsignedInt)player->getSupplyBoxValue();
		Real reward = (Real)( amount * scale );

		if( reward > 0.0f )
		{
			if( reinterpret_cast<BfmeGlob939D *>(TheGameLogic)->bfmeCall939D() )
				reward *= reinterpret_cast<Rva004C82E5GlobalData *>(TheWritableGlobalData)->m_multiPlayMults.getMoneyMult( ThePlayerList->rva002A7C0B( false ) );

			Real bounty = (Real)player->ScaleMoney( (Int)reward );
			money += data->m_bountyScale * bounty;
		}
	}

	reinterpret_cast<Rva004C82E5Terrain *>(TheTerrainLogic)->m_queryScratch = 0.0f;

	typedef void (Rva003B0D7C::*UnsignedDeposit)(UnsignedInt,Rva0039B7AD*,bool);
	(reinterpret_cast<Rva003B0D7C *>((char *)player + 0x90)->*reinterpret_cast<UnsignedDeposit>(&Rva003B0D7C::rva003B0D7C))( (UnsignedInt)((target)?devastateMin(data->m_bountyCap,money):devastateMin(data->m_bountyCap,money)), reinterpret_cast<Rva0039B7AD *>((char *)player + 0x3BC),true);

	if( !( (const StringBase<char> &)data->m_weaponName ).isEmpty() )
	{
		const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate( data->m_weaponName );
		if( wt )
			TheWeaponStore->createAndFireTempWeapon( wt, getObject(), target );
	}
}
