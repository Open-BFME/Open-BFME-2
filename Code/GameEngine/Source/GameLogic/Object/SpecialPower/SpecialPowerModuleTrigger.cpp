// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
//
// SpecialPowerModule::aboutToDoSpecialPower(const Coord3D *), retail
// 0x004939AB (268 bytes). Name and shape carried from Zero Hour's
// SpecialPowerModule.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference); access (protected) follows that
// donor. Target evidence: the sole caller is triggerSpecialPower (pinned
// 0x004941F3) at 0x0049420B; the body notifies TheScriptEngine (0x009FE16C,
// rowed 0x00357E7B) with the controlling player's index (+0x54), the final
// override's name (+0x10) and the object ID (+0x74), then builds the 0x88-byte
// audio event (shared header, rowed ctor 0x002D97D6 with flag 0) from the
// template's +0x34 sound, sets its object ID (rowed 0x002D9531) and queues it
// through TheAudio slot 25; with a location it does the same with the +0x38
// sound, the rowed position setter 0x002D9508 and the player-index setter
// 0x0033F15D. Zero Hour's EVA block is absent from retail. Codegen: the
// script notification is its own block with locals for the ID, the module data
// and the player index; the rest reads the template through a second local.
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Rva002D9531 { public: void rva002D9531(int v); };
class Rva002D9508 { public: void rva002D9508(const void *p); };
class Rva0033F15DDwordSlot { public: void set(int v); };

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AudioManager : public VSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
};
extern AudioManager *TheAudio;

class ScriptEngine
{
public:
	void rva00357E7B(int playerIndex, const AsciiString &name, int id);
};
extern ScriptEngine *TheScriptEngine;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x10];
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_name; }
	const OpaqueRefElement4 *getInitiateSound() const { return &((const SpecialPowerTemplate *)friend_getFinalOverride())->m_initiateSound; }
	const OpaqueRefElement4 *getInitiateAtTargetSound() const { return &((const SpecialPowerTemplate *)friend_getFinalOverride())->m_initiateAtLocationSound; }
	AsciiString m_name;
	char m_pad14[0x34 - 0x14];
	OpaqueRefElement4 m_initiateSound;
	OpaqueRefElement4 m_initiateAtLocationSound;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	char m_pad[0x54];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	int getID() const { return m_id; }
	char m_pad[0x74];
	int m_id;
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

class SpecialPowerModuleData : public ModuleData
{
public:
	int m_unknown4;
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
	Object *getObject() const { return m_object; }
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return (const SpecialPowerModuleData *)m_moduleData; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return getSpecialPowerModuleData()->m_specialPowerTemplate; }
protected:
	void aboutToDoSpecialPower(const Coord3D *location);
	const ModuleData *m_moduleData;
	Object *m_object;
};

void SpecialPowerModule::aboutToDoSpecialPower(const Coord3D *location)
{
	{
		Object *obj = getObject();
		int id = obj->getID();
		const SpecialPowerModuleData *d = getSpecialPowerModuleData();
		int idx = obj->getControllingPlayer()->getPlayerIndex();
		TheScriptEngine->rva00357E7B(idx, d->m_specialPowerTemplate->getName(), id);
	}
	const SpecialPowerModuleData *d = getSpecialPowerModuleData();
	BfmeAudioEventPrefix136 soundToPlay(*d->m_specialPowerTemplate->getInitiateSound(), 0);
	((Rva002D9531 *)&soundToPlay)->rva002D9531(getObject()->getID());
	TheAudio->addAudioEvent(&soundToPlay);

	if (location)
	{
		BfmeAudioEventPrefix136 soundAtLocation(*d->m_specialPowerTemplate->getInitiateAtTargetSound(), 0);
		((Rva002D9508 *)&soundAtLocation)->rva002D9508(location);
		((Rva0033F15DDwordSlot *)&soundAtLocation)->set(getObject()->getControllingPlayer()->getPlayerIndex());
		TheAudio->addAudioEvent(&soundAtLocation);
	}
}
