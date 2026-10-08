// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /GX
#include "GameLogic/BfmeStoredAICommandView.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

extern "C" void free(void *);
enum AICommandType { AICMD_NO_COMMAND=-1 };
enum CommandSourceType { CMD_FROM_AI=2 };
struct AICommandParms : public Rva00351570Src {
 AICommandParms(AICommandType,CommandSourceType);
 ~AICommandParms() { if(m_20.m_start) free(m_20.m_start); }
};

typedef bool Bool;
typedef unsigned int UnsignedInt;
enum WhichTurretType { TURRET_INVALID=-1 };
enum DeployStateTypes { READY_TO_MOVE, DEPLOY, READY_TO_ATTACK, UNDEPLOY, ALIGNING_TURRETS };
class Drawable;
class Object {
public:
	Drawable *getDrawable() const;
	void rva0028CFB2(const int *,const int *);
	bool addAttributeModifierToPool(const AsciiString &,int);
	void removeAttributeModifierFromPool(const AsciiString &);
	ObjectID getID() const { return m_id; }
	char pad00[0x74]; ObjectID m_id;
};
class AICommandInterface { public: void aiIdle(CommandSourceType); };
class AIUpdateInterface {
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretEnabled(WhichTurretType,Bool);
	void recenterTurret(WhichTurretType);
};
class Rva0048E61F { public: int rva0048E61F(); };
extern GameLogic *TheGameLogic;

// Native primary vtable dispatch at +0x268 (154 preceding slots).
// Pointer-only view: no instances, constructors or vtable providers are emitted.
class DeployStyleCommandDispatchView {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual void slot132();
	virtual void slot133();
	virtual void slot134();
	virtual void slot135();
	virtual void slot136();
	virtual void slot137();
	virtual void slot138();
	virtual void slot139();
	virtual void slot140();
	virtual void slot141();
	virtual void slot142();
	virtual void slot143();
	virtual void slot144();
	virtual void slot145();
	virtual void slot146();
	virtual void slot147();
	virtual void slot148();
	virtual void slot149();
	virtual void slot150();
	virtual void slot151();
	virtual void slot152();
	virtual void slot153();
	virtual void doCommand(const AICommandParms *,bool);
};

//
// ??0DeployStyleAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0048E983 (112 bytes). Behavior ctor over the pinned opaque AI-update
// base (0x26E9BD, thing plus data): installs the five behavior vtable slots
// (+0x00/+0x0C/+0x10/+0x20/+0x24 via explicit members with TU-local dummy
// statics, DIR32-masked) over a 0x3E4 member (ctor 0x26AFDA, size 0xC4
// ending at 0x4A8) plus zeros at +0x4A8..0x4B8 in retail order
// (0x4B4 before 0x4B0), then runs the pinned class helper (0x48E65B).
// This ABI view declares no virtuals of its own: the stores land from explicit
// members in body order (AssaultTransport precedent). Row supersedes the
// sole-caller pin; the instance factory at 0x24D1E6 is the single raw caller.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

class Rva0026E9BDBase
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;			// +0x00
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;			// +0x0C
	const void *m_p10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;			// +0x20
	const void *m_p24;			// +0x24
	unsigned char m_pad28[0x3E4 - 0x28];
};

class Rva0026AFDAMember
{
public:
	void initMember();

private:
	unsigned char m_pad[0xC4];
};

class DeployStyleAIUpdate : public Rva0026E9BDBase
{
public:
	DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData);
	void reset();
	void doLastOutsideCommand();
 void rva0048EB53(DeployStateTypes);
 Object *getObject() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)+8); }
 const void *getModuleData() const { return *reinterpret_cast<const void *const *>(reinterpret_cast<const char *>(this)+4); }
 Bool shouldDoLastOutsideCommand() { return (unsigned char)reinterpret_cast<Rva0048E61F *>(this)->rva0048E61F()!=0; }
 void aiIdle(CommandSourceType source) { reinterpret_cast<AICommandInterface *>(&m_p20)->aiIdle(source); }
 WhichTurretType getWhichTurretForCurWeapon() const { return reinterpret_cast<const AIUpdateInterface *>(this)->getWhichTurretForCurWeapon(); }
 void setTurretEnabled(WhichTurretType turret,Bool enabled) { reinterpret_cast<AIUpdateInterface *>(this)->setTurretEnabled(turret,enabled); }
 void recenterTurret(WhichTurretType turret) { reinterpret_cast<AIUpdateInterface *>(this)->recenterTurret(turret); }

protected:
	Rva0026AFDAMember m_member3E4;		// +0x3E4 (init 0x26AFDA via TU method pin)
	bool m_flag4A8;				// +0x4A8
	bool m_flag4A9;				// +0x4A9
	unsigned char m_pad4AA[0x4AC - 0x4AA];
	int m_4AC;				// +0x4AC
	int m_4B0;				// +0x4B0
	int m_4B4;				// +0x4B4
	int m_4B8;				// +0x4B8
	int m_4BC;				// +0x4BC
	int m_4C0;				// +0x4C0
	float m_4C4;			// +0x4C4
	float m_4C8;			// +0x4C8
	float m_4CC;			// +0x4CC
	unsigned char m_4D0;		// +0x4D0
	unsigned char m_4D1;		// +0x4D1
	unsigned char m_4D2;		// +0x4D2
	unsigned char m_4D3;		// +0x4D3
	unsigned char m_4D4;		// +0x4D4
	unsigned char m_4D5;		// +0x4D5
	unsigned char m_4D6;		// +0x4D6
};

// ??0DeployStyleAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x48E983
DeployStyleAIUpdate::DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0026E9BDBase(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_member3E4.initMember();
	int zero = 0;
	m_flag4A8 = false;
	m_flag4A9 = false;
	m_4AC = zero;
	m_4B4 = zero;
	m_4B0 = zero;
	m_4B8 = zero;
	reset();
}

// ?reset@DeployStyleAIUpdate@@QAEXXZ @0x48E65B (80 bytes). Clears the
// transient deploy-motion block (+0x4BC..0x4D6): two ints, three floats and
// seven flag bytes. Runs at the end of the ctor, on new AI commands and
// from update. The float triple is zeroed through one address-taken pointer
// (retail lea plus three movss); separate stores would use direct offsets.
void DeployStyleAIUpdate::reset()
{
	m_4BC = 0;
	m_4D0 = 0;
	m_4D4 = 0;
	m_4D3 = 0;
	m_4D1 = 0;
	m_4C0 = 0;
	m_4D2 = 0;
	m_4D5 = 0;
	m_4D6 = 0;
	float *goal = &m_4C4;
	goal[0] = 0.0f;
	goal[1] = 0.0f;
	goal[2] = 0.0f;
}

// WB11DA210 names doLastOutsideCommand and asserts DeployStyleAIUpdate.cpp535.
// Native48E90B..48E983 constructs a 192-byte parameter view, restores the
// 196-byte stored command at3E4, clears replay4A9 and dispatches slot268.
void DeployStyleAIUpdate::doLastOutsideCommand()
{
	AICommandParms parms(AICMD_NO_COMMAND,CMD_FROM_AI);
	reinterpret_cast<const Rva00351570 *>(&m_member3E4)->rva0035164E(parms);
	m_flag4A9=false;
	reinterpret_cast<DeployStyleCommandDispatchView *>(this)->doCommand(&parms,true);
}

class Rva0028F59A {
public:
 Rva0028F59A(int,int);
 operator const int *() const { return bits; }
 int bits[19];
};
class Rva001E4912 {
public:
 Rva001E4912 *rva001E4912(int,unsigned int,unsigned int);
 int bits[19];
};
class Rva001E42F2 { public: void rva001E42F2(const int *); };
class Rva002D9531 { public: void rva002D9531(int); };
class Rva0036CA00Str {
public:
 OpaqueRefCounted *referent;
 ~Rva0036CA00Str() { if(referent) referent->Release_Ref(); }
};
class Rva002390CB { public: int id; Rva0036CA00Str ref; };
class Drawable {
public:
 void setAnimationLoopDuration(UnsignedInt);
 Rva002390CB rva00274CD8(const AsciiString &);
};
class AudioManager {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9)
 SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
 SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
#undef SLOT
 virtual unsigned int addAudioEvent(const BfmeAudioEventPrefix136 *);
};
extern AudioManager *TheAudio;


// Native48EB53..48EE8C: full five-state transition and EH lifetime.
// BFME1 6c1e0b51 setMyState is the semantic guide; WB11D9AA0 preserves
// DeployStyleAIUpdate.cpp context but does not name this target method.
// Keep its target method label neutral. Modifier enters on READY_TO_ATTACK.
void DeployStyleAIUpdate::rva0048EB53(DeployStateTypes stateID)
{
 m_4B4=stateID;
 Object *self=getObject();
 Drawable *draw=self->getDrawable();
 switch(stateID) {
 case DEPLOY: {
  aiIdle(CMD_FROM_AI);
  self->rva0028CFB2(reinterpret_cast<const int *>(&static_cast<const Rva0028F59A &>(Rva0028F59A(0,0x5e))),reinterpret_cast<const int *>(&static_cast<const Rva0028F59A &>(Rva0028F59A(0,0x60))));
  m_4B8=*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(getModuleData())+0x64);
  if(draw) {
   draw->setAnimationLoopDuration(m_4B8);
   BfmeAudioEventPrefix136 sound(reinterpret_cast<const OpaqueRefElement4 &>(draw->rva00274CD8(AsciiString("Deploy")).ref),0);
   reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531((int)self->getID());
   TheAudio->addAudioEvent(&sound);
  }
  m_4B8+=TheGameLogic->getFrame();
  break;
 }
 case UNDEPLOY: {
  aiIdle(CMD_FROM_AI);
  Rva001E4912 both;
  self->rva0028CFB2(reinterpret_cast<const int *>(both.rva001E4912(0,0x60,0x64)),reinterpret_cast<const int *>(&static_cast<const Rva0028F59A &>(Rva0028F59A(0,0x5e))));
  m_4B8=*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(getModuleData())+0x68);
  if(draw) {
   draw->setAnimationLoopDuration(m_4B8);
   BfmeAudioEventPrefix136 sound(reinterpret_cast<const OpaqueRefElement4 &>(draw->rva00274CD8(AsciiString("Undeploy")).ref),0);
   reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531((int)self->getID());
   TheAudio->addAudioEvent(&sound);
  }
  m_4B8+=TheGameLogic->getFrame();
  if(*(reinterpret_cast<const unsigned char *>(getModuleData())+0x6d)) {
   WhichTurretType tur=getWhichTurretForCurWeapon();
   if(tur!=TURRET_INVALID) setTurretEnabled(tur,false);
  }
  if(!reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(getModuleData())+0x70)->isEmpty())
   self->removeAttributeModifierFromPool(*reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(getModuleData())+0x70));
  break;
 }
 case READY_TO_MOVE:
  m_4B8=0;
  if(shouldDoLastOutsideCommand()) doLastOutsideCommand();
  reinterpret_cast<Rva001E42F2 *>(self)->rva001E42F2(reinterpret_cast<const int *>(&static_cast<const Rva0028F59A &>(Rva0028F59A(0,0x5e))));
  break;
 case READY_TO_ATTACK:
  m_4B8=0;
  if(!m_4D0 && shouldDoLastOutsideCommand()) doLastOutsideCommand();
  self->rva0028CFB2(reinterpret_cast<const int *>(&static_cast<const Rva0028F59A &>(Rva0028F59A(0,0x60))),reinterpret_cast<const int *>(&static_cast<const Rva0028F59A &>(Rva0028F59A(0,0x64))));
  if(*(reinterpret_cast<const unsigned char *>(getModuleData())+0x6d)) {
   WhichTurretType tur=getWhichTurretForCurWeapon();
   if(tur!=TURRET_INVALID) setTurretEnabled(tur,true);
  }
  if(!reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(getModuleData())+0x70)->isEmpty())
   self->addAttributeModifierToPool(*reinterpret_cast<const AsciiString *>(reinterpret_cast<const char *>(getModuleData())+0x70),-1);
  break;
 case ALIGNING_TURRETS: {
  m_4B8=0;
  WhichTurretType tur=getWhichTurretForCurWeapon();
  if(tur!=TURRET_INVALID) recenterTurret(tur);
  break;
 }
 }
}

