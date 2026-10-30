// cl: /DNDEBUG /MD /GX /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /ICode/Libraries/Include
// stlport
#include <list>
#include <vector>
#include <string.h>
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef bool Bool;
class Object;
class Player;
class UpgradeTemplate;
class ProductionUpdateModuleData;
class ProductionTransferTemplate;
class TransferContainView;
class Xfer;
struct Rva0049DF81Input;
enum NameKeyType { NK_UNKNOWN = 0 };
enum ProductionType { PRODUCTION_INVALID = 0, PRODUCTION_UNIT, PRODUCTION_UPGRADE, PRODUCTION_HORDE_UNIT };
class Rva0049D526
{
public:
	void rva0049D57F(void *node);
	void rva0049D526(void *entry); // addToProductionQueue
};
//
// ?calcTotalProductionFrames@ProductionUpdate@@QAEHPAVRva0049CD4FArg@@@Z @0x0049CD4F 170B.
// The object at +8 must have a controlling player, and the argument must be
// non-null. Kind 1 asks the ThingTemplate at +8, kind 2 the UpgradeTemplate
// at +0xC, kind 3 the sub-object at player+0x738. A missing kind or a
// non-positive answer becomes 1. The object query at code 0xD may replace
// the 1.0f scale, and the answer is then divided by that scale.

class Player;

class Object {
public:
	char pad0[4];
public:
	ProductionTransferTemplate *thing;
public:
	char pad8[0x250-8];
public:
	TransferContainView *contain;
public:
	char pad254[0x274-0x254];
public:
	Object *holder;
public:
	Player *getControllingPlayer() const;
	bool rva0028C15E(int code, float *scale, int c, int d);
};

#include "../../Include/Common/ThingTemplate.h"

enum UpgradeType
{
	UPGRADE_TYPE_PLAYER = 0,
	UPGRADE_TYPE_OBJECT = 1
};
class AsciiString;
class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
	unsigned int calcCostToBuild(Player *player, unsigned int requester) const;
	const AsciiString &getUpgradeName() const { return m_name; }
	int rva0026EE30(void *player, void *object);
	char m_unknown00[4]; // +0x00
	UpgradeType m_type; // +0x04 +4
	AsciiString m_name; // +0x08 +8
	char m_pad0C[0x1C];
	AsciiString m_displayName; // +0x28
	char m_pad2C[0x14];
	void *m_researchSound; // +0x40
	int m_evaEvent; // +0x44
	void *m_unitSound; // +0x48
	char m_pad4C[0x24];
	int m_bfme70; // +0x70 +0x70
};

class Rva0037E6E8
{
public:
	int rva0037E649(int,Object *);
	float rva0037E815(int,Object *);
	int rva0037E6E8(void *extra, void *object);
};

class Rva0037E421
{
public:
	unsigned char productionSystemCancelUnitCreate(int id);
	void *rva0037E915(int index);
	void *rva0037E7A5(int);
	void *rva0037E451(int);
	void *rva0037E421(int);
};

class Player
{
public:
	char m_pad[0x738];
	Rva0037E421 m_table;
};

class Rva0049CD4FArg
{
public:
	int m_pad0;
	int m_kind;
	ThingTemplate *m_thing;
	UpgradeTemplate *m_upgrade;
	void *m_extra;
};

typedef unsigned int UnsignedInt;
class ModuleData;
class Thing;
class ThingTemplate;
class ProductionUpdateInterface;
class Rva0049D1B1;
struct Rva0049D0DEMask;
class Rva0049CD4FArg;


enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };

enum CanMakeType
{
	CANMAKE_OK = 0,
	CANMAKE_NO_PREREQ,
	CANMAKE_NO_MONEY,
	CANMAKE_FACTORY_IS_DISABLED,
	CANMAKE_QUEUE_FULL
};

enum ProductionID
{
	PRODUCTIONID_INVALID = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

template<int NUMBITS> class BitFlags
{
public:
	void xfer(Xfer *xfer);
 unsigned int test(unsigned bit) const { return m_words[bit>>5] & (1u << (bit&31)); }
 void clear() { memset(m_words,0,sizeof(m_words)); }
 void set(unsigned bit,bool value=true) { if(value) m_words[bit>>5] |= 1u << (bit&31); else m_words[bit>>5] &= ~(1u << (bit&31)); }
private:
	unsigned int m_words[(NUMBITS+31)/32];
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
	virtual void bmi01();
	virtual void bmi02();
	virtual void bmi03();
	virtual void bmi04();
	virtual void bmi05();
	virtual void bmi06();
	virtual void bmi07();
	virtual void bmi08();
	virtual void bmi09();
	virtual void bmi10();
	virtual void bmi11();
	virtual void bmi12();
	virtual void bmi13();
	virtual void bmi14();
	virtual void bmi15();
	virtual void bmi16();
	virtual void bmi17();
	virtual void bmi18();
	virtual void bmi19();
	virtual void bmi20();
	virtual void bmi21();
	virtual void bmi22();
	virtual void bmi23();
	virtual void bmi24();
	virtual void bmi25();
	virtual void bmi26();
	virtual void bmi27();
	virtual ProductionUpdateInterface *getProductionUpdateInterface();	// +0x70
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class ProductionUpdateInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual Bool queueCreateUnit(const ThingTemplate *,Int,ProductionID,Int,Bool,const AsciiString &,Bool);
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void cancelUnitCreate(ProductionID productionID);
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void i12();
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual void i17();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *firstProduction() const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

struct DoorInfo
{
	UnsignedInt m_doorOpenedFrame;
	UnsignedInt m_doorWaitOpenFrame;
	UnsignedInt m_doorClosedFrame;
	Bool m_holdOpen;
};

class Image;

class ProductionEntry
{
public:
    virtual void *scalarDeleting(unsigned int flags);
    Bool getProductionObject() const;
};

class Rva0049D1B1
{
public:
	Rva0049D1B1() throw();
	virtual ~Rva0049D1B1();

	// type 1 or 3, the rowed out-of-line copy 0x00327C1B
	Bool isUnit() const { return ((const ProductionEntry *)this)->getProductionObject(); }
	ProductionType getProductionType() const { return m_type; }
 Int getProductionID() const { return m_productionID; }
	const ThingTemplate *getProductionObject() const { return m_objectToProduce; }
	const UpgradeTemplate *getProductionUpgrade() const { return m_upgradeToResearch; }

	ProductionType m_type; // +4
	const ThingTemplate *m_objectToProduce; // +8
	const UpgradeTemplate *m_upgradeToResearch; // +0xC
	Int m_productionID; // +0x10
	float m_percentComplete; // +0x14
	float m_bfme18; // +0x18
	Int m_bfme1C; // +0x1C
	Int m_productionQuantityTotal; // +0x20
	Int m_productionQuantityProduced; // +0x24
	Int m_cost; // +0x28
	ExitDoorType m_exitDoor; // +0x2C
	Int m_bfme30; // +0x30
	Bool m_bfme34; // +0x34
	union { Int m_bfme38; const Image *m_buttonImage; }; // +0x38
	Int m_bfme3C; // +0x3C
	AsciiString m_name; // +40
	Bool m_slave; // +44
	char m_unknown45[3];
	Rva0049D1B1 *m_next; // +0x48
	Rva0049D1B1 *m_prev; // +0x4C
	char m_unknown50[0x54 - 0x50];
};

class ProductionUpdate : public UpdateModule, public ProductionUpdateInterface, public DieModuleInterface
{
public:
 ProductionUpdate(Thing *, const ModuleData *);
 virtual ~ProductionUpdate();
 virtual NameKeyType getModuleNameKey() const;
 virtual UpdateSleepTime update();
 void rva0049D3BC(); void rva0049CD24(Object *);
 virtual Bool queueCreateUnit(const ThingTemplate *,Int,ProductionID,Int,Bool,const AsciiString &,Bool);
 void rva0049E368(); void rva0049CF25();
 void rva0049DF81(Rva0049DF81Input *,Object *);
 Int calcTotalProductionFrames(Rva0049CD4FArg *);

	virtual CanMakeType rva0049CFCD() const;
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const;
	virtual ProductionID requestUniqueUnitID();
	virtual Bool queueUpgrade(const UpgradeTemplate *upgrade);
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);
	virtual void rva0049CC9D(const ThingTemplate *unitType, Bool five);
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const;
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *unitType) const;
	virtual Bool rva0049CC36(ProductionID productionID) const;
	virtual void rva0049CC61(const ThingTemplate *unitType);
	virtual void rva0049F8A9(const ThingTemplate *unitType, Bool cancel);
	virtual void rva0049CC15(ProductionID productionID, Int value);
	virtual void cancelAndRefundAllProduction();
	virtual void rva0049DEC8();
	virtual UnsignedInt rva0049CEAE(const ThingTemplate *unitType) const;
	virtual UnsignedInt rva0049CEE1(Int value) const;
	virtual UnsignedInt rva0049D0DE(const Rva0049D0DEMask *mask) const;
	virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const;

	static ProductionUpdateInterface *getProductionUpdateInterfaceFromObject(Object *obj);
	const Rva0049D1B1 *GetEntryToProcess();

protected:
	virtual void xfer(Xfer *xfer);

	const ProductionUpdateModuleData *getProductionUpdateModuleData() const
	{
		return (const ProductionUpdateModuleData *)m_moduleData;
	}
	void addToProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D526(production);
	}
	void removeFromProductionQueue(Rva0049D1B1 *production)
	{
		((Rva0049D526 *)this)->rva0049D57F(production);
	}

	Rva0049D1B1 *m_productionQueue; // +0x28
	Rva0049D1B1 *m_productionQueueTail; // +0x2C
	ProductionID m_uniqueID; // +0x30
	UnsignedInt m_productionCount; // +0x34
	UnsignedInt m_constructionCompleteFrame; // +0x38
	DoorInfo m_doors[4]; // +0x3C
	BitFlags<591> m_clearFlags; // +0x7C
	BitFlags<591> m_setFlags; // +0xC8
	Bool m_flagsDirty; // +0x114
	UnsignedInt m_bfme118; // +0x118
	Bool m_bfme11C;
	Bool m_cancellingAll; // +0x11C
	ObjectID m_bfme120; // +0x120
	_STL::list<ObjectID> m_createdAuxiliary; // +124
	UnsignedInt m_bfme128; // +0x128
	unsigned int m_bfme12C; // +0x12C
	_STL::vector<AsciiString> m_bfme130; // +0x130
	Bool m_bfme13C; // +0x13C
};

int ProductionUpdate::calcTotalProductionFrames(Rva0049CD4FArg *arg)
{
	if (!m_object)
		return 1;
	Player *player = m_object->getControllingPlayer();
	if (!player || !arg)
		return 1;

	int result;
	switch (arg->m_kind)
	{
	case 1:
	{
		int object = (int)m_object;
		result = arg->m_thing->calcTimeToBuild(player, object, -1);
		break;
	}
	case 2:
		result = arg->m_upgrade->rva0026EE30(player, m_object);
		break;
	case 3:
		result = ((Rva0037E6E8 *)&player->m_table)->rva0037E6E8(arg->m_extra, m_object);
		break;
	default:
		result = 1;
		break;
	}
	if (result < 1)
		result = 1;

	float scale = 1.0f;
	if (m_object->rva0028C15E(0xD, &scale, 0, 1))
		result = (int)((float)result / scale);
	return result;
}
