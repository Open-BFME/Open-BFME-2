// cl: /MD /DNDEBUG
// ?rva005DB8F7@Elem005DB98E@@QAEXMMM@Z 0x005DB8F7 49B
// Sets three floats at +4 +8 +0xC and timeGetTime at +0x10 on Elem005DB98E (20B element).
// Evidence: caller 0x5DBEC7 passes eax from peekPing as this with three floats; IAT timeGetTime.
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
	void rva005DB8F7(float a, float b, float c);
};

void Elem005DB98E::rva005DB8F7(float a, float b, float c)
{
	m_04 = a;
	m_08 = b;
	m_0C = c;
	m_10 = timeGetTime();
}
