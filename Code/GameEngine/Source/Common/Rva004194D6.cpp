// cl: /MD
// ?rva004194D6@Rva004194D6@@QAEXXZ, retail 0x004194D6, 52 bytes.
// State gate at +0x38 with 8-float threshold check at +0x14 against global at 0x00BBAEAC; sets 1 or 0.
// Evidence: callers 0x00419510 0x00419577 share +0x38 state; prev stlport next ConstIntGetters; float loop with comiss ja matches SSE shape.
extern const float BfmeZeroRange;

class Rva004194D6
{
public:
	void rva004194D6();
	bool rva0041950A();
private:
	char m_pad0[0x10];
	int m_10;
	float m_floats[8];
	char m_pad34[4];
	int m_38;
};

void Rva004194D6::rva004194D6()
{
	if (m_38 != 2)
		return;
	if (m_10 >= 100) {
		m_38 = 0;
		return;
	}
	for (int i = 0; i < 8; i++) {
		if (m_floats[i] > BfmeZeroRange) {
			m_38 = 1;
			return;
		}
	}
	m_38 = 0;
}

bool Rva004194D6::rva0041950A()
{
	if (m_38 == 2)
		rva004194D6();
	return m_38;
}
