// cl: /DNDEBUG /MD
// ?rva002B8860@Rva002B8860@@QAEXXZ @0x002B8860 140B. guard +0x168, globals, vector erase, clear, singleton fwd, forEach, tail endgame.
// Evidence: caller 0x002B9DC7, callees rowed/pinned, vtable slot 0x28, push 0x9CB260.
extern int g_Va00E032E0;
void Rva00433D27Enable();
void Rva00437E9C(int);

class Rva00222A8BTarget
{
public:
	virtual void v0() = 0;
	virtual void v1() = 0;
	virtual void v2() = 0;
	virtual void v3() = 0;
	virtual void v4() = 0;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void v8() = 0;
	virtual void v9() = 0;
	virtual void v10() = 0;
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameLogic
{
public:
	void rva00376D49();
};
extern GameLogic *TheGameLogic;

struct TreeHintRef00217D4C
{
	int m_a;
};
namespace _STL
{
template <class _Tp> class allocator
{
};
template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end;
	_Tp *erase(_Tp *first, _Tp *last);
};
}

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void clear();
};

class Rva002B6151Listener
{
public:
	virtual void notify(void *);
};
class Rva002B6151List
{
public:
	void forEach(void (Rva002B6151Listener::*notify)(void *), void *arg);
private:
	Rva002B6151Listener **m_begin;
	Rva002B6151Listener **m_end;
	Rva002B6151Listener **m_capacity;
	unsigned int m_index;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva002B5D36
{
public:
	void rva002B5D36();
};

class Rva002B8860
{
public:
	void rva002B8860();
private:
	char m_pad0[0x4C];
	Rva002B6151List m_4c;
	char m_pad5C[0x100 - 0x5C];
	void *m_100;
	char m_pad104[0x154 - 0x104];
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > m_154;
	Rva002BED91 m_160;
	void *m_164;
	unsigned char m_168;
	char m_pad169[0x175 - 0x169];
	unsigned char m_175;
};

void Rva002B8860::rva002B8860()
{
	if (m_168)
		return;
	if (g_Va00E032E0)
	{
		Rva00433D27Enable();
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->v10();
	}
	if (TheGameLogic)
		TheGameLogic->rva00376D49();
	m_168 = 1;
	m_164 = (char *)m_100 + 0x3C;
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > *p154 = &m_154;
	p154->erase(p154->_M_start, p154->_M_finish);
	m_160.clear();
	m_175 = 1;
	Rva00437E9C(1);
	m_4c.forEach(reinterpret_cast<void (Rva002B6151Listener::*)(void *)>(&Rva005CB260::rva005CB260), this);
	((Rva002B5D36 *)this)->rva002B5D36();
}
