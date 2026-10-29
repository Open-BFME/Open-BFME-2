// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /I.
// Native004ADD8D..004ADF0B RET0; WB1228F20 names createMountedTemplate.
// ModuleFactory24F68A and ctor4ADAB5 establish owning class and module prefix.
// No clean ZH/BF1 donor exists for the mounted extension: native defines each
// field and call contract; matched sibling toggles guide the update pattern.
// Native player score record3BC uses the existing neutral39CBCE binding;
// Object angle44/id74/name88/experience264/record468 and body254 are explicit.
// BuildAssistant slot14 is independently recovered buildObjectNow3952D8.
// Selection slots66/67 retain neutral names. Drawable selected43C is tested
// for nonzero; retaining replacementBody across source virtual slot4 keeps
// native destination receiver at ebp-8. No new pins or shared headers.
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

// Shared ToggleMountedSpecialAbilityUpdate unit view: one declaration of each
// class for every body retail built into this unit.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

enum KindOfType
{
	KIND_UNKNOWN = -1
};

enum WeaponSetType
{
	WEAPON_UNKNOWN = 0
};

enum ArmorSetType
{
	ARMORSET_NONE = 0
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Module;
class Player;
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;
class Waypoint;
struct Rva0028AC4EEntry;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

template <int N>
class MountedSlots : public MountedSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <>
class MountedSlots<0>
{
};

class MountedAIView : public MountedSlots<110>
{
public:
	virtual bool isIdle() const = 0;
	virtual void a111() = 0;
	virtual void a112() = 0;
	virtual void a113() = 0;
	virtual void a114() = 0;
	virtual void a115() = 0;
	virtual void a116() = 0;
	virtual void a117() = 0;
	virtual void a118() = 0;
	virtual void a119() = 0;
	virtual void a120() = 0;
	virtual void a121() = 0;
	virtual void a122() = 0;
	virtual void a123() = 0;
	virtual void a124() = 0;
	virtual void a125() = 0;
	virtual void a126() = 0;
	virtual void a127() = 0;
	virtual void a128() = 0;
	virtual void a129() = 0;
	virtual void a130() = 0;
	virtual void a131() = 0;
	virtual void a132() = 0;
	virtual void a133() = 0;
	virtual void a134() = 0;
	virtual void a135() = 0;
	virtual void a136() = 0;
	virtual void a137() = 0;
	virtual void a138() = 0;
	virtual void a139() = 0;
	virtual void a140() = 0;
	virtual void a141() = 0;
	virtual void slot142(int) = 0;
};

class MountedContainView : public MountedSlots<42>
{
public:
	virtual void slot42(int) = 0;
	virtual void c43() = 0;
	virtual void c44() = 0;
	virtual void c45() = 0;
	virtual void c46() = 0;
	virtual void c47() = 0;
	virtual void c48() = 0;
	virtual void c49() = 0;
	virtual void c50() = 0;
	virtual void c51() = 0;
	virtual void c52() = 0;
	virtual void c53() = 0;
	virtual void c54() = 0;
	virtual void c55() = 0;
	virtual void c56() = 0;
	virtual void c57() = 0;
	virtual void c58() = 0;
	virtual void c59() = 0;
	virtual void c60() = 0;
	virtual void c61() = 0;
	virtual void c62() = 0;
	virtual void c63() = 0;
	virtual void c64() = 0;
	virtual void c65() = 0;
	virtual void c66() = 0;
	virtual void c67() = 0;
	virtual void c68() = 0;
	virtual unsigned slot69(int) const = 0;
};

class MountedBodyView : public MountedSlots<4>
{
public:
	virtual float slot4() const = 0;
	virtual void b5() = 0;
	virtual void b6() = 0;
	virtual void b7() = 0;
	virtual void b8() = 0;
	virtual void b9() = 0;
	virtual void b10() = 0;
	virtual void b11() = 0;
	virtual void b12() = 0;
	virtual void b13() = 0;
	virtual void b14() = 0;
	virtual void b15() = 0;
	virtual void b16() = 0;
	virtual void b17() = 0;
	virtual void b18() = 0;
	virtual void b19() = 0;
	virtual void b20() = 0;
	virtual void b21() = 0;
	virtual void b22() = 0;
	virtual void b23() = 0;
	virtual void b24() = 0;
	virtual void b25() = 0;
	virtual void b26() = 0;
	virtual void b27() = 0;
	virtual void b28() = 0;
	virtual void b29() = 0;
	virtual void b30() = 0;
	virtual void b31() = 0;
	virtual void b32() = 0;
	virtual void b33() = 0;
	virtual void b34() = 0;
	virtual void b35() = 0;
	virtual void b36() = 0;
	virtual void b37() = 0;
	virtual void b38() = 0;
	virtual void b39() = 0;
	virtual void b40() = 0;
	virtual void b41() = 0;
	virtual void slot42(float) = 0;
};

class Rva003BD306Target
{
public:
	void rva0039B3D1(float, bool);
	char pad[0x10];
	float experience;
	char pad14[0x28];
	bool enabled;
};

class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &);
	char bytes[24];
};

struct MountedFlags
{
	unsigned words[19];
	__forceinline unsigned test(unsigned bit) const { return words[bit >> 5] & (1U << (bit & 31)); }
	__forceinline void clear(unsigned bit) { words[bit >> 5] &= ~(1U << (bit & 31)); }
	__forceinline void set(unsigned bit) { words[bit >> 5] |= (1U << (bit & 31)); }
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
	void fadeIn(unsigned);
	char m_pad[0xB0];
	float m_scale; // +0xB0
	char m_padB4[0x43C - 0xB4];
	unsigned char selected; // +0x43C
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	void rva0028BAC0(); // 0x0028BAC0
	void leaveGroup();
	void setStatus(ObjectStatusTypes status, bool set);
	const Rva0028AC4EEntry *rva0028AC4E() const;
	Player *getControllingPlayer() const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const;
	bool isKindOf(KindOfType) const;
	void rva0028AE6D();
	void clearWeaponSetFlag(WeaponSetType);
	void setWeaponSetFlag(WeaponSetType);
	void clearArmorSetFlag(ArmorSetType);
	void setArmorSetFlag(ArmorSetType);

protected:
	Module *findModule(NameKeyType) const;
	friend class ToggleMountedSpecialAbilityUpdate;

public:
	__forceinline void clearCondition214()
	{
		if (flags.test(214))
		{
			flags.clear(214);
			rva0028AE6D();
		}
	}
	__forceinline void setCondition214()
	{
		if (!flags.test(214))
		{
			flags.set(214);
			rva0028AE6D();
		}
	}

	char pad0[0x38];
	Coord3D position; // +0x38
	float angle; // +0x44
	char pad48[0x74 - 0x48];
	ObjectID id; // +0x74
	char pad78[0x88 - 0x78];
	StringBase<char> name; // +0x88
	char pad8C[0x10C - 0x8C];
	MountedFlags flags; // +0x10C model-condition words
	char pad158[0x250 - 0x158];
	MountedContainView *contain; // +0x250
	MountedBodyView *body; // +0x254
	MountedAIView *ai; // +0x258
	char pad25C[0x264 - 0x25C];
	Rva003BD306Target *experience; // +0x264
	char pad268[0x468 - 0x268];
	Rva001EAFC1 record; // +0x468
};

struct MountedPowerNames
{
	AsciiString *begin, *end, *capacity;
	bool empty() const { return begin == end; }
};

// ToggleMountedSpecialAbilityUpdateModuleData fields this unit reads.
struct MountedDataView
{
	char pad0[0xCD];
	bool cancelDisguise; // +0xCD CancelDisguiseWhenDismounting
	char padCE[2];
	StringBase<char> mountedTemplate; // +0xD0 MountedTemplate
	MountedPowerNames names; // +0xD4 SynchronizeTimerOnSpecialPower
};

class Rva004AD9B0;

class SpecialAbilityUpdate : public MountedSlots<17>
{
public:
	virtual void triggerAbilityEffect();
	// 0x004500A3 is rowed as SpecialAbilityUpdate::initiateIntentToDoSpecialPower
	// (555B; slot 0); same five-word shape.
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *a, const Object *b, const Coord3D *c, unsigned int d, const Waypoint *e);
	virtual void rva00451B92();

protected:
	virtual void onExit(bool a, bool b);
	friend class Rva004AD9B0;

public:
	const MountedDataView *data;
	Object *owner;
	char padC[0x24 - 0xC];
	int state;
	char pad28[0x8C - 0x28];
	bool flag8C;
};

class ToggleMountedSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void triggerAbilityEffect();
	void createMountedTemplate();
	void rva004ADCE8(const Object *replacement);
};

class ThingTemplate;
class ScoreKeeper {public:void addObjectBuilt(Object*,int);};
class Player {public:char pad[0x3BC];ScoreKeeper score;};
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString&);}; extern ThingFactory *TheThingFactory;
class BuildAssistant : public MountedSlots<14> {public:virtual Object* buildObjectNow(Object*,const ThingTemplate*,const Coord3D*,float,Player*)=0;};extern BuildAssistant *TheBuildAssistant;
class InGameUI : public MountedSlots<66> {public:virtual void slot66(Drawable*)=0;virtual void slot67(Drawable*)=0;};extern InGameUI *TheInGameUI;
class GameMessage {public:void appendBooleanArgument(bool);void appendObjectIDArgument(ObjectID);};
class MessageStream : public MountedSlots<18> {public:virtual GameMessage *appendMessage(int)=0;};extern MessageStream *TheMessageStream;
void ToggleMountedSpecialAbilityUpdate::createMountedTemplate(){
 const ThingTemplate *what=TheThingFactory->findTemplate(*(const AsciiString *)&data->mountedTemplate);
 if(!what)return;
 Object *original=owner;
 bool selected=original->getDrawable()->selected!=0;
 float angle=original->angle;
 Player *player=original->getControllingPlayer();
 Object *replacement=TheBuildAssistant->buildObjectNow(original,what,&original->position,angle,player);
 if(!replacement)return;
 player->score.addObjectBuilt(original,-1);
 replacement->name.set(original->name);
 replacement->record=original->record;
 replacement->experience->enabled=false;
 replacement->experience->rva0039B3D1(original->experience->experience,true);
 replacement->experience->enabled=true;
 MountedBodyView *replacementBody=replacement->body;
 replacementBody->slot42(original->body->slot4());
 replacement->getDrawable()->fadeIn(10);
 if(selected){
 TheInGameUI->slot67(original->getDrawable());
 GameMessage *message=TheMessageStream->appendMessage(1001);
 message->appendBooleanArgument(true);
 message->appendObjectIDArgument(replacement->id);
 TheInGameUI->slot66(replacement->getDrawable());
 }
 rva004ADCE8(replacement);
 flag8C=true;
}
