// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva001DDF04@Eva@@QAEXXZ @0x001DDF04 (594B), RET 0. Eva's priority worker
// (caller Eva::update 0x001DE261, WB twin 0x00ACB080 in Eva.cpp with "Eva decided
// to play event" / "--failed, no local player" / "--success" / "--failed,
// TheAudio returned" / "--failed, no sound for side"): picks the about-to-play
// event with the highest priority (+0x10 of its info), oldest first; takes the
// local player and its side from TheLivingWorldLogic +0x98 (living world, side
// via +0x40) or ThePlayerList's local player (side at +0x58); computes the play
// position, marks the status (0x001DD7C1), finds the side's sound in the info's
// side-sound map at +0x14, plays it through TheAudio slot 0x64 into +0x74 and,
// when the handle is real (>= 5), stores the mode at +0x78 and optionally runs
// 0x001DDAE1 on the status position; otherwise it looks again.
//
// Shape from the WorldBuilder debug body: everything after the search sits in
// `if (bestIndex != -1)` (a nested block, so `side` shares the loop counter's
// frame slot), keepLooking is cleared at the top of each pass, and the status
// and info records are addressed by byte offsets (i*0x34, i*0x30) off bases
// that are reloaded every iteration. The info record's flag byte is at +0x2D.
// Retail keeps edx (priority) and xmm0/xmm1 live across the call to 0x001DCE4C,
// so that callee's single out-of-line definition and ledger row live here.
#include <map>
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T, L>& a, const _Rb_tree_iterator<T, R>& b)
{ return a._M_node != b._M_node; }
}
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
	T *start() const { return m_start; }
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
	EvaCoord(const EvaCoord &evaCoord) : x(evaCoord.x), y(evaCoord.y), z(evaCoord.z) {}
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
	unsigned char m_pad20[0x2d - 0x20];
	Bool m_2d;					// +0x2D
	unsigned char m_pad2e[0x30 - 0x2e];
};

#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

struct EvaWorldMapPlayer
{
	unsigned char m_pad00[0x14];
	int m_14;					// +0x14
	unsigned char m_pad18[0x40 - 0x18];
	const AsciiString *m_side;			// +0x40
};

#include "../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;

extern GameLogic *TheGameLogic;

#include "../../Include/Common/GameAudio.h"
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
		keepLooking = false;
		Int bestIndex = -1;
		UnsignedInt bestPriority = 0;
		Real bestTime = 0.0f;
		for (UnsignedInt i = 0; i < m_allEventInfos.size(); ++i)
		{
			Rva001DCDAF *st = (Rva001DCDAF *)((char *)m_eventStatus.start() + i * sizeof(Rva001DCDAF));
			if (st->m_aboutToPlayTime >= 0.0f)
			{
				Arg001DCDAF *inf = (Arg001DCDAF *)((char *)m_allEventInfos.start() + i * sizeof(Arg001DCDAF));
				UnsignedInt priority = inf->m_priority;
				Real time = st->rva001DCE4C(inf);
				if (bestIndex == -1 || priority > bestPriority || (priority == bestPriority && time < bestTime))
				{
					bestIndex = i;
					bestTime = time;
					bestPriority = priority;
				}
			}
		}
		if (bestIndex != -1)
		{

			Arg001DCDAF *infoBase = m_allEventInfos.start();
			Arg001DCDAF *info = &infoBase[bestIndex];
			Rva001DCDAF *status = &m_eventStatus[bestIndex];
			Player *localPlayerRTS = 0;
			EvaWorldMapPlayer *localPlayerWorldMap = 0;
			AsciiString side;
			Int inLivingWorld;
			if (TheGameLogic->rva001DCD1C())
			{
				inLivingWorld = 1;
				localPlayerWorldMap = (EvaWorldMapPlayer *)TheLivingWorldLogic->field98;
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
					if (info->m_2d)
					{
						void *where = ((Rva001DCD05 *)status)->rva001DCD05();
						if (where)
							((Rva001DDAE1 *)this)->rva001DDAE1((Coord3D *)where);
					}
				}
			}
		}
	} while (keepLooking);
}
