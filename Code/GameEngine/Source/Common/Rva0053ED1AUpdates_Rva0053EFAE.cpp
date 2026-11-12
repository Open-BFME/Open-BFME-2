// cl: /O1 /DNDEBUG /MD /EHsc
// Split from Rva0053ED1AUpdates.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

#include "../../Include/Common/GameEngineDeletingBase.h"

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

#include "../../Include/GameClient/Bfme2GameWindow.h"

enum ScienceType
{
	SCIENCE_NONE = 0
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
	T *erase(T *first, T *last);
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
// Keep these accesses inline without competing with the STLport providers.
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::begin() { return m_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *, allocator<void *> >::end() { return m_finish; }
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
  virtual void rva0053EF92();
  virtual void update();
	void rva0053EFC7(WindowList &list);
	void rva0053EF2E();
private:
	WindowList m_vec48;
	int m_at54;
	int m_at58;
};




void Rva0053ED1A::update()
{
	if (m_at58 != m_at54)
		rva0053EF7B();
	static_cast<Rva005C6D4D *>(this)->rva005C6D9C();
}

