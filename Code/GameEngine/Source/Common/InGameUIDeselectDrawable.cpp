// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /arch:SSE /G7
// stlport
// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z @0x0029F34F 136B
// evidence: InGameUI slot57 deselect via BFME1 donor plus retail offsets plus rowed helpers
#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include <algorithm>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

enum ObjectID
{
	OBJECTID_NONE = 0
};

class Drawable
{
public:
	void rva00276B95();

	char m_pad00[0x43c];
	bool m_selected;
};

class ControlBar;
class BfmeWorldRV { public: void rva0031AA4B(int); };

extern ControlBar *TheControlBar;

class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }

private:
	unsigned char m_unmodelled000[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva0029ACA0 { public: void rva0029ACC7(int); };

typedef _STL::list<Drawable *> BfmeDrawableList;

class InGameUI
{
public:
	virtual void deselectDrawable(Drawable *draw);

protected:
	void evaluateSoloNexus(Drawable *newlyAddedDrawable = 0);

private:
	unsigned char m_unmodelled004[0x1c];
	BfmeDrawableList m_selectedDrawables;
	unsigned char m_unmodelled024[0x544];
	int m_selectCount;
	unsigned char m_unmodelled56C[0x4];
	unsigned int m_frameSelectionChanged;
};

// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z retail 0x0029F34F 136B
// Slot 57 deselect mirror of slot 56 selectDrawable at 0x002A3805.
// Evidence: Drawable flag +0x43C with out-of-line clear 0x00276B95;
// frame +0x570 count +0x568 list +0x20 via rowed ObjectID find 0x0029B694
// and rowed removeRecycle 0x0029DFE9 with same pushes as list erase;
// evaluateSoloNexus 0x0029B967 with 0; ControlBar 0x0031AA4B;
// reset 0x0029ACC7 with 0. BFME1 donor InGameUIDeselectDrawable.
void InGameUI::deselectDrawable(Drawable *draw)
{
	if (!draw->m_selected)
		return;
	m_frameSelectionChanged = TheGameLogic->getFrame();
	draw->rva00276B95();
	_STL::list<ObjectID>::iterator findIt = _STL::find(((_STL::list<ObjectID> *)&m_selectedDrawables)->begin(), ((_STL::list<ObjectID> *)&m_selectedDrawables)->end(), *(ObjectID *)&draw);
	m_selectedDrawables.erase(*(BfmeDrawableList::iterator *)&findIt);
	--m_selectCount;
	evaluateSoloNexus(0);
	((BfmeWorldRV *)TheControlBar)->rva0031AA4B((int)draw);
	((Rva0029ACA0 *)this)->rva0029ACC7(0);
}
