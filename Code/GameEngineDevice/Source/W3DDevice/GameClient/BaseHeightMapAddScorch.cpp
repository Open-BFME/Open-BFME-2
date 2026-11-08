// ?addScorch@BaseHeightMapRenderObjClass@@QAEXVVector3@@MW4Scorches@@@Z
// Ref: Open-BFME-1@575ba2b04743f190f069805fbdc59936123c45da
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp addScorch.
// Ring-buffer algorithm follows that donor; target array E0/stride1C and state
// 3790/3794/3798 are independently proven by native67EA3..67FCD (298B).
// Target identity: W3DGameClient::addScorch4C7A8 calls67EA3 on
// TheTerrainRenderObject. WWMath Vector3's member copy preserves float stores.
// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /DNDEBUG /MD /Oi- /arch:SSE /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Target signature follows the REL32 call from W3DGameClient::addScorch.
// The array and state offsets are independently established by target bytes.

#include <math.h>
#include "vector3.h"

enum Scorches
{
	SCORCHES_UNKNOWN = 0
};

struct ScorchEntry00067EA3
{
	char unreconstructed00[4];
	Vector3 position;
	float radius;
	int kind;
	unsigned char active;
	char pad[3];
};

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The header keeps the 500 scorch records at +0xE0 as raw storage.
static __forceinline ScorchEntry00067EA3 *scorchEntries(BaseHeightMapRenderObjClass *self)
{
	return reinterpret_cast<ScorchEntry00067EA3 *>(self->unknown00E0);
}

void BaseHeightMapRenderObjClass::addScorch(Vector3 pos, float radius, Scorches type)
{
	float estimate = radius * 0.25f;
	for (int i = 0; i < m_numScorches; ++i)
	{
		ScorchEntry00067EA3 *entry = &scorchEntries(this)[i];
		if (!(fabs((double)(pos.X - entry->position.X)) < estimate))
			continue;
		if (!(fabs((double)(pos.Y - entry->position.Y)) < estimate))
			continue;
		if (!(fabs((double)(radius - entry->radius)) < estimate))
			continue;
		if (entry->kind != type)
			continue;
		scorchEntries(this)[i].active = 0;
		return;
	}
	int slot = m_numScorches;
	if (slot >= 500)
	{
		slot = field3798;
		int next = (slot + 1) % 500;
		field3798 = next;
		--m_numScorches;
	}
	scorchEntries(this)[slot].position = pos;
	scorchEntries(this)[slot].radius = radius;
	scorchEntries(this)[slot].kind = type;
	scorchEntries(this)[slot].active = 0;
	++m_numScorches;
	m_scorchesInBuffer = 0;
}
