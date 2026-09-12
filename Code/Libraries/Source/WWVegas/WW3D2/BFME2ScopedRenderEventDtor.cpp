// cl: /EHsc /MD /arch:SSE /G7

void bfmeRva0011F3C0(void);

class BFME2ScopedRenderEvent
{
public:
	~BFME2ScopedRenderEvent();
};

BFME2ScopedRenderEvent::~BFME2ScopedRenderEvent()
{
	bfmeRva0011F3C0();
}
