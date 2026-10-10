// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??1Rva0040FB4A@@UAE@XZ @0x0040FB4A 82B (the opaque pin keeps the non-virtual
// spelling; scalar deleting dtor 0x0040FD1C, vtable 0x00C395E4). Unloads the
// Apt level of the screen at +0x24 (TheAptPlayer method 0x00224B7D, WB
// AptPlayer::RemoveLevel, with the screen's +0x274 level id), drains the
// quick-match window list through the direct base-class call 0x00538ADC,
// clears the screen pointer and lets the out-of-line base dtor 0x00538C5F
// (the BfmeQuickMatchScreenBase teardown) run last. Identity unproven.
class Rva00224B7DTarget
{
public:
	bool method(int level);
};
extern Rva00224B7DTarget *TheAptPlayer;

class BfmeQuickMatchScreenBase
{
public:
	virtual void rva00538ADC();
};

struct Rva0040FB4AScreen
{
	char m_pad[0x274];
	int m_274;
};

class Rva00538C5F
{
public:
	virtual ~Rva00538C5F();
};

class Rva0040FB4A : public Rva00538C5F
{
public:
	virtual ~Rva0040FB4A();
private:
	char m_pad04[0x20];
	Rva0040FB4AScreen *m_24;
};

Rva0040FB4A::~Rva0040FB4A()
{
	TheAptPlayer->method(m_24->m_274);
	((BfmeQuickMatchScreenBase *)this)->BfmeQuickMatchScreenBase::rva00538ADC();
	m_24 = 0;
}
