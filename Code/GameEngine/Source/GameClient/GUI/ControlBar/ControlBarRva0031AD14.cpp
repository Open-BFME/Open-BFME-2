// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// ?rva0031AD14@ControlBar@@QAEXHHHHH@Z @ 0x0031AD14 52B: ControlBar 5-dword
// store to +0x218..+0x228. Evidence: gap between 0x0031ACF5 and 0x0031AE13
// plus callers 0x0031E94C and 0x0031ED2C plus EBP frame with ret 0x14.
typedef bool Bool;
#include "subsystem_interface.h"
class ControlBar : public SubsystemInterface
{
public:
	void rva0031AD14(int a, int b, int c, int d, int e);

private:
	char m_pad0C[0x218 - 0x0C];
	int m_0218;
	int m_021C;
	int m_0220;
	int m_0224;
	int m_0228;
};

void ControlBar::rva0031AD14(int a, int b, int c, int d, int e)
{
	m_0218 = a;
	m_021C = b;
	m_0220 = c;
	m_0224 = d;
	m_0228 = e;
}
