// cl: /DNDEBUG /MD
// ?rva000D1C10@Rva000D1C10@@QAEXXZ @0x000D1C10 115B
// Leaf fade-step helper (no callees). State at +8 with value at +0xC ramped
// by 1/12 per step clamped 0..1. Caller at 0x000D28BC in unclaimed 0x000D2301.

class Rva000D1C10
{
public:
	void rva000D1C10();

private:
	void *m_vtable; // +0
	int m_pad04; // +4
	int m_state; // +8
	float m_value; // +0x0C
};

void Rva000D1C10::rva000D1C10()
{
	switch (m_state) {
	case 0: {
		float v = m_value + 0.083333336f;
		m_value = v;
		if (v >= 1.0f) {
			m_state = 1;
			m_value = 1.0f;
		}
		return;
	}
	case 1:
		m_value = 1.0f;
		return;
	case 2: {
		float v = m_value - 0.083333336f;
		m_value = v;
		if (v <= 0.0f) {
			m_state = 3;
			m_value = 0.0f;
		}
		return;
	}
	case 3:
		m_value = 0.0f;
		return;
	default:
		return;
	}
}
