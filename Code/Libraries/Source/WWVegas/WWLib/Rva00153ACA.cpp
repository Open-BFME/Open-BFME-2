// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// ?rva00153ACA@Rva0015354E@@QAEXUTreeHintRef00217D4C@@PBD@Z @0x00153ACA 207B
// Evidence: unlock lane, this=Rva0015354E (+0x10 store via rowed rva001535FF 0x001535FF and dec 0x001531E6), virtual slot 0xF8, TreeHintRef assign 0x002174A4 and Release 0x0007DEEF, push_back 0x00153A27 stride 8, caller 0x000E2A81 builds Rva00080221 temp.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
struct Rva00153A27Element
{
	TreeHintRef00217D4C m_ref;
	const char *m_name;
};
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &x);
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
struct Rva00153729
{
	int m00;
	_STL::vector<Rva00153A27Element> m_vec[6];
};
struct ComF8
{
	virtual void *__stdcall s00(); virtual void *__stdcall s04(); virtual void *__stdcall s08(); virtual void *__stdcall s0C();
	virtual void *__stdcall s10(); virtual void *__stdcall s14(); virtual void *__stdcall s18(); virtual void *__stdcall s1C();
	virtual void *__stdcall s20(); virtual void *__stdcall s24(); virtual void *__stdcall s28(); virtual void *__stdcall s2C();
	virtual void *__stdcall s30(); virtual void *__stdcall s34(); virtual void *__stdcall s38(); virtual void *__stdcall s3C();
	virtual void *__stdcall s40(); virtual void *__stdcall s44(); virtual void *__stdcall s48(); virtual void *__stdcall s4C();
	virtual void *__stdcall s50(); virtual void *__stdcall s54(); virtual void *__stdcall s58(); virtual void *__stdcall s5C();
	virtual void *__stdcall s60(); virtual void *__stdcall s64(); virtual void *__stdcall s68(); virtual void *__stdcall s6C();
	virtual void *__stdcall s70(); virtual void *__stdcall s74(); virtual void *__stdcall s78(); virtual void *__stdcall s7C();
	virtual void *__stdcall s80(); virtual void *__stdcall s84(); virtual void *__stdcall s88(); virtual void *__stdcall s8C();
	virtual void *__stdcall s90(); virtual void *__stdcall s94(); virtual void *__stdcall s98(); virtual void *__stdcall s9C();
	virtual void *__stdcall sA0(); virtual void *__stdcall sA4(); virtual void *__stdcall sA8(); virtual void *__stdcall sAC();
	virtual void *__stdcall sB0(); virtual void *__stdcall sB4(); virtual void *__stdcall sB8(); virtual void *__stdcall sBC();
	virtual void *__stdcall sC0(); virtual void *__stdcall sC4(); virtual void *__stdcall sC8(); virtual void *__stdcall sCC();
	virtual void *__stdcall sD0(); virtual void *__stdcall sD4(); virtual void *__stdcall sD8(); virtual void *__stdcall sDC();
	virtual void *__stdcall sE0(); virtual void *__stdcall sE4(); virtual void *__stdcall sE8(); virtual void *__stdcall sEC();
	virtual void *__stdcall sF0(); virtual void *__stdcall sF4();
	virtual int __stdcall slotF8(const char *a, int b);
};
struct Rva0015354EStore
{
	const char *m_name00;
	int *m_start04;
	int *m_finish08;
	int *m_end0C;
};
class Rva001531E6
{
public:
	void rva001531E6();
};
class Rva0015354E
{
public:
	void rva001535FF(const char *name);
	void rva00153ACA(TreeHintRef00217D4C arg, const char *name);
private:
	ComF8 *m_com00;
	Rva00153729 *m_start04;
	Rva00153729 *m_finish08;
	Rva00153729 *m_end0C;
	Rva0015354EStore *m_store10;
};
void Rva0015354E::rva00153ACA(TreeHintRef00217D4C arg, const char *name)
{
	if (m_store10 == 0)
		return;
	rva001535FF(name);
	int idx = *(m_store10->m_finish08 - 1);
	Rva00153A27Element elem;
	elem.m_ref = arg;
	elem.m_name = name;
	for (Rva00153729 *it = m_start04; it != m_finish08; ++it)
	{
		const char *cur = m_store10->m_name00;
		if (cur == 0)
			cur = name;
		if (cur == 0)
			continue;
		if (m_com00->slotF8(cur, it->m00))
			it->m_vec[idx].push_back(elem);
	}
	((Rva001531E6 *)this)->rva001531E6();
}
