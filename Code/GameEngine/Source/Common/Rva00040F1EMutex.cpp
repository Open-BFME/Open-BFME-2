// cl: /MD
// ??0Rva00040F1E@@QAE@HPBDPAX@Z at 0x00040F1E (46B). Mutex ctor vtable 0x007C16C4
// CreateMutexA IAT 0x00BBA210. Caller at 0x0005D189 passes 1 0 0 giving
// CreateMutex NULL FALSE NULL. Non-virtual base holds handle at +4 so its
// inline zero runs before vptr matching retail order.
extern "C" __declspec(dllimport) void *__stdcall CreateMutexA(void *attrs, int owned, char const *name);

struct Rva00040F1EBase
{
	Rva00040F1EBase() : m_handle(0) {}
	void *m_handle;
};

class Rva00040F1E : public Rva00040F1EBase
{
public:
	virtual ~Rva00040F1E();
	Rva00040F1E(int a1, char const *a2, void *a3);
};

Rva00040F1E::Rva00040F1E(int a1, char const *a2, void *a3)
{
	m_handle = CreateMutexA(a3, (a1 == 0), a2);
}
