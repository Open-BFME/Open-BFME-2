// cl: /MD
// ??1Rva005F74BA@@QAE@XZ retail 0x005F74BA 26B
// Evidence: same 26B owning-pointer shape as rowed clear 0x005F74A0 via rowed dtor 0x005F6AB0 plus operator delete 0x0002FD60; needed as array element dtor for outer 0x005F75C9 via EH vector dtor.
void __cdecl operator delete(void *p);

namespace StrategicHUD { class BuildQueueDetailsMovieClip { public: class Impl { public: class QueuedIconSlot; }; }; }
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot
{
public:
    ~QueuedIconSlot();
};

struct Rva005F74BA
{
    StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *m_ptr;
    ~Rva005F74BA();
};

Rva005F74BA::~Rva005F74BA()
{
    StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot *p = m_ptr;
    m_ptr = 0;
    if (p)
    {
        p->StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::~QueuedIconSlot();
        ::operator delete(p);
    }
}
