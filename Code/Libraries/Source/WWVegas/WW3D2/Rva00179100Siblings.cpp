// cl: /DNDEBUG /MD
// ?SetFlag@Rva00179100@@QAEX_N@Z, retail 0x00179100 (21 B).
// Register/width-variant sibling of the rowed boolean flag setters
// (ParticleEmitterDefClass::Set_Merge_Intersections 0x001B1640, the
// SegLineRendererClass/StreakRendererClass copies at 0x0015DFF0 and
// 0x00742F00). Same body: test the bool argument, set or clear one flag bit
// and return. The differences are the byte (bool) test, flag bit 1 (value 2)
// and the 0x30 Flags offset, so it is a distinct local order/operand form, not
// a copy. The 0x30 offset is PointGroupClass::Flags as the rowed generic
// Set_Flag at 0x00179060 proves (it computes 1<<flag into the same +0x30), so
// the class is outlined here under an honest address-derived name rather than
// claiming a method name no symbol proves. No callers; the no-name method is
// reachable only through the class's own translation unit.

class Rva00179100
{
public:
	void SetFlag(bool onoff);
private:
	char m_pad[0x30];
	unsigned int m_flags;
};

void Rva00179100::SetFlag(bool onoff)
{
	if (onoff)
		m_flags |= 2;
	else
		m_flags &= ~2;
}
