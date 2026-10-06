// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003307F2@Rva003307F2@@QAEXPBVModuleData@@@Z retail 0x003307F2 61 bytes.
// Unlock lane: broadcast arg via Rva0033068BList::forEach at +0 with rowed
// forwarders 0x001FF3A9 then 0x005CB260, push arg into vector at +0x10,
// inc dword at +0x14 via rowed 0x0053F8E5. Evidence: callees rowed
// 0x33068B 0x4DFCB0 0x53F8E5; caller 0x003308D2; prev shares flags.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData
{
public:
	char m_pad[20];
	int m_ref;
};

class Rva0033068BListener
{
public:
	virtual void notify(void *, int);
};

class Rva0033068BList
{
public:
	void forEach(void (Rva0033068BListener::*notify)(void *, int), void *arg, int value);
private:
	Rva0033068BListener **m_begin;
	Rva0033068BListener **m_end;
	Rva0033068BListener **m_capacity;
	unsigned int m_index;
};

struct TreeHintRef00217D4C;

class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva0053F8E5DwordCounter
{
public:
	void inc();
};

class Rva003307F2
{
public:
	void rva003307F2(const ModuleData *mod);
private:
	Rva0033068BList m_list;
	_STL::vector<const ModuleData *> m_vec;
};

void Rva003307F2::rva003307F2(const ModuleData *mod)
{
	m_list.forEach(
		reinterpret_cast<void (Rva0033068BListener::*)(void *, int)>(&Rva001FF3A9::rva001FF3A9),
		this,
		(int)mod);
	m_vec.push_back(mod);
	((Rva0053F8E5DwordCounter *)mod)->inc();
	m_list.forEach(
		reinterpret_cast<void (Rva0033068BListener::*)(void *, int)>(&Rva005CB260::rva005CB260),
		this,
		(int)mod);
}
