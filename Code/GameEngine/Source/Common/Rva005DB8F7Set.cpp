// cl: /MD /DNDEBUG
// platformsdk
// ?rva005DB8F7@Elem005DB98E@@QAEXMMM@Z 0x005DB8F7 49B
// Sets three floats at +4 +8 +0xC and timeGetTime at +0x10 on Elem005DB98E (20B element).
// Evidence: caller 0x5DBEC7 passes eax from peekPing as this with three floats; IAT timeGetTime.

#include <windows.h>
struct Elem005DB98E
{
public:
	void rva005DB885(int a);
	void rva005DB8F7(float a, float b, float c);
	int m_00; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	float m_0C; // +0x0C
	unsigned long m_10; // +0x10
	char m_14[4]; // +0x14
};

void Elem005DB98E::rva005DB8F7(float a, float b, float c)
{
	m_04 = a;
	m_08 = b;
	m_0C = c;
	m_10 = timeGetTime();
}
