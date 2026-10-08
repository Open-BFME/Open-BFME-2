// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??0Rva0037381C@@QAE@XZ @0x003733C8 (73B).
// Ctor for MI class Rva0037381C (primary 0xC via baseConstruct, secondary
// Snapshot at +0xC vtable 0x00BBB554, map<int,void*> at +0x10). Calls rowed
// baseConstruct 0x001B4E63 then rowed map 0x0033C432. Vtables 0x00C17E14/
// 0x00C17E04 via gate. Evidence: vtable stores, callees rowed, dtor rowed
// 0x0037381C, caller 0x0022F8CB.
#include <map>

extern const void *const g_00BBB554[];

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class __declspec(novtable) Rva003733C8Primary
{
public:
	__forceinline Rva003733C8Primary() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva003733C8Primary() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

class __declspec(novtable) Rva003733C8Secondary
{
public:
	__forceinline Rva003733C8Secondary() { *(const void **)this = g_00BBB554; }
	virtual ~Rva003733C8Secondary();
};

class Rva0037381C : public Rva003733C8Primary, public Rva003733C8Secondary
{
public:
	Rva0037381C();
	virtual ~Rva0037381C();
private:
	_STL::map<int, void *> m_map;
};

Rva0037381C::Rva0037381C()
{
}
