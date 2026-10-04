// cl: /O1 /MD
// ?set@Rva0040F9D@@QAE_NXZ at 0x00040F9D (24B).
// Honest address-derived class: vptr at +0 and event handle at +4 match the
// base-dtor layout at 0x00040EDB (CloseHandle on +4). IAT SetEvent slot
// 0x00BBA2CC with neg/sbb/neg bool normalization. 8 callers incl 0x0010EC93.
// ??0Rva0040F9D@@QAE@HHPBDPAX@Z at 0x00040F64 (57B). Event ctor vtable 0x007C16D0
// CreateEventA IAT 0x00BBA2C8. Same this at 0x0010F058 for ctor and set proves
// same class. Callers pass 1 0 0 0 giving CreateEvent NULL TRUE FALSE NULL.
// Non-virtual base holds handle at +4 so its inline zero runs before vptr.
// ?reset@Rva0040F9D@@QAE_NXZ at 0x00040FCD (24B). Same handle layout as set.
// IAT ResetEvent slot 0x00BBA2D4 with neg/sbb/neg bool normalization.
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *eventHandle);
extern "C" __declspec(dllimport) int __stdcall ResetEvent(void *eventHandle);
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *attrs, int manualReset, int initialState, char const *name);

struct Rva0040F9DBase
{
	Rva0040F9DBase() : m_handle(0) {}
	void *m_handle;
};

class Rva0040F9D : public Rva0040F9DBase
{
public:
    virtual ~Rva0040F9D() = 0;
	bool set();
	bool reset();
	Rva0040F9D(int a1, int a2, char const *a3, void *a4);
};

bool Rva0040F9D::set()
{
	if (m_handle != 0)
		return SetEvent(m_handle) != 0;
	return false;
}

bool Rva0040F9D::reset()
{
	if (m_handle != 0)
		return ResetEvent(m_handle) != 0;
	return false;
}

Rva0040F9D::Rva0040F9D(int a1, int a2, char const *a3, void *a4)
{
	m_handle = CreateEventA(a4, (a2 == 0), (a1 == 0), a3);
}
