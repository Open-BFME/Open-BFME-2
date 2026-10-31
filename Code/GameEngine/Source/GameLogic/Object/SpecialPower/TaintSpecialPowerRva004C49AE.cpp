// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004C49AE, 266B: TaintSpecialPower::rva004C49AE (name pinned: the
// location member, ret 4, called on the primary this).
// Same role as BFME 1's TaintSpecialPower::after (reference/open-bfme-1/
// game/GameEngine/Source/GameLogic/Object/SpecialPower/
// TaintSpecialPowerAfter.cpp), without its object scans: clear (0x0027F28E)
// and refresh (0x0027D1A4, radius + 50) the terrain area around the
// location, play the taint FX (module data +0x84) and OCL (+0x88, on a copy
// of the location), add the taint object named at +0x7C (addObject
// 0x004C4940), then paint taint with TheTaintManager (0x006C0AB0): radius x
// 1.25 at amount 0x80 for everyone, and, when the object exists, the plain
// radius at amount 0 for its id. Radius is module data +0x80. The two
// terrain helpers are TerrainLogic members, rowed by address
// (Rva0027F28E.cpp, Rva0027D1A4Forward.cpp).

typedef float Real;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmePointFC;

#include <string.h>
#include "../../../Common/Thing/thing.h"
class AsciiString;
class Matrix3D;
class Player;
class Team;
class ModuleData;
struct Region3D;





class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = 0, const float primarySpeed = 0.0f, const Coord3D *secondary = 0 );
};

class ObjectCreationList
{
public:
	void create( void *primaryObj, void *primary, void *secondary, int createOwner );
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_0x54 = 0x54
};

template <int N> class BitFlags
{
public:
	// Retail's guarded static of this type carries no EH state.
	__declspec(nothrow) BitFlags() { clear(); }
	bool any() const;	// 0x0023C58B for N = 11
	bool setBitByName(const char *token);
	void clear() { memset(m_words, 0, sizeof(m_words)); }
private:
	unsigned int m_words[N == 11 ? 1 : 19];
};

enum WeaponSetType { WEAPONSET_FIRST = 0 };
enum DisabledType { DISABLED_FIRST = 0 };
enum ModelConditionFlagType { MODELCONDITION_FIRST = 0 };

class Object : public Thing
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028EC68(int a, void *b, int c);
	void setTeam(Team *);
	Team *getTeam() const { return m_team; }
	bool isDisabled() const { return m_disabledMask.any(); }
	void setWeaponSetFlag(WeaponSetType type);
	void clearWeaponSetFlag(WeaponSetType type);
	void rva001E42F2(const int *mask);
	bool addAttributeModifierToPool(const AsciiString &name, int n);
	void setDisabledUntil(DisabledType type, unsigned int frame);
	void setSpecialModelConditionState(ModelConditionFlagType set, unsigned int frames);
private:
	char m_pad60[0x74 - 0x60];
public:
	int m_id; // +0x74
private:
	char m_pad78[0x1C8 - 0x78];
	BitFlags<11> m_disabledMask; // +0x1C8
	char m_pad1CC[0x304 - 0x1CC];
	Team *m_team; // +0x304
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual float getGroundHeight( float x, float y, Coord3D *normal ) const;
	virtual void v07();
	virtual void getExtent( Region3D *extent ) const;
	void addTree(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva00280176(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027D3D9(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027F28E(const Coord3D *loc, float radius, int flag);
	void rva0027D1A4(const Coord3D *loc, float radius, int flag);
};
extern TerrainLogic *TheTerrainLogic;


class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld( const BfmePointFC *point, Real radius, int amount, bool absolute, int owner );
};

extern BfmeTaintManager *TheTaintManager;

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

class TaintSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	TaintSpecialPowerModuleData();

	int m_taintObject; // +0x7C
	Real m_taintRadius; // +0x80
	FXList *m_taintFX; // +0x84
	ObjectCreationList *m_taintOCL; // +0x88
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
	virtual void doSpecialPowerUsingWaypoints(void *target, float angle, int commandOptions) = 0;
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
	virtual void doSpecialPower(unsigned int options);	// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);	// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
	virtual void pauseCountdown(bool pause);	// 0x00492FC2
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class TaintSpecialPower : public SpecialPowerModule
{
public:
	TaintSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	void rva004C49AE(const Coord3D *position);
	Object *addObject(const Coord3D *position, const AsciiString &name);
	Object *getObject() const { return m_object; }
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);

protected:
	virtual ~TaintSpecialPower();
};



void TaintSpecialPower::rva004C49AE( const Coord3D *loc )
{
	TaintSpecialPowerModuleData *data = (TaintSpecialPowerModuleData *)m_moduleData;
	Real radius = data->m_taintRadius;
	Object *owner = m_object;

	TheTerrainLogic->rva0027F28E( loc, radius, 1 );
	TheTerrainLogic->rva0027D1A4( loc, radius + 50.0f, 1 );

	if( data->m_taintFX )
		FXList::doFXPos( data->m_taintFX, loc );

	ObjectCreationList *ocl = data->m_taintOCL;
	if( ocl )
	{
		Coord3D oclPoint;
		oclPoint.x = loc->x;
		oclPoint.y = loc->y;
		oclPoint.z = loc->z;
		ocl->create( owner, &oclPoint, 0, 0 );
	}

	Object *taint = addObject( loc, *(const AsciiString *)&data->m_taintObject );
	TheTaintManager->bfmeApplyCircleWorld( (const BfmePointFC *)loc, radius * 1.25f, 0x80, true, -1 );
	if( taint )
		TheTaintManager->bfmeApplyCircleWorld( (const BfmePointFC *)loc, radius, 0, true, taint->m_id );
}
