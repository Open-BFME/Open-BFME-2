// cl: /O1 /DNDEBUG /MD
// ?rva0057EF18@AptMpGameRules@@QAEXXZ @0x0057EF18 46B
// Clears the +0x7C widget vector via rowed voidptr erase then rowed Drawable
// resize to 10, clears +0x89, then tail jmps to pinned 0x0057ED2B. Evidence:
// packet disasm with rowed callees 0x0031BD55 and 0x000E6D39; callers
// 0x0057EF95 0x0057F02D and InitGadgets; AptMpGameRules layout in
// AptMpGameRulesCallbacks.cpp; neighbours in Common.
class Drawable;

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *erase(T *first, T *last);
	void resize(unsigned int n, T x);
};
}

class AptMpGameRules
{
public:
	virtual void v00();
	virtual void ruleChanged(int rule, bool silent);
	void rva0057EF18();
	void rva0057ED2B();
private:
	char m_pad04[0x60 - 0x04];
	int m_mode;
	char m_pad64[0x7C - 0x64];
	_STL::vector<Drawable *, _STL::allocator<Drawable *> > m_7C;
	char m_pad88;
	bool m_89;
};

void AptMpGameRules::rva0057EF18()
{
	m_89 = false;
	_STL::vector<void *, _STL::allocator<void *> > *v =
		(_STL::vector<void *, _STL::allocator<void *> > *)&m_7C;
	v->erase(v->begin(), v->end());
	m_7C.resize(10, (Drawable *)0);
	rva0057ED2B();
}
