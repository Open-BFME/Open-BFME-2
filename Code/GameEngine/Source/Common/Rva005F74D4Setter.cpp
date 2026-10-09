// cl: /MD
// ?rva005F74D4@Rva005F74D4@@QAEXPAVQueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@@Z retail 0x005F74D4 35B
// Evidence: cmp new vs old at +0 then store new before dtor plus delete; rowed dtor 0x005F6AB0 plus rowed operator delete 0x0002FD60; caller 0x005F8015; precedent plus4 forwarder file layout
namespace StrategicHUD { class BuildQueueDetailsMovieClip { public: class Impl { public: class QueuedIconSlot; }; }; }
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot
{
public:
	virtual ~QueuedIconSlot();
};

class Rva005F74D4
{
public:
	void rva005F74D4(StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *p);
private:
	StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *m_ptr00;
};

void Rva005F74D4::rva005F74D4(StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *p)
{
	if (p != m_ptr00) {
		StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *old = m_ptr00;
		m_ptr00 = p;
		if (old) {
			old->StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::~QueuedIconSlot();
			::operator delete(old);
		}
	}
}
