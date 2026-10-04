// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
//
// ?doFXPos@SoundFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z 107B @0x001E00C3:
// slot 1 of the SoundFXNugget vtable 0x00BDD768 (class and the sound name at
// +0x148 as in SoundFXNuggetCtor.cpp; behaviour is Zero Hour's doFXPos).
// Slot 2 (doFXObj, 0x001E012E) is held back: FXList.cpp's ZH port emits an
// inline copy under the same name (see reverse/re_attempts.log).
//
// The local is the shared 0x88-byte audio event (Common/BfmeAudioEventPrefix136.h,
// AudioEventRTS's lead) built by 0x002D97D6 from the name; its position setter
// is the ledger's rowed 0x002D9508, reached through its rowed owner. TheAudio's
// addAudioEvent is slot 0x64.
#include "Common/BfmeAudioEventPrefix136.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class Object;

// Rowed setter the event's position goes through.
class Rva002D9508
{
public:
	void rva002D9508(const void *position);
};

class AudioManager
{
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
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event); // +0x64
};

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
