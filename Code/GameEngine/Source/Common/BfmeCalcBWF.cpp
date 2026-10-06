// BFME coordinate transform at RVA 0x0087E0D0; callers carry the angle as float bits.
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
class BfmeRetBWF { public: float x; float y; float z; };
class BfmeCalcBWF
{
public:
	bool bfmeCalcBWF(BfmeRetBWF *one, float value, BfmeRetBWF *two);
private:
	char pad[8]; float m_field0x8; float m_field0xc;
};
bool BfmeCalcBWF::bfmeCalcBWF(BfmeRetBWF *one, float angle, BfmeRetBWF *two)
{
	BfmeRetBWF *source = *(BfmeRetBWF * volatile *)&one;
	const float firstZero = 0.0f;
	*two = *source;
	if (m_field0x8 == firstZero && m_field0xc == 0.0f) return false;
	float sine=(float)sin(angle); float cosine=(float)cos(angle);
	two->x += cosine*m_field0x8 + sine*m_field0xc;
	two->y += sine*m_field0x8 + cosine*m_field0xc;
	return true;
}


// Shared read-only zero, following BFME1's data-provider fix (e07a7b29f).
// Six matched BFME2 references across five sources place this scalar at
// VA 0x00BBAEAC, whose four initialized bytes are zero. BfmeZeroRange is
// the existing project alias; this placement does not establish a retail owner.
// BFME1 donor e07a7b29f, reviewed at d6db6bfa4f. This provider retains the
// float memory loads that constant substitution widens in double-return bodies.
extern const float BfmeZeroRange = 0.0f;
