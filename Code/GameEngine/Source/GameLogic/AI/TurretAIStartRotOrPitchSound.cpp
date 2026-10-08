// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// TurretAI::startRotOrPitchSound, retail 0x004D8B50..0x004D8C23 (211 bytes,
// EH). Zero Hour's TurretAI.cpp method in its BFME form, which BFME 1's
// TurretAIOwnerAndMachine.cpp donor also shows: unless the turret sound is
// already playing, the owner's drawable is asked for its "TurretMoveLoop"
// sound (rowed keyed lookup Drawable::rva00274CD8), tagged with the owner's
// ID and started through TheAudio, keeping the playing handle at +0x20.
//
// BFME 2 builds the event as a local (rowed 0x88-byte event ctor 0x002D97D6
// with 0, dtor 0x002D9A43) instead of keeping it as a member; the name and
// the lookup result are temporaries of that one full-expression, released
// right after the event is built, as retail does. TheAudio's
// isCurrentlyPlaying(handle) is slot 52 and addAudioEvent slot 25; the
// object-ID setter is rowed 0x002D9531. Lives apart from TurretAIUpdate.cpp
// so that unit's caller keeps seeing only a declaration.

#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);
	int m_0;
	Rva0036CA00Str m_4;
};

class Drawable
{
public:
	Rva002390CB rva00274CD8(const AsciiString &name);	// keyed sound lookup
};

class Object
{
public:
	Drawable *getDrawable() const;
	int getID() const { return m_id; }
private:
	unsigned char m_pad00[0x74];
	int m_id;								// +0x74
};

class Rva002D9531
{
public:
	void rva002D9531(int objectID);			// 0x002D9531, AudioEventRTS::setObjectID
};

template <int N> class TurretAudioSlots : public TurretAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class TurretAudioSlots<0>
{
};

class TurretAudioPart1 : public TurretAudioSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);	// slot 25
};

template <int N> class TurretAudioMore : public TurretAudioMore<N - 1>
{
public:
	virtual void more(char (*)[N]);
};
template <> class TurretAudioMore<0> : public TurretAudioPart1
{
};

class AudioManager : public TurretAudioMore<26>
{
public:
	virtual bool isCurrentlyPlaying(int handle);	// slot 52
};
extern AudioManager *TheAudio;

class TurretAI
{
private:
	void startRotOrPitchSound();

	unsigned char m_pad00[0x10];
	Object *m_owner;						// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	int m_turretRotOrPitchHandle;			// +0x20
};

void TurretAI::startRotOrPitchSound()
{
	if (!TheAudio->isCurrentlyPlaying(m_turretRotOrPitchHandle))
	{
		Drawable *drawable = m_owner->getDrawable();
		if (drawable)
		{
			BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&drawable->rva00274CD8(AsciiString("TurretMoveLoop")).m_4, 0);
			reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531(m_owner->getID());
			m_turretRotOrPitchHandle = TheAudio->addAudioEvent(&sound);
		}
	}
}
