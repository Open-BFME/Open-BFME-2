// cl: /MD /EHsc
// ??1QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@UAE@XZ retail 0x005F6AB0 56 bytes.
// Evidence: chain lane calls helper 0x005F697C then base dtor 0x005F69F5 plus vtable at this sibling of 0x005F6A58.
// Model: virtual dtor over rowed base Rva005F69F5 with helper call via cast.
class Rva005F697C
{
public:
	void rva005F697C();
};

class Rva005F69F5
{
public:
	virtual ~Rva005F69F5();
};

namespace StrategicHUD { class BuildQueueDetailsMovieClip { public: class Impl { public: class QueuedIconSlot; }; }; }
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot : public Rva005F69F5
{
public:
	virtual ~QueuedIconSlot();
};

StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::~QueuedIconSlot()
{
	((Rva005F697C *)this)->rva005F697C();
}
