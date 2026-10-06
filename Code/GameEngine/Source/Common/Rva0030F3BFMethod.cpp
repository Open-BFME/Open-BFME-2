// cl: /MD
// ?rva0030F3BF@Rva0030F388@@QAEXM@Z @ 0x0030F3BF 69B: float clamp and guarded broadcast on the same object as 0x0030F388
// Evidence: calls rowed 0x0030F388 with same this; flag at +0x1c shared; vtable slot 1 of 0x00809834 (class of ??1Rva0030F42E opaque deleter); floats at +0x14 (spec int at +0x1c) and +0x18; unblocked by landing 0x0030F388.
struct Rva0030F3BFSpec
{
	char m_pad00[0x1c];
	int m_1c;
};

class Rva0030F388
{
public:
	void rva0030F388();
	void rva0030F3BF(float value);
private:
	char m_00[4];
	char m_listPad[16];
	Rva0030F3BFSpec *m_14;
	float m_18;
	bool m_flag;
};

void Rva0030F388::rva0030F3BF(float value)
{
	if (value < 0.0f)
		return;
	if (!m_flag)
		return;
	float newVal = m_18 + value;
	float limit = (float)m_14->m_1c;
	if (newVal > limit)
	{
		newVal = limit;
		rva0030F388();
	}
	m_18 = newVal;
}
