// ?DeleteReference@RadarMarker@@QAEXXZ, retail 0x002D76BB, 11 bytes.
//
// WB11076B0 explicitly names RadarMarker::DeleteReference and asserts
// m_refCount > 0 at Radar.cpp:198; native agrees on every instruction.
// Drops the dword count at +8 and when it reaches zero
// tail-jumps through vtable slot 1. Adjacent rowed inc at 0x002D76B7 proves
// the +8 counter offset; callers at 0x004C9BAC 0x004C9C5A 0x004C9D53 and the
// tail-jump wrapper at 0x0004E4E1 prove the release role. Shape matches the
// rowed RefCountClass::Release_Ref at 0x005D1A7D (dec plus virtual slot 0)
// with the count at +8 and the deleter at slot 1. No // cl: line (defaults
// match the frameless 11-byte shape).
class RadarMarker
{
public:
	virtual void v0();
	virtual void v1();

	int m04;
	int m_ref08;
	void DeleteReference();
};

void RadarMarker::DeleteReference()
{
	if (--m_ref08 == 0)
		v1();
}
