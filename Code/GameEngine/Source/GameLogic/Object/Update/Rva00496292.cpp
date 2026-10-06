// cl: /DNDEBUG /MD
// ?Rva00496292Destroy@@YAXPAX0@Z 0x00496292 25B destroy range stride 12 via dtor pin
// Evidence: callers at 0x004962C5 and 0x004962F2; calls dtor pin ??1BfmeStringRecord00426A5B@@QAE@XZ at 0x00495C43; add esi 0xc.

struct BfmeStringRecord00426A5B {
	~BfmeStringRecord00426A5B();
	char m_pad[12];
};

void Rva00496292Destroy(void *first, void *last)
{
	BfmeStringRecord00426A5B *p = (BfmeStringRecord00426A5B *)first;
	BfmeStringRecord00426A5B *end = (BfmeStringRecord00426A5B *)last;
	while (p != end) {
		p->~BfmeStringRecord00426A5B();
		++p;
	}
}
