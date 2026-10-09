// cl: /MD /EHsc
// ??1QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAE@XZ retail 0x005F6AB0 56 bytes.
// Evidence: chain lane calls helper 0x005F697C then base dtor 0x005F69F5 plus vtable at this sibling of 0x005F6A58.
// Not virtual: slot 0 of the class's table 0x00C79828 (and of the base's 0x00C797C4) is the
// byte getter 0x004C9990, as slot 0 of WB's QueuedIconSlot table is a 17-byte getter; no table
// holds a deleting dtor, and the holder setter 0x005F74D4 and holder dtor 0x005F74BA call
// 0x005F6AB0 directly before operator delete.
// Model: dtor over rowed base Rva005F69F5 with helper call via cast. The views declare only
// DoSetState, the slot-9 virtual WorldBuilder names (the base's slot 9 is 0x002B22A5).
class Rva005F697C
{
public:
	void rva005F697C();
};

class Rva005F69F5
{
public:
	~Rva005F69F5();
	virtual void DoSetState(int index);
};

namespace StrategicHUD { class BuildQueueDetailsMovieClip { public: class Impl { public: class QueuedIconSlot; }; }; }
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot : public Rva005F69F5
{
public:
	~QueuedIconSlot();
	virtual void DoSetState(int index);
};

StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::~QueuedIconSlot()
{
	((Rva005F697C *)this)->rva005F697C();
}

// ??_GQueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAEPAXI@Z @0x005F6B58 28B:
// retail keeps this scalar deleting dtor but never references it (no vtable slot, call or
// jmp reaches it). A non-inlined delete emits it, as in FamilyDeletingDtors9.cpp.
void famgenDelete(StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *p) { delete p; }
