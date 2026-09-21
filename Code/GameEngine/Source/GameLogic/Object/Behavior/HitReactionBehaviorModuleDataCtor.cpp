// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ??0HitReactionBehaviorModuleData@@QAE@XZ, retail 0x004591EA, 45 bytes.
// Frameless loop ctor over table 0xC410F0 (HitReactionLifeTimer1 at +8,
// 2 at +C, 3 at +10, HitReactionThreshold1 at +14, 2 at +18, 3 at +1C,
// FastHitsReset at +20, HitsParalyze at +21). Identity is the table plus the
// rowed HitReactionBehavior pool key 0x4591A5 in the same cluster plus
// factory 0x24AE4A news 0x24 sole caller plus proc 0x459217 rowed. Shape:
// flat TU-local class with explicit void*m_vtable (no virtuals, folded
// vtable 0xC4ED70 emits nothing) plus int and float arrays; a single source
// loop over the three timer/threshold pairs reproduces retail's
// and-plus-movss interleaved loop with push-3/pop-edx count materialization.
// Thresholds default to FLT_MAX (pool 0xBBB8E0, float-ref verified).

class HitReactionBehaviorModuleData
{
public:
	HitReactionBehaviorModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04
	int m_lifeTimer[3]; // +0x08
	float m_threshold[3]; // +0x14
	bool m_fastHitsReset; // +0x20
	bool m_hitsParalyze; // +0x21
};

// ??0HitReactionBehaviorModuleData@@QAE@XZ @0x4591EA
HitReactionBehaviorModuleData::HitReactionBehaviorModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4ED70);
	m_fastHitsReset = false;
	m_hitsParalyze = false;
	for (int i = 0; i < 3; ++i)
	{
		m_lifeTimer[i] = 0;
		m_threshold[i] = 3.402823466e+38F;
	}
}
