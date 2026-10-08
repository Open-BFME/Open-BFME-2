// ?rva00278440@Rva00278440Host@@QAEXH@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD /EHsc
//
// ?rva00278440@Rva00278440Host@@QAEXH@Z, retail 0x00278440, 111B: Drawable-adjacent
// host member guarded by +0x447/+0x448/+0x44A flags, fills a ref wrapper via
// 0x0027824D, notifies via 0x00278341 and releases via OpaqueRefCounted.
// Evidence: pin ?rva00278440@Rva00278440Host@@QAEXH@Z, LINK BONUS names it,
// callers 0x002784AF and 0x0028FD50, flags /O1 /arch:SSE /G7.

struct Rva0027937BArg;
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva0027937BArg
{
	OpaqueRefCounted *m_ptr;
};

class Rva00278341Host
{
public:
	void rva00278341(int a, int b);
protected:
	unsigned char m_pad0[0x110];
	OpaqueRefCounted *m_x110;
	unsigned char m_pad114[0x447 - 0x114];
	unsigned char m_x447;
	unsigned char m_x448;
	unsigned char m_pad449;
	unsigned char m_x44A;
};

class Rva0027824DHost : public Rva00278341Host
{
public:
	void rva0027824D(Rva0027937BArg *out, int v);
};

class Rva00278440Hold
{
public:
	OpaqueRefCounted *m_p;
	Rva00278440Hold(OpaqueRefCounted *p) : m_p(p) {}
	~Rva00278440Hold()
	{
		if (m_p)
			m_p->Release_Ref();
	}
	OpaqueRefCounted *get() const { return m_p; }
};

class Rva00278440Host : public Rva0027824DHost
{
public:
	void rva00278440(int v);
};

void Rva00278440Host::rva00278440(int v)
{
	if (m_x447 && m_x448 && m_x44A)
	{
		OpaqueRefCounted *raw;
		rva0027824D((Rva0027937BArg *)&raw, v);
		Rva00278440Hold hold(raw);
		if (hold.get() != m_x110)
			rva00278341(v, 0);
	}
}
