// cl: /DNDEBUG /MD /I.
//
// ?xfer@DamageFilteredCreateObjectDie@@MAEXPAVXfer@@@Z, retail 0x00485FE3, 50 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084AB54 (class of ??0DamageFilteredCreateObjectDie
// rowed at 0x00485F87 in DamageFilteredCreateObjectDieCtor.cpp).
//
// Version1 via rowed 0x000053EE, base DieModule xfer via rowed 0x004CE56D
// (?xfer@Rva004CE56D@@QAEXPAVXfer@@@Z), then uint at +0x18 via Xfer slot
// 0x78 plus int at +0x1C via Xfer slot 0x7C. Layout is the rowed ctor class
// (DieModule base 0x14 plus +0x14 member giving +0x18 start; ctor zeroes
// +0x18 and sets +0x1C to -1). Recipe is the ClickReactionBehaviorXfer
// slot-3 pattern.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

class Rva004CE56D
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x14 - 4];
};

//
// DamageFilteredCreateObjectDie's +0x14 damage-module interface overrides
// (table 0x00C4AA84, installed by the matched ctor 0x00485F87, which also
// zeroes +0x18 and sets +0x1C to -1; the matched xfer saves both), so `this`
// is that subobject (module data at -0x10).
//   slot 0, retail 0x004860E9 (77 bytes), onDamage: for damage whose +0x18
//           value equals the module data's +0x40, records the frame (+0x18)
//           and, when the source Object (+0x08) and its controlling Player
//           still exist, the Player's +0x54 value (+0x1C).
//   slot 1, retail 0x00485EF6 (7 bytes): clears the recorded frame; its
//           argument is unused.
// Slot names by address.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
class ObjectCreationList;
class Player
{
public:
	unsigned char m_pad00[0x54];
	Object *rva002AC629();
	int m_54;			// +0x54
};
class Object
{
public:
	Player *getControllingPlayer() const;
	char pad00[0x38]; Coord3D position;
};
extern GameLogic *TheGameLogic;
class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;		// +0x08
	unsigned char m_pad0C[0x18 - 0x0C];
	int m_18;			// +0x18
};
struct DamageFilteredCreateObjectDieModuleData
{
	unsigned char m_pad00[0x38];
	ObjectCreationList *m_creationList;
	int m_dieDamage;
	int m_damageTypeTriggersForDuration;
	unsigned int m_timeWindow;			// +0x44
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;			// +0x08
};
#include "../../../../Include/GameLogic/Module/DieModule.h"
class Rva00C4AA84Iface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(void *arg) = 0;
};
class DamageFilteredCreateObjectDie : public DieModule, public Rva00C4AA84Iface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void onHealing(void *arg);
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_frame;		// +0x18
	int m_playerValue;		// +0x1C
};
class ObjectCreationList
{
public:
 void create(void *,void *,void *,int);
};
class PlayerList { public: Player *getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class Rva002AA22AByteField { public: unsigned char get() const; };

// Target C4AA90 DieModuleInterface slot0 is onDie, as the ZH interface
// specifies. Native this is primary+10: data -C, owner -8 and recorded
// frame/player at +8/+C. DamageFiltered's extra selection/time window
// paths are target evidence; ZH CreateObjectDie supplies OCL-on-die purpose.
void DamageFilteredCreateObjectDie::onDie(const DamageInfo *damageInfo)
{
 if (!damageInfo || !isDieApplicable(damageInfo)) return;
 const DamageFilteredCreateObjectDieModuleData *data =
  (const DamageFilteredCreateObjectDieModuleData *)m_moduleData;
 if (!data) return;
 Object *object=m_object;
 if (!object) return;
 if (data->m_dieDamage == damageInfo->m_18)
 {
  Object *source=TheGameLogic->findObjectByID(damageInfo->m_sourceID);
  if (!source) return;
  if (data->m_creationList)
   data->m_creationList->create(source,&object->position,0,0);
  TheGameLogic->destroyObject(object);
 }
 else if (TheGameLogic->getFrame()-m_frame < data->m_timeWindow)
 {
  {
   int playerValue = m_playerValue;
   if (playerValue != -1)
   {
    Player *player=ThePlayerList->getNthPlayer(playerValue);
    if (player && !((const Rva002AA22AByteField *)player)->get())
    {
     Object *source=player->rva002AC629();
     // The fallback address is unused when source is null.
     ObjectCreationList *creationList = source ? data->m_creationList : reinterpret_cast<ObjectCreationList *>(const_cast<DamageFilteredCreateObjectDieModuleData *>(data));
     if (source)
     {
      if (creationList) creationList->create(source,&object->position,0,0);
      TheGameLogic->destroyObject(object);
     }
    }
   }
  }
 }
 else m_playerValue=-1;
}

void DamageFilteredCreateObjectDie::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004CE56D *)this)->xfer(xfer);
	*xfer == m_frame;
	*xfer == m_playerValue;
}
