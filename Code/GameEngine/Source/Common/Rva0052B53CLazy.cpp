// cl: /O1
// ?rva0052B53C@Rva0052B53C@@QAEXXZ @0x0052B53C 29B. Unlock lane: lazy MD5Final
// of digest at +0x41 with ctx ptr at +0x54 guarded by flag at +0x58; callers
// at 0x002DE265/0x0052B562; unblocks 0x0052B559. Prev/next are Disp getters
// (no // cl:); /O1 for pop-pop cleanup and cmp-byte guard.
struct MD5_CTX
{
	char m_pad[0x58];
};
void __cdecl MD5Final(unsigned char digest[16], MD5_CTX *context);
void __cdecl MD5Init(MD5_CTX *context);
void __cdecl MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputLen);

class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);
};
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

typedef int Int;

class Rva009D8630BlockWriter
{
public:
	Rva009D8630BlockWriter();
	virtual ~Rva009D8630BlockWriter();
	char m_pad[0x40 - 4];
};

class Rva0052B53C : public Rva009D8630BlockWriter
{
public:
	Rva0052B53C(unsigned char v);
	void rva0052B53C();
	unsigned char *rva0052B559();
	void rva0052B4FF(void *a, const void *b, unsigned int c);
private:
	unsigned char m_0040;
	unsigned char m_digest[16];
	char m_pad2[3];
	MD5_CTX *m_ctx;
	unsigned char m_done;
};
Rva0052B53C::Rva0052B53C(unsigned char v)
{
	m_0040 = v;
	m_ctx = new MD5_CTX;
	m_done = 0;
	ji_006291ae(m_digest, 0, 0x10);
	MD5Init(m_ctx);
}
void Rva0052B53C::rva0052B53C()
{
	if (m_done == 0) {
		MD5Final(m_digest, m_ctx);
		m_done = 1;
	}
}

// ?rva0052B559@Rva0052B53C@@QAEPAEXZ retail 0x0052B559 19B. Chain lane: calls
// this session's 0x0052B53C if flag at +0x58 is 0 then returns digest at
// +0x41; caller at 0x002DE272.
unsigned char *Rva0052B53C::rva0052B559()
{
	if (m_done == 0)
		rva0052B53C();
	return m_digest;
}

// ?rva0052B4FF@Rva0052B53C@@QAEXPAXPBXI@Z @0x0052B4FF 61B. vslot slot 38
// offset 0x98 of vtable 0x00C68620; forwards (context/bytes/count) to
// XferSave::XferEnum then MD5Update(ctx at +0x54) unless null bytes with
// nonzero count or done flag at +0x58; callees rowed.
void Rva0052B53C::rva0052B4FF(void *a, const void *b, unsigned int c)
{
	if (b == 0 && c != 0)
		return;
	if (m_done != 0)
		return;
	((XferSave *)this)->XferSave::XferEnum(a, b, c);
	MD5Update(m_ctx, (unsigned char *)b, c);
}
