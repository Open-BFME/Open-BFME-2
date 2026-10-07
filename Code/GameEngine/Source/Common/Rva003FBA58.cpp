// cl: /DNDEBUG /MD /Op
// ?rva003FBA58@Rva003FBA58@@QAEXXZ @0x003FBA58 140B
// Chain lane: calls 0x003FB9C8 just landed; vtable slot 10 of 0x008747B8
// (class of ??1Rva005C4B1B). Prev 0x003FBA0E in Rva003FBA0ERva003FBA0E.cpp
// same layout +0x2C +0x34 +0x3C +0x40 +0x44 +0x48 +0x50 +0x54 float.
// Calls rowed Rva003FB9C8/Rva003FB9EB/Rva003FBA0E helpers and slot 0x30
// with 0; float vs BfmeZeroRange; clears +0x2C via and in zero branch.
class Rva003FBA0E
{
public:
	void rva003FBA0E(int a, int b, int c, int d, int e, float f);
};

class Rva003FB9C8
{
public:
	void rva003FB9C8(int a, int b);
	void rva003FB9EB(int a, int b);
};

class Rva003FBA58
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12(bool a);
	void rva003FBA58();
	void rva003FBAE4(bool enabled);
private:
	char m_pad04[4];
	void *m_08; // +0x08
	char m_pad0C[0x2C - 0x0C];
	int m_2c; // +0x2C
	int m_30;
	int m_34; // +0x34
	int m_38; // +0x38
	int m_3c; // +0x3C
	int m_40; // +0x40
	int m_44; // +0x44
	int m_48; // +0x48
	int m_4c; // +0x4C
	int m_50; // +0x50
	float m_54; // +0x54
	char m_pad58[0xA0 - 0x58];
	float m_a0, m_a4, m_a8;
};

void Rva003FBA58::rva003FBA58()
{
	if (m_50 == 0) {
		if (m_08 != 0) {
			if (m_2c == 2 || (m_2c == 3 && m_54 == 0.0f)) {
				this->s12(0);
			}
		}
		m_2c = 0;
	} else if (m_50 == 1) {
		if (m_2c == 1) {
			((Rva003FB9C8 *)this)->rva003FB9C8(m_34, 1);
			return;
		} else if (m_2c == 2) {
			((Rva003FB9C8 *)this)->rva003FB9EB(m_34, 1);
			return;
		} else if (m_2c == 3) {
			((Rva003FBA0E *)this)->rva003FBA0E(m_3c, m_40, m_44, m_48, 1, m_54);
		}
	}
}

// Native 003FBAE4..003FBB80, 156B, RET4. The receiver and slot +30
// agree with the rowed sibling above; the +A0/+A4/+A8 values are float
// components in retail. Original class and method names remain unknown.
void rva0010E87A(int object, float amount);
void rva0010E676(void *object, float x, float y, float z);

void Rva003FBA58::rva003FBAE4(bool enabled)
{
	if (m_2c != 0) {
		float amount = enabled ? 1.0f : 0.0f;
		if (m_30 == 0)
			rva0010E87A(reinterpret_cast<int>(m_08), amount);
		else if (m_30 == 1)
			rva0010E676(m_08, m_a0 * amount, m_a4 * amount, m_a8 * amount);
		s12(enabled);
		m_2c = 0;
	}
}
