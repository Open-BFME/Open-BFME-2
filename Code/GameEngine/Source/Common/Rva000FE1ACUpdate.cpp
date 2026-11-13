// cl: /DNDEBUG /MD
// platformsdk
//
// ?rva000FE1AC@WaterTracksRenderSystem@@QAEXXZ @0x000FE1AC 91B.
// Container at +0x10 tail iterated via FeNode +0xb0 next; +0x3c flag selects
// +0x74 += 0x21 vs releaseTrack move; time base g_00DEC224 init flag and
// g_00DEC220 with timeGetTime IAT; caller 0x00100068; callee
// ?releaseTrack@WaterTracksRenderSystem rowed. _ReadWriteBarrier is reconstruction shaping
// to keep sub mem + add mem (without it cl folds to mov [mem],eax).

#include <windows.h>

struct FeNode
{
	unsigned char m_pad0[0x3c];
	unsigned char m_flag3c;
	unsigned char m_pad1[0x74 - 0x3d];
	int m_74;
	unsigned char m_pad2[0xb0 - 0x78];
	FeNode *m_next;
	FeNode *m_prev;

	int update(int elapsed);
};

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/WaterTracksRenderSystem.h"

extern unsigned int g_waterTracksTimeInitialized;
// g_00DEC224: matched references place it at VA 0xdec224 (zero-filled .bss).
unsigned int g_waterTracksTimeInitialized;
extern unsigned long g_00DEC220;
// g_00DEC220: matched references place it at VA 0xdec220 (zero-filled .bss).
unsigned long g_00DEC220;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void WaterTracksRenderSystem::rva000FE1AC()
{
	if (!(g_waterTracksTimeInitialized & 1))
	{
		g_waterTracksTimeInitialized |= 1;
		g_00DEC220 = timeGetTime();
	}
	FeNode *node = reinterpret_cast<FeNode *>(m_usedModules);
	unsigned long cur = timeGetTime();
	unsigned long delta = cur - g_00DEC220;
	_ReadWriteBarrier();
	g_00DEC220 += delta;
	while (node != 0)
	{
		FeNode *next = node->m_next;
		if (node->m_flag3c != 0)
			node->m_74 += 0x21;
		else
			releaseTrack(node);
		node = next;
	}
}

// BF1 f98983a7 W3DWaterTracks.cpp update is a source guide. Native
// FDF3F..FDF4C independently starts after RET4 at FDF3C and ends at its
// own RET4. The WaterTracks system update FE1AC and current bind/editor
// bodies prove the same node's elapsed word at74, flag3C and linksB0/B4.
// FeNode remains the established structural view; the original leaf name
// and its declaration's precise source type are not asserted from the donor.
int FeNode::update(int elapsed)
{
	m_74 += elapsed;
	return 1;
}
