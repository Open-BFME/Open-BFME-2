// ??1BFME2ScopedRenderEvent@@QAE@XZ
// partial score=0.9 date=2026-09-10
// cl: /O1 /MD
//
// BFME2ScopedRenderEvent destructor, retail 0x0011F3C0, 12 bytes.
// Dedicated TU so bfme2_polygon_render.cpp keeps its matched bodies.

class BFME2ScopedRenderEvent
{
public:
	~BFME2ScopedRenderEvent();
};

BFME2ScopedRenderEvent::~BFME2ScopedRenderEvent()
{
	void (*fn)() = *(void (**)())0x00DEDBE0;
	if (fn == 0)
		return;
	fn();
}
