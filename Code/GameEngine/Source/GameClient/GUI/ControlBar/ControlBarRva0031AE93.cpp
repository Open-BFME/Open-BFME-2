// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// ?rva0031AE93@ControlBar@@QAEXPAH0@Z @ 0x0031AE93 27B: ControlBar copy
// +0x280/+0x284 to out params. Evidence: sibling 0x0031AEAE shares
// two-out shape plus caller 0x0009FB63 plus ret 8.
typedef bool Bool;
#include "subsystem_interface.h"
class ControlBar : public SubsystemInterface
{
public:
	void rva0031AE93(int *a, int *b);

private:
	char m_pad0C[0x280 - 0x0C];
	int m_0280;
	int m_0284;
};

void ControlBar::rva0031AE93(int *a, int *b)
{
	*a = m_0280;
	*b = m_0284;
}
