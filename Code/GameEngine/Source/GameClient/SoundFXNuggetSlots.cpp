// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
//
// ?doFXPos@SoundFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z 107B @0x001E00C3:
// slot 1 of the SoundFXNugget vtable 0x00BDD768 (class and the sound name at
// +0x148 as in SoundFXNuggetCtor.cpp; behaviour is Zero Hour's doFXPos).
// Slot 2 (doFXObj, 0x001E012E, 132B) is defined below; FXList.cpp now only declares it so its ZH
// port no longer emits a conflicting inline copy under the same name.
//
// The local is the shared 0x88-byte audio event (Common/BfmeAudioEventPrefix136.h,
// AudioEventRTS's lead) built by 0x002D97D6 from the name; its position setter
// is the ledger's rowed 0x002D9508, reached through its rowed owner. TheAudio's
// addAudioEvent is slot 0x64.
#include "Common/BfmeAudioEventPrefix136.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Matrix3D;

#include "../../Include/Common/Player.h"

#include "../GameLogic/Object/object.h"

// setPlayerIndex on the event: rowed dword-slot setter 0x0033F15D.
#include "../../Include/Common/Rva0033F15DDwordSlot.h"

// Rowed setter the event's position goes through.
#include "../../Include/GameLogic/Module/Rva002D9508.h"

#include "../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad04[0x148 - 4];
};

class SoundFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	OpaqueRefElement4 m_soundName; // +0x148
};

void SoundFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float, const Coord3D *) const
{
	BfmeAudioEventPrefix136 sound(m_soundName, 0);
	if (primary)
	{
		((Rva002D9508 *)&sound)->rva002D9508(primary);
	}
	TheAudio->addAudioEvent(&sound);
}

// Behaviour is Zero Hour's SoundFXNugget::doFXObj: the event takes the primary's controlling
// player index and its position (the Object's position is the Coord3D at +0x38).
void SoundFXNugget::doFXObj(const Object *primary, const Object *secondary) const
{
	BfmeAudioEventPrefix136 sound(m_soundName, 0);
	if (primary)
	{
		((Rva0033F15DDwordSlot *)&sound)->set(primary->getControllingPlayer()->m_playerIndex);
		((Rva002D9508 *)&sound)->rva002D9508((const char *)primary + 0x38);
	}
	TheAudio->addAudioEvent(&sound);
}
