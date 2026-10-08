// cl: /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BuildAssistant.cpp -- BuildAssistant members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Zero Hour's isRemovableForConstruction
// (Common/System/BuildAssistant.cpp) with BFME2's second never-removable kind.
//
// Layout (target evidence): Object +0x04 is the thing template, whose kind-of
// bits start at +0x108; the effectively-dead flag is bit 0 at Object +0x438.
// Kind indices are read off the tested bytes: 89 (inert, +0x113 bit 1),
// 152 (+0x11B bit 0), 6 (shrubbery, +0x108 bit 6) and 51 (cleared by build,
// +0x10E bit 3); their BFME2 names are not recovered.
//
// canMakeUnit and its countInProduction callback follow Generals'
// BuildAssistant.cpp (ProductionCountData, countObjectsByThingTemplate and
// iterateObjects); WB's canMakeUnit (assert "Needs an AIUpdateInterface if a
// DOZER", BuildAssistant.cpp:3302) supplies BFME2's additions: a revival
// index argument served by the Player +0x738 revival tracker, the Player +0x60
// limit check that returns 7, and a dozer amount added to the money.
// Target layouts: Player +0x90 Money (+0x94 amount), Object +0x258 AI,
// Object +0x437 script status, ThingTemplate +0x5E0 max simultaneous (word).
// isKindOf returns the masked word (not a Bool) because retail loads the 156
// mask once and tests both templates against it. The two leading NULL checks
// are separate statements as in WB (two "return 1" blocks); joined with ||
// they share one return and retail's late push ebx no longer reproduces.
//
// buildObjectNow follows Zero Hour's (same file) with the line-build kinds
// tested inline and BFME2's changes read off retail and WB's body: only a
// non-dozer builder of neither kind 30 nor 149 clears and moves the site (the
// move result is ignored); a kind-104 builder hands the build to the
// interface WB asserts as getFoundationAIInterface (rowed rva0028BCF4, vslot
// 7, same arguments as the AI's construct, vslot 126); the new object takes
// the builder's +0x45C value (GameLogic::rva0023D0C2), its pathfind layer
// unless kind 2 and a pathfind map entry unless kind 189; a kind-156 builder
// skips onStructureConstructionComplete; and units announce themselves
// through the one-drawable voice hand-off (message 0x7DA) instead of ZH's
// VoiceCreated sound.

#include <list>
#include <string.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#endif

enum KindOfType
{
	KINDOF_2 = 2,
	KINDOF_SHRUBBERY = 6,
	KINDOF_STRUCTURE = 7,
	KINDOF_DOZER = 14,
	KINDOF_15 = 15,
	KINDOF_30 = 30,
	KINDOF_CLEARED_BY_BUILD = 51,
	KINDOF_INERT = 89,
	KINDOF_104 = 104,
	KINDOF_149 = 149,
	KINDOF_152 = 152,
	KINDOF_156 = 156,
	KINDOF_157 = 157,
	KINDOF_189 = 189
};

// BFME2's object status bit names (the name table at .rdata 0x009A5F30).
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

enum CommandSourceType
{
	CMD_FROM_PLAYER,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum CanMakeType
{
	CANMAKE_OK,
	CANMAKE_NO_PREREQ,
	CANMAKE_NO_MONEY,
	CANMAKE_FACTORY_IS_DISABLED,
	CANMAKE_QUEUE_FULL,
	CANMAKE_PARKING_PLACES_FULL,
	CANMAKE_MAXED_OUT_FOR_PLAYER,
	CANMAKE_7						// BFME2: the Player +0x60 check refused
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 0x02
};

class Player;
class Object;
class Team;
class Drawable;
struct Rva002A7557In;

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	UnsignedInt getMaxSimultaneousOfType() const { return m_maxSimultaneousOfType; }
	Int rva0033A69A(const Player *player, Int a, Int b) const;

private:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[8];		// +0x108
	unsigned char m_pad128[0x5E0 - 0x128];
	UnsignedShort m_maxSimultaneousOfType;	// +0x5E0
};

class ProductionUpdateInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;					// +0x00
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *type) const;	// +0x1C
};

class ProductionUpdate
{
public:
	static ProductionUpdateInterface *getProductionUpdateInterfaceFromObject(Object *obj);
};

class Rva0028BD17Interface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Bool slot06();						// +0x18
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class DozerAIInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual UnsignedInt slot30();					// +0x78
};

class AIUpdateInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92();
	virtual DozerAIInterface *getDozerAIInterface();		// +0x174
	virtual void slot94(); virtual void slot95(); virtual void slot96(); virtual void slot97();
	virtual void slot98(); virtual void slot99(); virtual void slot100(); virtual void slot101();
	virtual void slot102(); virtual void slot103(); virtual void slot104(); virtual void slot105();
	virtual void slot106(); virtual void slot107(); virtual void slot108(); virtual void slot109();
	virtual void slot110(); virtual void slot111(); virtual void slot112(); virtual void slot113();
	virtual void slot114(); virtual void slot115(); virtual void slot116(); virtual void slot117();
	virtual void slot118(); virtual void slot119(); virtual void slot120(); virtual void slot121();
	virtual void slot122(); virtual void slot123(); virtual void slot124(); virtual void slot125();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);	// +0x1F8

	__forceinline void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }

private:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_command;		// +0x20
};

// What WB asserts as getFoundationAIInterface: its vslot 7 takes the AI
// construct's arguments.
class FoundationAIInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);	// +0x1C
};

// What ThingFactory::newObject takes: the initial status bits.
struct CreateMask
{
	CreateMask() { memset(m_words, 0, sizeof(m_words)); }
	void setBit(Int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }

	UnsignedInt m_words[4];
};

class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const;
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);

protected:
	const ThingTemplate *m_template;	// +0x004
};

class Object : public Thing
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	Bool isEffectivelyDead() const { return m_isEffectivelyDead; }
	Bool testScriptStatusBit(ObjectScriptStatusBit b) const { return (m_scriptStatus & b) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void *rva0028BD17() const;
	void *rva0028BC58(Int which);
	Player *getControllingPlayer() const;
	void setProducer(Object *obj);
	void *rva0028BCF4() const;
	void rva0028B4CE(PathfindLayerEnum layer);
	Int get45C() const { return m_45C; }

private:
	unsigned char m_pad008[0x258 - 8];
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x437 - 0x25C];
	unsigned char m_scriptStatus;		// +0x437
	Bool m_isEffectivelyDead : 1;		// +0x438 bit 0
	unsigned char m_pad439[0x45C - 0x439];
	Int m_45C;				// +0x45C
};

class Rva002A7461
{
public:
	bool rva002A7557(Rva002A7557In *p, int unused);
};

class Rva0037E6E8
{
public:
	Int rva0037E649(Int index, Object *obj);
};

class Rva0037E421
{
public:
	void *rva0037E7A5(int index);
};

class Money
{
public:
	UnsignedInt countMoney() const { return m_money; }

private:
	unsigned char m_pad0[4];
	UnsignedInt m_money;			// +0x04
};

class Player
{
public:
	Money *getMoney() { return &m_money; }
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate * const *things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;
	Int iterateObjects(Int (*func)(Object *, void *), void *userData) const;
	Team *getDefaultTeam() const { return m_defaultTeam; }
	void onStructureCreated(Object *builder, Object *structure);
	void onStructureConstructionComplete(Object *builder, Object *structure, Bool isRebuild);
	void onUnitCreated(Object *factory, Object *unit);

	unsigned char m_pad000[0x60];
	Rva002A7461 m_rva060;			// +0x060
	unsigned char m_pad061[0x90 - 0x61];
	Money m_money;				// +0x090
	unsigned char m_pad098[0x2EC - 0x98];
	Team *m_defaultTeam;			// +0x2EC
	unsigned char m_pad2F0[0x738 - 0x2F0];
	union
	{
		Rva0037E6E8 m_revivalCost;	// +0x738
		Rva0037E421 m_revivalTracker;	// +0x738
	};
};

class BuildAssistant
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Object *buildObjectNow(Object *constructorObject, const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer);	// +0x38
	virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x60
	virtual Bool isPossibleToMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x64

	Bool isRemovableForConstruction(Object *obj);
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle, Player *owningPlayer);
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *statusBits, Bool flag);
};

extern ThingFactory *TheThingFactory;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;	// +0x18
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;		// +0x10
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;

// Retail calls the list destructor out of line (the shared pointer-list
// destructor 0x00239AF4).
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};

class PickAndPlayInfo;

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DA = 0x7DA
	};
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

// The rowed member every newly made object ends with (ZH's
// handlePartitionCellMaintenance).
class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

// ------------------------------------------------------------------------------------------------
struct ProductionCountData
{
	UnsignedInt count;
	const ThingTemplate *type;
};

// countInProduction, retail 0x0039194F.
static Int countInProduction( Object *obj, void *userData )
{
	ProductionUpdateInterface *pui = ProductionUpdate::getProductionUpdateInterfaceFromObject( obj );
	if( pui )
	{
		ProductionCountData *productionCountData = (ProductionCountData *)userData;
		productionCountData->count += pui->countUnitTypeInQueue( productionCountData->type );
	}
	return 1;
}

// BuildAssistant::canMakeUnit, retail 0x00391B08.
CanMakeType BuildAssistant::canMakeUnit( Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex ) const
{
	if( builder == NULL )
		return CANMAKE_NO_PREREQ;
	if( whatToBuild == NULL && revivalIndex == -1 )
		return CANMAKE_NO_PREREQ;

	if( builder->isEffectivelyDead() )
		return CANMAKE_FACTORY_IS_DISABLED;

	Rva0028BD17Interface *x = (Rva0028BD17Interface *)builder->rva0028BD17();
	if( x && x->slot06() )
	{
		if( !(builder->isKindOf( KINDOF_156 ) && whatToBuild && whatToBuild->isKindOf( KINDOF_156 )) )
			return CANMAKE_FACTORY_IS_DISABLED;
	}

	Bool isRevival = revivalIndex != -1;

	if( builder->testScriptStatusBit( OBJECT_STATUS_SCRIPT_DISABLED ) || builder->testScriptStatusBit( OBJECT_STATUS_SCRIPT_UNPOWERED ) )
		return CANMAKE_FACTORY_IS_DISABLED;

	if( !isPossibleToMakeUnit( builder, whatToBuild, revivalIndex ) )
		return CANMAKE_NO_PREREQ;

	ProductionUpdateInterface *pu = (ProductionUpdateInterface *)builder->rva0028BC58( 0 );
	if( pu != NULL )
	{
		CanMakeType cmt = pu->rva0049CFCD();
		if( cmt != CANMAKE_OK )
			return cmt;
	}

	Player *player = builder->getControllingPlayer();
	Money *money = player->getMoney();
	UnsignedInt dozerAmount = 0;
	if( builder->isKindOf( KINDOF_DOZER ) || builder->isKindOf( KINDOF_15 ) )
	{
		AIUpdateInterface *ai = builder->getAI();
		DozerAIInterface *dozerAI = ai ? ai->getDozerAIInterface() : NULL;
		if( dozerAI )
			dozerAmount = dozerAI->slot30();
	}

	if( isRevival )
	{
		if( player->m_revivalCost.rva0037E649( revivalIndex, builder ) > money->countMoney() + dozerAmount )
			return CANMAKE_NO_MONEY;
		if( !player->m_rva060.rva002A7557( (Rva002A7557In *)player->m_revivalTracker.rva0037E7A5( revivalIndex ), 1 ) )
			return CANMAKE_7;
	}
	else
	{
		if( whatToBuild && !whatToBuild->isKindOf( KINDOF_157 ) )
		{
			if( (UnsignedInt)whatToBuild->rva0033A69A( player, (Int)builder, -1 ) > money->countMoney() + dozerAmount )
				return CANMAKE_NO_MONEY;
		}
		if( !player->m_rva060.rva002A7557( (Rva002A7557In *)whatToBuild, 1 ) )
			return CANMAKE_7;
	}

	// make sure we're not maxed out for this type of unit.
	if( whatToBuild && whatToBuild->getMaxSimultaneousOfType() != 0 )
	{
		const Bool ignoreDead = true;
		const Bool ignoreUnderConstruction = false;
		Int existingCount;
		player->countObjectsByThingTemplate( 1, &whatToBuild, ignoreDead, &existingCount, ignoreUnderConstruction );
		if( existingCount >= whatToBuild->getMaxSimultaneousOfType() )
			return CANMAKE_MAXED_OUT_FOR_PLAYER;

		// also check objects that are in production
		ProductionCountData productionCountData;
		productionCountData.count = 0;
		productionCountData.type = whatToBuild;
		player->iterateObjects( countInProduction, &productionCountData );
		if( productionCountData.count + existingCount >= whatToBuild->getMaxSimultaneousOfType() )
			return CANMAKE_MAXED_OUT_FOR_PLAYER;
	}

	return CANMAKE_OK;
}

// BuildAssistant::isRemovableForConstruction, retail 0x00391CE3.
Bool BuildAssistant::isRemovableForConstruction(Object *obj)
{
	if (obj == 0)
		return false;
	if (obj->isKindOf(KINDOF_INERT))
		return false;
	if (obj->isKindOf(KINDOF_152))
		return false;
	if (obj->isKindOf(KINDOF_SHRUBBERY))
		return true;
	if (obj->isKindOf(KINDOF_CLEARED_BY_BUILD))
		return true;
	if (obj->isEffectivelyDead())
		return true;
	return false;
}

// BuildAssistant::buildObjectNow, retail 0x003952D8 (vslot 14).
Object *BuildAssistant::buildObjectNow( Object *constructorObject, const ThingTemplate *what,
										const Coord3D *pos, Real angle, Player *owningPlayer )
{

	// sanity
	if( what == NULL || pos == NULL )
		return NULL;

	if( owningPlayer == NULL )
		return NULL;

	if( !constructorObject->isKindOf( KINDOF_DOZER ) && !what->isKindOf( KINDOF_30 ) && !what->isKindOf( KINDOF_149 ) )
	{

		// clear out any objects from the building area that are "auto-clearable" when building
		clearRemovableForConstruction( what, pos, angle );

		moveObjectsForConstruction( what, pos, angle, owningPlayer );

	}

	// do the build
	if( constructorObject->isKindOf( KINDOF_DOZER ) )
	{
		AIUpdateInterface *ai = constructorObject->getAI();

		if( ai )
		{
			ai->aiIdle( CMD_FROM_AI ); // stop any current behavior.
			return ai->construct( what, pos, angle, owningPlayer, FALSE, 0 );
		}
		return NULL;

	}
	else if( constructorObject->isKindOf( KINDOF_104 ) )
	{
		FoundationAIInterface *foundation = (FoundationAIInterface *)constructorObject->rva0028BCF4();
		return foundation->construct( what, pos, angle, owningPlayer, FALSE, 0 );
	}
	else
	{

		CreateMask startingStatus;
		if( what->isKindOf( KINDOF_STRUCTURE ) )
			startingStatus.setBit( OBJECT_STATUS_UNDER_CONSTRUCTION );

		Object *obj = TheThingFactory->newObject( what, owningPlayer->getDefaultTeam(), &startingStatus, false );
		obj->setProducer( constructorObject );
		TheGameLogic->rva0023D0C2( obj, constructorObject->get45C() );

		// place on terrain surface
		Coord3D groundPos;
		groundPos.x = pos->x;
		groundPos.y = pos->y;
		groundPos.z = TheTerrainLogic->getGroundHeight( groundPos.x, groundPos.y );
		obj->setPosition( &groundPos );

		obj->setOrientation( angle );

		if( !obj->isKindOf( KINDOF_2 ) )
			obj->rva0028B4CE( TheTerrainLogic->getLayerForDestination( obj, pos ) );

		if( !obj->isKindOf( KINDOF_189 ) )
			TheAI->pathfinder()->AddObjectToPathfindMap( obj );

		// notify the player that this thing has come into existence
		if( obj->isKindOf( KINDOF_STRUCTURE ) )
		{
			owningPlayer->onStructureCreated( constructorObject, obj );
			if( !constructorObject->isKindOf( KINDOF_156 ) )
				owningPlayer->onStructureConstructionComplete( constructorObject, obj, FALSE );
		}
		else
		{
			owningPlayer->onUnitCreated( constructorObject, obj );

			DrawableList list;
			list.push_back( obj->getDrawable() );
			pickAndPlayUnitVoiceResponse( &list, GameMessage::MSG_BFME2_0x7DA, 0 );
		}

		reinterpret_cast<Rva0028CBFD *>( obj )->rva0028CBFD();

		return obj;

	}

}
