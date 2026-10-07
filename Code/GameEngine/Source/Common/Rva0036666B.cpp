// cl: /MD
// ?rva0036666B@Rva0036666B@@QAE_NXZ 0x0036666B 16B via two-dword non-zero check at +0x34/+0x38
// Evidence: retail xor/cmp/jne/cmp/je/xor/inc shape; callers test al (e.g. 0x002E71D4 test al al); neighbours in Code/GameEngine/Source/Common.

class Rva00366B30
{
public:
	void rva00366B77();
};

class Rva00366E2E
{
public:
	void rva00366E2E();
};

class Rva0036666B
{
public:
	char m_pad00[0x30];
	bool m_b30;
	char m_pad31[3];
	int m_a34;
	int m_b38;
	bool rva0036666B();
	bool rva0036736E(bool b);
};

bool Rva0036666B::rva0036666B()
{
	return m_a34 != 0 || m_b38 != 0;
}

// ?rva0036736E@Rva0036666B@@QAE_N_N@Z, retail 0x0036736E, 39 bytes.
// Setter with change detection at +0x30: same bool returns false, otherwise stores
// and dispatches by +0x34 to rva00366E2E (nonzero) or rva00366B77 (zero), true.
// Evidence: pinned name, same +0x30/+0x34 and callees as packet, caller 0x002E722A,
// neighbour rva0036666B same class.
bool Rva0036666B::rva0036736E(bool b)
{
	if (b == m_b30) {
		return false;
	}
	int sel = m_a34;
	m_b30 = b;
	if (sel != 0) {
		((Rva00366E2E *)this)->rva00366E2E();
	} else {
		((Rva00366B30 *)this)->rva00366B77();
	}
	return true;
}
