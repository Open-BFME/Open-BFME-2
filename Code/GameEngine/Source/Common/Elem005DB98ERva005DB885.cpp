// cl: /MD /DNDEBUG /Oy-
// Built from the banked attempt reverse/attempts/0x005db885.cpp; fix: 0.5 and
// 1.0f are compiler literals (retail constants at VA 0x00BC26F8 and
// 0x00BBB8D8), not extern globals, which is what gives retail's early
// addss and store.
// Elem005DB98E::rva005DB885 @0x005DB885 95B
// Elem time smoothing: delta from timeGetTime, 0<delta<10000 gates float update of m_04/m_0C then m_10 stamp.
// Evidence: caller 0x005DBF09 passes eax from peekPing as this with dword arg; same Elem005DB98E layout and IAT timeGetTime as next 0x005DB8F7.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct Elem005DB98E
{
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	unsigned long m_10;
	char m_14[4];
public:
	void rva005DB885(int a);
};

void Elem005DB98E::rva005DB885(int a)
{
	unsigned long now = timeGetTime();
	a = (int)(now - (unsigned long)a);
	if (a >= 10000)
		return;
	if (a <= 0)
		return;
	m_04 = (float)((double)(m_0C * m_04) + (double)a * 0.5);
	m_0C += 1.0f;
	m_04 /= m_0C;
	m_10 = timeGetTime();
}
