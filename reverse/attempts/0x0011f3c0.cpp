// ??1BFME2ScopedRenderEvent@@QAE@XZ
// partial score=0.9 date=2026-09-10
// cl: /O2 /DNDEBUG /MD
//
// BFME2ScopedRenderEvent destructor, retail 0x0011F3C0, 12 bytes. If the
// end-event hook is set, tail-jump it; otherwise return.

typedef void (*BfmeRenderEventEndFn)();
extern BfmeRenderEventEndFn g_bfmeRenderEventEnd;

class BFME2ScopedRenderEvent
{
public:
	~BFME2ScopedRenderEvent();
};

BFME2ScopedRenderEvent::~BFME2ScopedRenderEvent()
{
	if (g_bfmeRenderEventEnd)
		g_bfmeRenderEventEnd();
}
