// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0033A951@Rva0033A951@@QAE_NXZ @0x0033A951 46B: scan 0x368 records for true.
// Evidence: rowed callee 0x002C7253 Rva002C7253::rva002C7253; neighbours 0x0033A920 0x0033A97F.
class Rva002C7253
{
public:
	bool rva002C7253() const;
};

class Rva0033A951
{
public:
	bool rva0033A951();

private:
	unsigned char m_pad000[0x358];
	Rva002C7253 *m_begin; // +0x358
	Rva002C7253 *m_end; // +0x35C
};

bool Rva0033A951::rva0033A951()
{
	for (Rva002C7253 *cur = m_begin; cur != m_end; cur = (Rva002C7253 *)((unsigned char *)cur + 0x368))
	{
		if (cur->rva002C7253())
			return true;
	}
	return false;
}
