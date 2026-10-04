// cl: /O2
// 0x007EB1C0: FESL hubsingle.cpp ServiceHubImpl singleton factory.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

void *Gen007F0130(unsigned int size);

class ServiceHubImpl
{
public:
	ServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f) throw();

	char m_pad[0x2B0];
};

inline void *operator new(unsigned int, void *p)
{
	return p;
}

void *bfmeGo929C(void);
void Rva007F0120(void *a, void *b);
Rva007EB810Diag *Rva007EB810Get();
void Rva007EBAA0(void);

extern ServiceHubImpl *g_Va0130A588;
extern unsigned char g_Va0130A58C;
extern unsigned char g_Va0130A58D;

ServiceHubImpl *createServiceHubImpl(void *a, void *b, void *c, void *d, void *e, void *f)
{
	void *p = bfmeGo929C();
	if (p == 0)
	{
		Rva007F0120(p, p);
		g_Va0130A58C = 1;
	}
	if (Rva007EB810Get() == 0)
	{
		Rva007EBAA0();
		g_Va0130A58D = 1;
	}
	if (g_Va0130A588)
		Rva007EB810Get()->fail(
			"!ServiceHubImpl::gInstance",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\hubsingle.cpp",
			0x35);
	void *raw = Gen007F0130(0x2B0);
	if (raw)
	{
		g_Va0130A588 = new (raw) ServiceHubImpl(a, b, c, d, e, f);
		return g_Va0130A588;
	}
	g_Va0130A588 = 0;
}
// ?g_Va0130A588@@3PAVServiceHubImpl@@A: the global at VA 0xe09fa4 is ?g_Va0130A588@@3PAVT_007ea120@@A.
#pragma comment(linker, "/alternatename:?g_Va0130A588@@3PAVServiceHubImpl@@A=?g_Va0130A588@@3PAVT_007ea120@@A")

// Primary semantic guide: whole BFME1 createServiceHubImpl.cpp, revision
// 5cc75ddda6455c338a5068307e587a793f96d6b3, blob
// 31ac73344d164781f380891d0a70736bd7cc605c, compiled /O2 without headers.
// Target 658110/58 is bounded by INT3 padding before/after its two returns.
// Native requests 0x2B0 bytes from the established 65D010 allocator, forwards
// six raw argument words unchanged to the rowed 657DD0 ServiceHubImpl
// constructor, and returns either that constructor's receiver or null.
// The known neighboring named factory at 658160 uses the same allocator,
// constructor and allocation size; the wrapper's own original name remains
// unknown. The existing constructor declaration/throw specification is
// retained; no new member layout or assertion of runtime nonthrowing behavior
// is inferred from the wrapper's lack of local exception machinery.
ServiceHubImpl *rva00658110(void *a, void *b, void *c, void *d, void *e, void *f)
{
    void *raw = Gen007F0130(0x2B0);
    return raw ? new (raw) ServiceHubImpl(a, b, c, d, e, f) : 0;
}
