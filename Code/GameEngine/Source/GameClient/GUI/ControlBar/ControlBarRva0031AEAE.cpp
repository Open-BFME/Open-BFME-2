// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// ?rva0031AEAE@ControlBar@@QAEXPAH0@Z @ 0x0031AEAE 27B: ControlBar copy
// +0x288/+0x28C to out params. Evidence: gap between 0x0031AE13 and
// 0x0031AEC9 plus caller 0x0009FA82 plus ret 8 two-pointer shape.
typedef bool Bool;
#include "subsystem_interface.h"
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"
class ControlBar : public SubsystemInterface
{
public:
	void rva0031AEAE(int *a, int *b);

private:
	char m_pad0C[0x288 - 0x0C];
	ICoord2D m_controlBarBackgroundMarkerPos;
};

void ControlBar::rva0031AEAE(int *a, int *b)
{
	*a = m_controlBarBackgroundMarkerPos.x;
	*b = m_controlBarBackgroundMarkerPos.y;
}
