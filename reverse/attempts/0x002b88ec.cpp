// ?rva002B88EC@Rva002B8860@@QAEXXZ
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva002B88EC@Rva002B8860@@QAEXXZ @0x002B88EC 97B. Adjacent proven Rva002B8860 methods share the +0x154 vector, +0x160 clear target, listener list and flags; packet call targets and caller evidence support this method identity.
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
class GameLogic
{
public:
	void rva0023D0E3(bool);
};
extern GameLogic *TheGameLogic;
void Rva00437E9C(int);
void Rva002B29BDFire();
class Rva005CB260
{
public:
	void rva005CB260();
};
class Rva002B8860
{
public:
	void rva002B88EC();
private:
	char m_pad0[0x4C];
	Rva002B6151List m_4c;
	char m_pad5C[0x154 - 0x5C];
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > m_154;
	Rva002BED91 m_160;
	void *m_164;
	unsigned char m_168;
	char m_pad169[0x175 - 0x169];
	unsigned char m_175;
};
void Rva002B8860::rva002B88EC()
{
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > *p154 = &m_154;
	p154->erase(p154->_M_start, p154->_M_finish);
	m_160.clear();
	m_175 = 1;
	Rva00437E9C(1);
	m_164 = (void *)-1;
	Rva002B29BDFire();
	if (!m_168)
		m_4c.forEach(reinterpret_cast<void (Rva002B6151Listener::*)(void *)>(&Rva005CB260::rva005CB260), this);
	TheGameLogic->rva0023D0E3(false);
}
