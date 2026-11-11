// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: sort-then-forward at 0x174A57 (51B). Early-out when
// +0x18==+0x1C; else cdecl sort(a,b,0x57368A), thiscall 0x17438B(a,b),
// tail-jump to 0x17437D. Address-derived names.
// The comparator's full29B C++ owner now lives in
// FXShaderRendererFlushRenderingTasks.cpp. Bind its real symbol instead
// of baking the callback VA into this caller; its physical argument and
// EAX zero/one result contract are established by that native body.
struct Rva0017368ATask;
unsigned Rva0017368ACompare(const Rva0017368ATask &,const Rva0017368ATask &);

// ?rva00174870@@YAXHHH@Z
struct BfmeAssignRecord32;
namespace _STL {
template <class RandomIt, class Compare> void sort(RandomIt first, RandomIt last, Compare comp);
}
typedef bool (*BfmeAssignRecord32Less)(const BfmeAssignRecord32 &, const BfmeAssignRecord32 &);
class FXShaderRenderer
{
public:
	void PerformRendering(int a, int b);
};
#include "../../../Libraries/Source/WWVegas/WW3D2/Rva00DF6F94GapFillerContext.h"
class Rva00174A57
{
public:
	void rva00174A57();
private:
	char m_pad[0x18];
	int m_18;
	volatile int m_1C;
};

// ?rva00174A57@Rva00174A57@@QAEXXZ
void Rva00174A57::rva00174A57()
{
	if (m_18 == m_1C)
		return;
	_STL::sort<BfmeAssignRecord32 *, BfmeAssignRecord32Less>((BfmeAssignRecord32 *)m_18, (BfmeAssignRecord32 *)m_1C, (BfmeAssignRecord32Less)&Rva0017368ACompare);
	((FXShaderRenderer *)this)->PerformRendering(m_18, m_1C);
	return ((Rva00DF6F94GapFillerContext *)this)->rva0017437D();
}
