// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
//
// ?rva00541883@Rva00541579@@QAEXH@Z @ 0x00541883 72B
// Evidence: guarded key removal on the Pod28 channel, sibling of the
// banked Rva0054034A removal (same 0x9CB27E/0x9CB274 notify pair around
// a rowed erase). Rejects non-positive keys, validates the hint through
// the banked locator 0x00541579 (pinned), notifies the +0x00 listener
// list through rowed forEach 0x005414E5 with the raw pmf constant
// (union-punned; callee indirect-calls the slot), erases the hinted
// 0x1C-stride element through rowed vector erase 0x005412E2 over a
// minimal view, then notifies again. Names are generated.
#include <vector>

struct BfmePod28
{
	int m_00;
	char m_pad04[0x18];
};

struct Rva0054107FRecord
{
	char m_bytes[28];
};

namespace _STL
{
	// Bind vector<Rva0054107FRecord>::erase to the rowed worker at
	// 0x005412E2. Declaration only: the definition lives in the row owner.
	template <class _Tp, class _Alloc> class vector;
	template <> class vector<Rva0054107FRecord, allocator<Rva0054107FRecord> >
	{
	public:
		Rva0054107FRecord *erase(Rva0054107FRecord *__pos);
	private:
		Rva0054107FRecord *_M_start;
		Rva0054107FRecord *_M_finish;
		Rva0054107FRecord *_M_end;
	};
}

class Rva005414E5Listener
{
public:
	virtual void notify00(void *, int);
	virtual void notify04(void *, int);
	virtual void notify08(void *, int);
	virtual void notify0C(void *, int);
	virtual void notify10(void *, int);
	virtual void notify14(void *, int);
	virtual void notify18(void *, int);
	virtual void notify1C(void *, int);
	virtual void notify20(void *, int);
};

class Rva005414E5List
{
public:
	void forEach(void (Rva005414E5Listener::*notify)(void *, int), void *arg, int value);
private:
	Rva005414E5Listener **m_begin;
	Rva005414E5Listener **m_end;
	Rva005414E5Listener **m_capacity;
	unsigned int m_index;
};

class Rva00541579
{
public:
	bool rva00541579(int key);
	void rva00541883(int key);
private:
	Rva005414E5List m_list00;
	BfmePod28 *m_begin10;
	BfmePod28 *m_end14;
	int m_pad18;
	int m_hint1C;
};

void Rva00541579::rva00541883(int key)
{
	if (key <= 0)
		return;
	if (!rva00541579(key))
		return;
	m_list00.forEach(&Rva005414E5Listener::notify20, this, key);
	((_STL::vector<Rva0054107FRecord, _STL::allocator<Rva0054107FRecord> > *)&m_begin10)->erase((Rva0054107FRecord *)&m_begin10[m_hint1C]);
	m_list00.forEach(&Rva005414E5Listener::notify18, this, key);
}
