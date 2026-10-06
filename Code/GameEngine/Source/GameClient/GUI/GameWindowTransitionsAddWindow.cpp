// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?addWindow@TransitionGroup@@QAEXPAVTransitionWindow@@@Z, retail 0x001DC19F, 20 bytes.
// Null-guarded forward to rowed list<int>::push_back at 0x0005548F (VA 0x0045548F).
// Target evidence (retail bytes, not pin alone):
// 83 7C 24 04 00 / 74 0A / 8D 44 24 04 / 50 / E8 (to 0x5548F) / C2 04 00.
// Callchain: parseWindow 0x1DCB2F (53B, pending review, same TU family) calls
// ((TransitionGroup*)instance)->addWindow(transWin) with instance=group.
// List home: Rva001DC0EC 0x14 layout (rowed ctor 0x1DC0C7, dtor 0x1DC0EC):
// list<int> at +0, dir +4 (=1), cur +8 (=0), name data +0xC (=0), fireOnce +0x10 (=false).
// Retail table 0x7DBBCC FireOnce offset 16 proves +0x10 (Groups TU view), not ZH +0.
// Donors (shape only, list home target-derived): ZH GameWindowTransitions.cpp
// TransitionGroup::addWindow (null-guard + push_back) and BFME1 6583b3c1
// GameWindowTransitions_parseWindow.cpp (same, list at +4 in BFME1, NOT reused;
// BFME2 list at +0 per ctor/dtor). No ZH inline-list body copied.
// Providers: list<int>::push_back 0x0005548F (matched, stlport_list_int_o1.cpp),
// no new pins, no DIR32, no EH/frame. TransitionWindow opaque (only pointer
// passed; genuine 0x18 view in GroupTotalFrames TU, not needed here).
// TU-scoped only, no shared-header edits, no new class view beyond proven 0x14.
#include <list>

class TransitionWindow;

class TransitionGroup
{
public:
	void addWindow(TransitionWindow *window);
private:
	_STL::list<int, _STL::allocator<int> > m_list; // +0, genuine Rva001DC0EC home
	int m_04; // +0x04 direction
	int m_08; // +0x08 current frame
	int m_0C; // +0x0C name data
	bool m_10; // +0x10 fireOnce
};

void TransitionGroup::addWindow(TransitionWindow *window)
{
	if (!window)
		return;
	m_list.push_back(*(int *)&window);
}
