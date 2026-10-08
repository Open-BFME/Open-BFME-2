// cl: /Ireference/shims/bfme2_ascii /EHs /MD
// ?rva0010F1D0@Rva0010F185@@QAEXXZ, retail 0x0010F1D0, 127 bytes.
// Virtual slot 1 of vtable 0x007CFAB8 for the Rva0010F185 audio entry:
// lock-guarded AIL stream open with EmptyString fallback. Target for the
// guard is (*(item+0xC)+0x38) where item is base m_str at +8, filename is
// AsciiString data at +0x10 (+8) or g_Rva0107301CEmptyString, args are
// m_0C at +0xC and m_14 at +0x14, handle stored to item+8, unlock if locked.
// Evidence: callees rowed 0x0010F24F 0x0010F26E plus IAT AIL_open_stream
// and AIL_set_stream_user_data; class and flags from Rva0010F185Ctor prev
// 0x0010F185 same cl; vtable VA 0x00BCFAB8 slot 1.
#include "ascii_string.h"

struct Rva00041004;
typedef void *HSTREAM;

extern "C" __declspec(dllimport) HSTREAM __stdcall AIL_open_stream(void *driver, const char *filename, void *extra);
extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_user_data(HSTREAM stream, int index, void *data);

class Rva0036CA00Str
{
public:
	void *m_item;
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str();
};

struct CountBase
{
	volatile int m_count;
	__forceinline CountBase() : m_count(0) {}
	virtual void dummy();
};

class Rva001164D3 : public CountBase
{
public:
	Rva001164D3(const Rva0036CA00Str &s);
	Rva0036CA00Str m_str;
};

class Rva0010F24F
{
public:
	void rva0010F24F();
	Rva00041004 *m_target;
	unsigned char m_locked;
};

class Rva0010F26E
{
public:
	void rva0010F26E();
	Rva00041004 *m_target;
	unsigned char m_locked;
};

class Rva0010F185 : public Rva001164D3
{
public:
	void rva0010F1D0();
	void const *m_0C;
	AsciiString m_s10;
	void const *m_14;
};

void Rva0010F185::rva0010F1D0()
{
	void *p = m_str.m_item;
	if (p)
		p = *(void **)((char *)p + 0x0C);
	if (p)
		p = (char *)p + 0x38;
	else
		p = 0;
	Rva00041004 *target = (Rva00041004 *)p;
	Rva0010F24F guard;
	guard.m_target = target;
	guard.m_locked = 0;
	guard.rva0010F24F();
	char *sdata = *(char **)&m_s10;
	const char *filename = sdata ? sdata + 8 : "";
	HSTREAM stream = AIL_open_stream((void *)m_0C, filename, (void *)m_14);
	if (stream)
	{
		AIL_set_stream_user_data(stream, 0, 0);
		AIL_set_stream_user_data(stream, 1, 0);
	}
	*(HSTREAM *)((char *)m_str.m_item + 8) = stream;
	if (guard.m_locked)
		((Rva0010F26E *)&guard)->rva0010F26E();
}
