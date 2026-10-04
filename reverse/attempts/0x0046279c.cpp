// ?doLoadSound@OpenContain@@MAEXXZ
// partial score=0.99 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
//
// OpenContain::doLoadSound, retail 0x0046279C (143 bytes), and
// OpenContain::doUnloadSound, retail 0x0046282B (128 bytes), ported from Zero
// Hour's GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference). Slots 21 and 22
// of OpenContain's behavior-module vftable 0x00C435E8 (shared by the
// GarrisonContain / TransportContain / TunnelContain / CaveContain tables).
// Zero Hour's bodies on BFME 2's layout (target evidence): module data +0x04
// with the enter / exit sounds at +0x38 / +0x3C, the object +0x08 (id +0x74),
// m_lastUnloadSoundFrame +0x7C, m_lastLoadSoundFrame +0x80,
// m_loadSoundsEnabled +0xDD. The AudioEventRTS is BFME 2's 0x88-byte event
// (shared header) built through the rowed 0x002D97D6 from the module data's
// sound with flag 0; setObjectID is the rowed 0x002D9531 (reached through the
// address-named view other units use) and TheAudio's addAudioEvent is vslot 25.
#include "Common/BfmeAudioEventPrefix136.h"

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

class Rva002D9531
{
public:
	void rva002D9531(int v); // AudioEventRTS::setObjectID
};

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

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
};

struct OpenContainModuleData
{
	unsigned char m_pad00[0x38];
	OpaqueRefElement4 m_enterSound; // +0x38
	OpaqueRefElement4 m_exitSound; // +0x3C
};

class OpenContain
{
protected:
	virtual void doLoadSound();
	virtual void doUnloadSound();
	const OpenContainModuleData *getOpenContainModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const OpenContainModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x7C - 0x0C];
	UnsignedInt m_lastUnloadSoundFrame; // +0x7C
	UnsignedInt m_lastLoadSoundFrame; // +0x80
	unsigned char m_pad84[0xDD - 0x84];
	Bool m_loadSoundsEnabled; // +0xDD
};

static inline void setObjectID(BfmeAudioEventPrefix136 &sound, ObjectID id)
{
	((Rva002D9531 *)&sound)->rva002D9531(id);
}

//-------------------------------------------------------------------------------------------------
void OpenContain::doLoadSound()
{
	//
	// play a sound for loading someone into a building
	//
	if( m_loadSoundsEnabled )
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if( now != m_lastLoadSoundFrame )
		{
			if (getOpenContainModuleData())
			{
				BfmeAudioEventPrefix136 enterSound(getOpenContainModuleData()->m_enterSound, 0);
				setObjectID(enterSound, getObject()->getID());
				TheAudio->addAudioEvent(&enterSound);
			}
			// save this frame as the last time we did this sound
			m_lastLoadSoundFrame = now;
		}
	}
}

//-------------------------------------------------------------------------------------------------
void OpenContain::doUnloadSound()
{
	//
	// play a sound for unloading someone from a building ... but don't play more
	// than one per frame (we can do meta unload all commands)
	//
	UnsignedInt now = TheGameLogic->getFrame();
	if( now != m_lastUnloadSoundFrame )
	{
		if (getOpenContainModuleData())
		{
			BfmeAudioEventPrefix136 exitSound(getOpenContainModuleData()->m_exitSound, 0);
			setObjectID(exitSound, getObject()->getID());

			TheAudio->addAudioEvent(&exitSound);
		}
		// save this frame as the last time we did this sound
		m_lastUnloadSoundFrame = now;
	}
}
