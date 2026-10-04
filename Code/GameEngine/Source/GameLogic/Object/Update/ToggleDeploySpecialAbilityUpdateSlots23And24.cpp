// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
//
// Slots 23 and 24 of ToggleDeploySpecialAbilityUpdate's vftable 0x00C55370
// (installed by the matched ctor 0x004AE4AB). The class's matched slot-17
// override 0x004AE634 (ToggleSpecialAbilityUpdateSlot17.cpp) calls slot 23
// for an owner of kind-of 0x64 and slot 24 otherwise, each with the owner;
// these rows keep that unit's address names and signature. Method identities
// are not established.
//
// ?rva004AE5B8@ToggleDeploySpecialAbilityUpdate@@UAEXPAVObject@@@Z, retail
// 0x004AE5B8, 124 bytes: plays the module data's +0xCC sound on the owner
// (audio event built by the rowed 0x002D97D6, object ID set by the rowed
// 0x002D9531, TheAudio slot 25) and runs the rowed DeployStyleAIUpdate
// helper 0x0048E6D2 on the argument's AI (Object+0x258).
//
// ?rva004AE6D7@ToggleDeploySpecialAbilityUpdate@@UAEXPAVObject@@@Z, retail
// 0x004AE6D7, 183 bytes: only when the +0x20 interface's slot 8 answers true
// for a null argument (ZH SpecialPowerUpdateInterface has
// isPowerCurrentlyInUse(const CommandButton * = NULL) in slot 8; the name is
// not asserted here) and the argument has an AI: idles that AI (rowed
// AICommandInterface::aiIdle, CMD_FROM_AI) when the rowed Object gate
// rva0028B7C8 holds (filed as int, retail tests AL) or the AI's slot 111
// answers true; then plays the module data's +0xC8 sound on the owner and
// runs the rowed mirror helper 0x0048E6AB on that AI.

#include "Common/BfmeAudioEventPrefix136.h"

class ModuleData;

class Rva002D9531
{
public:
	void rva002D9531(int v);
};

template <int N> class Rva004AE5B8Slots : public Rva004AE5B8Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004AE5B8Slots<0>
{
};

class AudioManager : public Rva004AE5B8Slots<25>
{
public:
	virtual int rva004AE5B8Slot25(BfmeAudioEventPrefix136 *event) = 0;
};

extern AudioManager *TheAudio;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterfaceSlots : public Rva004AE5B8Slots<111>
{
public:
	virtual bool rva004AE6D7Slot111() = 0;
};

class AIUpdateInterfaceView : public AIUpdateInterfaceSlots
{
public:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_command; // +0x20
};

class DeployStyleAIUpdate : public AIUpdateInterfaceView
{
public:
	void rva0048E6D2();
	void rva0048E6AB();
};

class Object
{
public:
	int rva0028B7C8() const;

	unsigned char m_pad000[0x74];
	int m_id; // +0x74
	unsigned char m_pad078[0x258 - 0x78];
	DeployStyleAIUpdate *m_ai; // +0x258
};

struct ToggleDeploySpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0xC8];
	OpaqueRefElement4 m_soundC8; // +0xC8
	OpaqueRefElement4 m_soundCC; // +0xCC
};

class SpecialPowerUpdateInterface : public Rva004AE5B8Slots<8>
{
public:
	virtual bool rva004AE6D7Slot8(const void *button) = 0;
};

class UpdateModuleView
{
public:
	virtual ~UpdateModuleView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class ToggleDeploySpecialAbilityUpdate : public UpdateModuleView, public SpecialPowerUpdateInterface
{
public:
	virtual void rva004AE5B8(Object *obj);
	virtual void rva004AE6D7(Object *obj);
};

// ?rva004AE5B8@ToggleDeploySpecialAbilityUpdate@@UAEXPAVObject@@@Z @0x004AE5B8
void ToggleDeploySpecialAbilityUpdate::rva004AE5B8(Object *obj)
{
	const ToggleDeploySpecialAbilityUpdateModuleData *data = (const ToggleDeploySpecialAbilityUpdateModuleData *)m_moduleData;
	BfmeAudioEventPrefix136 sound(data->m_soundCC, 0);
	Object *me = m_object;
	((Rva002D9531 *)&sound)->rva002D9531(me->m_id);
	TheAudio->rva004AE5B8Slot25(&sound);
	obj->m_ai->rva0048E6D2();
}

// ?rva004AE6D7@ToggleDeploySpecialAbilityUpdate@@UAEXPAVObject@@@Z @0x004AE6D7
void ToggleDeploySpecialAbilityUpdate::rva004AE6D7(Object *obj)
{
	if (!rva004AE6D7Slot8(0))
		return;
	DeployStyleAIUpdate *ai = obj->m_ai;
	if (!ai)
		return;
	if ((char)obj->rva0028B7C8() || ai->rva004AE6D7Slot111())
		ai->m_command.aiIdle(CMD_FROM_AI);

	const ToggleDeploySpecialAbilityUpdateModuleData *data = (const ToggleDeploySpecialAbilityUpdateModuleData *)m_moduleData;
	BfmeAudioEventPrefix136 sound(data->m_soundC8, 0);
	Object *me = m_object;
	((Rva002D9531 *)&sound)->rva002D9531(me->m_id);
	TheAudio->rva004AE5B8Slot25(&sound);
	ai->rva0048E6AB();
}
