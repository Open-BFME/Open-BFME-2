// cl: /O1 /Oi /DNDEBUG /MD
//
// ??0ClickReactionBehaviorModuleData@@QAE@XZ, retail 0x004595F0, 27 bytes.
// ClickReactionBehaviorModuleData frameless store-only ctor over table
// 0xC412F8 (ClickReactionTimer@8 plus ReactionFrames1@C through 5@1C): the
// folded vtable 0x00C4ED70 plus the 600 (0x258) default timer plus a
// compiler stosd run over the five frame slots. Identity is the rowed proc
// 0x45960C (same table) plus the rowed pool key 0x4595AB
// (ClickReactionBehavior) in the same cluster plus factory 0x24AED3 news
// 0x20 sole caller. Shape follows the ReflectDamage trivial-ctor precedent:
// flat TU-local class with explicit void*m_vtable (no virtuals, no vtable
// emission) plus plain-data members. The five zero dwords fall out of an
// inlined fixed-size memset (xor-eax plus lea-edi plus unrolled stosd, no
// rep prefix); the timer and vtable stay body assignments in retail order.
// Row supersedes the sole-caller pin.

#include <cstring>

class ClickReactionBehaviorModuleData
{
public:
	ClickReactionBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_clickReactionTimer; // +8
	int m_reactionFrames1; // +0xC
	int m_reactionFrames2; // +0x10
	int m_reactionFrames3; // +0x14
	int m_reactionFrames4; // +0x18
	int m_reactionFrames5; // +0x1C
};

// ??0ClickReactionBehaviorModuleData@@QAE@XZ @0x4595F0
ClickReactionBehaviorModuleData::ClickReactionBehaviorModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_clickReactionTimer = 0x258;
	memset(&m_reactionFrames1, 0, sizeof(int) * 5);
}
