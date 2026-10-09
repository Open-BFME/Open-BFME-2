// ?rva001DDF04@Eva@@QAEXXZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva001DDF04@Eva@@QAEXXZ
// Retail 0x001DDF04..0x001DE156 (594 bytes). BANKED NEAR MISS (score ~0.97):
// same size; 13 instruction-level differences, all in the best-event search
// loop's induction variables: retail keeps the status offset in [ebp-0x1C]
// and reloads m_eventStatus' base (+0x5C) each iteration, this build makes a
// pointer IV from a hoisted base; plus the post-loop +0x1C load order.
// Retail keeps edx (priority) and xmm0/xmm1 live across the call to
// rva001DCE4C, so that callee must be compiled in the same TU (it is
// defined below only for that reason; it is rowed in
// Code/GameEngine/Source/GameLogic/System/Rva001DCDAF.cpp). Without the
// definition the base reload matches but the xmm/edx allocation does not.
// Tried: reference/pointer/index forms of the status and info access, Int vs
// UnsignedInt index, WB-shaped `better` flag and keepLooking init,
// definition order. The map scan matched once end() was cached (WB shape).
//
// Eva (caller Eva::update at 0x001DE261, WB twin 0x00ACB080 in Eva.cpp with
// "Eva decided to play event" / "--failed, no local player" / "--success" /
// "--failed, TheAudio returned" / "--failed, no sound for side"): picks the
// about-to-play event with the highest priority (+0x10 of its info), oldest
// first; takes the local player and its side from TheLivingWorldLogic +0x98
// (living world, side via +0x40) or ThePlayerList's local player (side at
// +0x58); computes the play position (getPlayPositionForEvent), marks the
// status (0x001DD7C1), finds the side's sound in the info's side-sound map at
// +0x14, plays it through TheAudio slot 0x64 into +0x74 and, when the handle
// is real (>= 5), stores the mode at +0x78 and optionally runs 0x001DDAE1 on
// the status position; otherwise it looks again.
#include <map>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

template <class T> class EvaVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { return m_start[i]; }
	const T &operator[](UnsignedInt i) const { return m_start[i]; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

struct Vec001DCDAF
{
	Real x;
	Real y;
	Real z;
};

struct EvaCoord
{
	EvaCoord() {}
	EvaCoord(const EvaCoord &p) : x(p.x), y(p.y), z(p.z) {}
	EvaCoord(Real ax, Real ay, Real az) : x(ax), y(ay), z(az) {}
	Real x;
	Real y;
	Real z;
};

typedef _STL::map<AsciiString, OpaqueRefElement4> EvaSideSoundMap;

// One event's info record (0x30 bytes).
struct Arg001DCDAF
{
	unsigned char m_pad00[4];
	UnsignedInt m_04;				// +0x04
	unsigned char m_pad08[0x10 - 0x08];
	UnsignedInt m_priority;				// +0x10
	EvaSideSoundMap m_sideSounds;			// +0x14
	unsigned char m_pad20[0x2c - 0x20];
	Bool m_2c;					// +0x2C
	unsigned char m_pad2d[0x30 - 0x2d];
};

class Player
{
public:
	unsigned char m_pad00[0x54];
	Int m_playerIndex;				// +0x54
	AsciiString m_side;				// +0x58
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local;				// +0x10
};
extern PlayerList *ThePlayerList;

struct EvaWorldMapPlayer
{
	unsigned char m_pad00[0x14];
	int m_14;					// +0x14
	unsigned char m_pad18[0x40 - 0x18];
	const AsciiString *m_side;			// +0x40
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0x98];
	EvaWorldMapPlayer *m_localPlayer;		// +0x98
};
extern LivingWorldLogic *TheLivingWorldLogic;

extern GameLogic *TheGameLogic;

class AudioManager
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
#undef SLOT
	virtual UnsignedInt addAudioEvent(const BfmeAudioEventPrefix136 *event);	// +0x64
};
extern AudioManager *TheAudio;

class Rva0033F15DDwordSlot { public: void set(int value); };	// the event's player index
class Rva002D94CE { public: void rva002D94CE(int value); };
class Rva002D9508 { public: void rva002D9508(const void *position); };
class Rva001DCD05 { public: void *rva001DCD05(); };
struct Coord3D;
class Rva001DDAE1 { public: void rva001DDAE1(Coord3D *pos); };

// One event's status record (0x34 bytes).
class Rva001DCDAF
{
public:
	Real rva001DCE4C(const Arg001DCDAF *info);
	void rva001DD7C1(Arg001DCDAF *info, const Vec001DCDAF *position);
	EvaCoord getPlayPositionForEvent(const Arg001DCDAF *info, Player *localPlayerRTS, EvaWorldMapPlayer *localPlayerWorldMap) const;

	Real m_blockedTime;				// +0x00
	Real m_aboutToPlayTime;				// +0x04
	unsigned char m_pad08[0x34 - 0x08];
};

Real Rva001DCDAF::rva001DCE4C(const Arg001DCDAF *a)
{
	return (Real)a->m_04 - m_aboutToPlayTime;
}

class Eva
{
public:
	void rva001DDF04();

private:
	unsigned char m_pad00[0x1c];
	EvaVectorView<Arg001DCDAF> m_allEventInfos;	// +0x1C
	unsigned char m_pad28[0x5c - 0x28];
	EvaVectorView<Rva001DCDAF> m_eventStatus;	// +0x5C
	unsigned char m_pad68[0x74 - 0x68];
	UnsignedInt m_playingHandle;			// +0x74
	Int m_playingInLivingWorld;			// +0x78
};

void Eva::rva001DDF04()
{
	Bool keepLooking;
	do
	{
		Int bestIndex = -1;
		UnsignedInt bestPriority = 0;
		Real bestTime = 0.0f;
		for (UnsignedInt i = 0; i < m_allEventInfos.size(); ++i)
		{
			if (m_eventStatus[i].m_aboutToPlayTime >= 0.0f)
			{
				UnsignedInt priority = m_allEventInfos[i].m_priority;
				Real time = m_eventStatus[i].rva001DCE4C(&m_allEventInfos[i]);
				if (bestIndex == -1 || priority > bestPriority || (priority == bestPriority && time < bestTime))
				{
					bestIndex = i;
					bestTime = time;
					bestPriority = priority;
				}
			}
		}
		if (bestIndex == -1)
			return;

		Arg001DCDAF *info = &m_allEventInfos[bestIndex];
		Rva001DCDAF *status = &m_eventStatus[bestIndex];
		Player *localPlayerRTS = 0;
		EvaWorldMapPlayer *localPlayerWorldMap = 0;
		AsciiString side;
		Int inLivingWorld;
		if (TheGameLogic->rva001DCD1C())
		{
			inLivingWorld = 1;
			localPlayerWorldMap = TheLivingWorldLogic->m_localPlayer;
			if (localPlayerWorldMap == 0)
				return;
			side = *localPlayerWorldMap->m_side;
		}
		else
		{
			inLivingWorld = 0;
			localPlayerRTS = ThePlayerList->getLocalPlayer();
			if (localPlayerRTS == 0)
				return;
			side = localPlayerRTS->m_side;
		}

		EvaCoord pos = status->getPlayPositionForEvent(info, localPlayerRTS, localPlayerWorldMap);
		status->rva001DD7C1(info, (const Vec001DCDAF *)&pos);

		keepLooking = true;
		EvaSideSoundMap::iterator it = info->m_sideSounds.begin();
		EvaSideSoundMap::iterator end = info->m_sideSounds.end();
		for (; it != end; ++it)
		{
			if (side.compareNoCase((*it).first) == 0)
				break;
		}
		if (it != end && (*it).second.referent != 0)
		{
			BfmeAudioEventPrefix136 speech((*it).second, 0);
			if (localPlayerRTS)
				((Rva0033F15DDwordSlot *)&speech)->set(localPlayerRTS->m_playerIndex);
			if (localPlayerWorldMap)
				speech.m_int70 = localPlayerWorldMap->m_14;
			((Rva002D94CE *)&speech)->rva002D94CE(inLivingWorld);
			((Rva002D9508 *)&speech)->rva002D9508(&pos);
			m_playingHandle = TheAudio->addAudioEvent(&speech);
			if (m_playingHandle >= 5)
			{
				m_playingInLivingWorld = inLivingWorld;
				keepLooking = false;
				if (info->m_2c)
				{
					void *where = ((Rva001DCD05 *)status)->rva001DCD05();
					if (where)
						((Rva001DDAE1 *)this)->rva001DDAE1((Coord3D *)where);
				}
			}
		}
	} while (keepLooking);
}
