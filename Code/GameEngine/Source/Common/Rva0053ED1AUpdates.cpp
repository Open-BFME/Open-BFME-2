// cl: /O1 /DNDEBUG /MD /EHsc
//
// Rva0053ED1A follow-on methods around 0x0053EF7B/0x0053EFAE/0x0053EFC7.
// Evidence: same class view as Rva0053ED1ACtor.cpp (primary
// GameEngineDeletingBase at +0, secondary Rva005C6D4D at +0xC covering
// +0xC..+0x47, vector at +0x48 with end pointer at +0x4C, ints at +0x54
// and +0x58). 0x0053EFAE reads +0x58/+0x54, conditionally calls 0x0053EF7B
// with ecx intact, then tail-jumps to the secondary-base method at
// 0x005C6D9C with ecx=this+0xC. 0x0053EF7B stores +0x58 to +0x54, then
// dispatches on it: zero tail-calls 0x0053EF2E, nonzero takes virtual slot
// 5 (0x14) on the secondary base. 0x0053EFC7 filters a GameWindow list
// in place (erase + park offscreen for hidden or status-unqualified
// windows), then on change flushes via 53EF2E, swaps the new list in,
// syncs +0x54=+0x58 and notifies the secondary base with the 4-byte-
// element count. Callees are the rowed GameWindow methods and the
// ICF-folded rowed STLport spellings (voidptr erase 0x001FF51F,
// vector<BfmeE12> swap 0x00567ECD, ScienceType vector != 0x0053ED05),
// reached by casting the 12-byte WindowList storage. Names generated
// except rowed callees; the secondary base's real type is not established.

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva005C6D4D
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void rva005C6D9C();
	void secondarySetCount(int count);
	void rva0053EF2EHelper();
private:
	char m_pad04[0x38];
};

class Rva005C6C7B
{
public:
	void reset();
};

class GameWindow
{
public:
	bool winIsHidden();
	unsigned winGetStatus();
	int winSetSize(int w, int h);
	int winSetPosition(int x, int y);
};

enum ScienceType
{
	SCIENCE_NONE = 0
};

struct BfmeE12
{
	char e[12];
};

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
	typedef T *pointer;
	typedef const T *const_pointer;
	T *erase(T *it);
	void swap(vector &other);
	pointer begin() { return m_start; }
	const_pointer begin() const { return m_start; }
	pointer end() { return m_finish; }
	const_pointer end() const { return m_finish; }
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
template <class T, class A>
bool operator!=(const vector<T, A> &a, const vector<T, A> &b);
}

class WindowList
{
public:
	GameWindow **m_begin;
	GameWindow **m_end;
	GameWindow **m_cap;
};

class Rva0053ED1A : public GameEngineDeletingBase, public Rva005C6D4D
{
public:
  void rva0053EF7B();
  void rva0053EF92();
  void rva0053EFAE();
	void rva0053EFC7(WindowList &list);
	void rva0053EF2E();
private:
	WindowList m_vec48;
	int m_at54;
	int m_at58;
};

void Rva0053ED1A::rva0053EF7B()
{
	m_at54 = m_at58;
	if (m_at58 != 0)
		static_cast<Rva005C6D4D *>(this)->v5();
	else
		rva0053EF2E();
}

void Rva0053ED1A::rva0053EF92()
{
	((Rva005C6C7B *)((char *)this + 12))->reset();
	rva0053EF2E();
	m_at54 = 0;
	m_at58 = 0;
}

void Rva0053ED1A::rva0053EFAE()
{
	if (m_at58 != m_at54)
		rva0053EF7B();
	static_cast<Rva005C6D4D *>(this)->rva005C6D9C();
}

void Rva0053ED1A::rva0053EFC7(WindowList &list)
{
	typedef _STL::vector<void *, _STL::allocator<void *> > VoidVec;
	typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;
	typedef _STL::vector<BfmeE12, _STL::allocator<BfmeE12> > E12Vec;
	GameWindow **it = list.m_begin;
	while (it != list.m_end) {
		GameWindow *win = *it;
		if (win == 0) {
			it = (GameWindow **)((VoidVec *)&list)->erase((void **)it);
			continue;
		}
		if (!win->winIsHidden()) {
			if (win->winGetStatus() & 0x4000000) {
				++it;
				continue;
			}
		}
		it = (GameWindow **)((VoidVec *)&list)->erase((void **)it);
		win->winSetSize(1, 1);
		win->winSetPosition(-100, -100);
	}
	WindowList *mine = &m_vec48;
	if (*(const SciVec *)mine != *(const SciVec *)&list) {
		rva0053EF2E();
		((E12Vec *)mine)->swap(*(E12Vec *)&list);
		m_at54 = m_at58;
		int count = (int)(((const SciVec *)mine)->end() - ((const SciVec *)mine)->begin());
		static_cast<Rva005C6D4D *>(this)->secondarySetCount(count);
	}
}
