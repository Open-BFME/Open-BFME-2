// ?rva002AC2CF@Rva002AC2CFTarget@@QAEXHHH@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva002AC2CF@Rva002AC2CFTarget@@QAEXHHH@Z @0x002AC2CF 113B: two-segment copy via memcpy with empty-string fallback.
// Evidence: vtable 0x00BFDC6C#1 forwarder tail-jmps with 3 args; callees rowed ji_006291a8 memcpy and data 0x007BAC1C empty string.
typedef int Int;

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);
extern const char g_Rva0107301CEmptyString[];

struct Rva002AC2CFSecond
{
	void *m_data;
};

class Rva002AC2CFTarget
{
public:
	void rva002AC2CF(Int a0, Int a1, Int a2);
private:
	char *m_buf;
	int m_len;
	void **m_second;
};

// ?rva002AC2CF@Rva002AC2CFTarget@@QAEXHHH@Z present-unmatched
void Rva002AC2CFTarget::rva002AC2CF(Int a0, Int a1, Int a2)
{
	int len = m_len;
	if (a1 < len)
	{
		int chunk = a2;
		if (a1 + chunk > len)
			chunk = len - a1;
		memcpy((void *)a0, m_buf + a1, chunk);
		a2 -= chunk;
		if (a2 <= 0)
			return;
		a0 += chunk;
		a1 += chunk;
	}
	void *d = *m_second;
	int off2 = a1 - len;
	const char *base = (const char *)d + 8;
	if (!d)
		base = g_Rva0107301CEmptyString;
	memcpy((void *)a0, base + off2, a2);
}
