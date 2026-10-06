// ?rva004EC869@Rva004EC869@@QAEXPAURva005996FFArg@@@Z @ 0x004EC869 139B chain via 0x005996FF.
// Evidence: calls rowed 0x005996FF Rva005996FFListErase plus rowed predicate 0x004E9378 plus rowed list<int> erase 0x00438539 plus rowed vector<ModuleData*> push_back 0x004DFCB0; caller 0x004EC8F4.
// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <list>
#include <vector>

struct Inner64;
struct Rva005996FFArg
{
	char m_pad00[4];
	Inner64 *m_04;
	char m_pad08[0x6C];
	int m_74;
};

class Rva005996FF
{
public:
	void rva005996FF(Rva005996FFArg *arg, bool flag);
};

class Rva00599825
{
public:
	void rva00599825(int id);
};

class Rva004E9378
{
	char m_pad[0x10];
	int m_state;
public:
	bool rva004E9378();
};

class ModuleData
{
public:
  virtual ~ModuleData();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void virt(int x);
public:
  char m_pad04[4];
	int m_08;
	char m_pad0C[4];
	int m_10;
	char m_pad14[0x0C];
	unsigned char m_20;
};

class Rva004EC869
{
public:
	void rva004EC869(Rva005996FFArg *arg);
	void rva004EC2D4(int value);
private:
	char m_pad00[0x130];
	_STL::vector<const ModuleData *> m_vec;
	_STL::list<int> m_list;
};

void Rva004EC869::rva004EC869(Rva005996FFArg *arg)
{
	((Rva005996FF *)((char *)this + 0x140))->rva005996FF(arg, true);
	_STL::list<int>::iterator it = m_list.begin();
	if (it == m_list.end())
		return;
	{
		int value = arg->m_74;
		ModuleData *cur;
		while (it != m_list.end()) {
			cur = (ModuleData *)(*it);
			if (cur->m_08 == value)
				goto found;
			++it;
		}
		return;
found:
		;
		if (((Rva004E9378 *)cur)->rva004E9378())
			return;
		if (cur->m_20) {
			cur->virt(0);
			cur->m_08 = 0;
			m_list.erase(it);
			m_vec.push_back(cur);
		} else {
			cur->virt(3);
		}
	}
}

void Rva004EC869::rva004EC2D4(int value)
{
	((Rva00599825 *)((char *)this + 0x140))->rva00599825(value);
	_STL::list<int>::iterator it = m_list.begin();
	if (it == m_list.end())
		return;
	{
		ModuleData *cur;
		while (it != m_list.end()) {
			cur = (ModuleData *)(*it);
			if (cur->m_08 == value)
				goto found;
			++it;
		}
		return;
found:
		;
		cur->virt(2);
	}
}
