// cl: /MD /EHsc
// ??1Rva00355CD8@@UAE@XZ @0x00355CD8 62B. Dtor storing vtable 0x00814E54,
// conditional virtual slot1 on base+4 (Gen m_next) with arg +0xC, then base
// ??1Gen_004902A0@@UAE@XZ. Evidence: deleting dtor at 0x00355FC1 calls here,
// shared EH scope 0x00B7D529 with sibling 0x00355D66, same flags.
class Gen_004902A0
{
public:
	virtual ~Gen_004902A0() throw();
	virtual void slot1(int x);
	Gen_004902A0 *m_next; // +4
};

class Rva00355CD8 : public Gen_004902A0
{
public:
	virtual ~Rva00355CD8();
	virtual void slot1(int value);
private:
	int m_minimum; // +8: lower range endpoint, used by slot1
	int m_argC; // +0xC: upper range endpoint, sent by dtor
};

Rva00355CD8::~Rva00355CD8()
{
	if (m_next)
		m_next->slot1(m_argC);
}

// BFME 1 donor 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/GameClient/GUI/Rva00490350ProgressRange.cpp.
// Target vtable RVA 0x00814E54 slot1 points to 0x00355D16 (56B), alongside
// the deleting destructor already emitted here. Target accesses confirm the
// same previous-handler pointer and two integer range endpoints as the donor;
// the float at VA 0x00BCF628 is 0.01f. The donor labels this updateProgress;
// retain this class's target-address identity and existing slot name.
void Rva00355CD8::slot1(int value)
{
    Gen_004902A0 *target = m_next;
    if (target)
    {
        int low = m_minimum;
        int span = m_argC - low;
        float spanReal = (float)span;
        target->slot1(low + (int)(spanReal * ((float)value * 0.01f)));
    }
}

// ?Rva00355C39Interpolate@@YAHHHH@Z
// BFME1 34f59164f6 Common/Rva00490250IntegerLerp.cpp supplies the readable
// formula. Native355C39..355C60 reads three integer stack arguments and
// truncates (b-a) * (t * 0.01f), then adds a; target scale is VA00BCF628.
// The original function name and callers are not recovered. Keep an opaque
// address-derived name beside the independently established range updater.
int Rva00355C39Interpolate(int a, int b, int t)
{
	float factor = (float)t / 100.0f;
	int difference = b - a;
	factor *= (float)difference;
	return a + (int)factor;
}
