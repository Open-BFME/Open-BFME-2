// ?rva003B07B8@Rva003B0401@@QAEXXZ
// partial score=0.96 date=2026-10-06
// cl: /O1 /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003B07B8@Rva003B0401@@QAEXXZ @0x003B07B8 125B
// Virtual slot 10 (offset 0x28) of vtable 0x0081DA10, class Rva003B0401 (dtor 0x003B0401).
// Evidence: slot via vftable map; callees rowed pop 0x003B02F4 and push 0x003B0433 and delete 0x0002FD60; no caller.
// Layout from ctor 0x003B0454: +0x24 vector BfmeE12 reserve and +0x34 vector ModuleData reserve; here +0x24 is priority_queue<Rva003B02F4Entry> and +0x34 is Rva003B0433 holder.
#include <queue>
#include <vector>
#include <functional>

class WW3D
{
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
private:
	static unsigned int SyncTime;
};

extern int g_00DBA4E8;
extern float g_00BC26EC;
extern float g_00BC28F8;

class ModuleData;

struct Rva003B02F4Entry
{
	float key;
	const ModuleData *a;
	void *b;
};

struct Rva003B02F4Greater
{
	bool operator()(const Rva003B02F4Entry &x, const Rva003B02F4Entry &y) const
	{
		return x.key > y.key;
	}
};

class ModuleData;

class Rva003B0433
{
public:
	void rva003B0433(const ModuleData *&m);
private:
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec;
	_STL::greater<int> m_comp;
};

class Rva003B07B8Item
{
public:
	virtual void *rva003B07B8Get(int v);
};

class Rva003B0401
{
public:
	void rva003B07B8();
private:
	char m_pad00[0x24];
	_STL::priority_queue<Rva003B02F4Entry, _STL::vector<Rva003B02F4Entry>, Rva003B02F4Greater> m_queue24;
	Rva003B0433 m_holder34;
};

void Rva003B0401::rva003B07B8()
{
	unsigned int prod = WW3D::Get_Sync_Time() * (unsigned int)g_00DBA4E8;
	float t = (float)prod * g_00BC28F8;
	while (!m_queue24.empty())
	{
		const Rva003B02F4Entry &top = m_queue24.top();
		if (!(t > top.key))
			break;
		const ModuleData *mod = top.a;
		void *obj = top.b;
		void *toDelete;
		if (obj)
			toDelete = ((Rva003B07B8Item *)obj)->rva003B07B8Get(0);
		else
			toDelete = 0;
		::operator delete(toDelete);
		m_queue24.pop();
		m_holder34.rva003B0433(mod);
	}
}
