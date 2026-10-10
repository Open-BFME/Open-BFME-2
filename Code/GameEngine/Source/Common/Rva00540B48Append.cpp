// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7
//
// ?append@Rva00540B48@@QAEXHABVRva0053FDE6@@@Z @0x0054098B 155B (ret 8):
// insert-or-update on the sorted key map the chunk reader 0x00540B48 fills.
// Negative keys are ignored. The banked 0x0054034A locator (pinned) finds
// the key and leaves its slot in the hint at +0x1C: a hit brackets the
// value assignment with listener slots 2 and 4, a miss brackets inserting a
// fresh entry after the hint (rowed 0x0054001B ctor, rowed vector insert
// 0x00540731) with slots 0 and 3. Each notification goes through the rowed
// forEach 0x005402DC on the listener list at +0x00 with this and the key;
// the four member pointers are the pinned VC7.1 vcall thunks. The vector's
// begin is read before the entry is built (kept across the call in the dead
// key slot), the hint after. The value assignment is the 9-dword
// Rva0053FDE6 operator= retail folds at 0x0053FFCE; this unit emits it
// (noinline, as retail calls it) so a fold-proof pin can name it there.
// Identity is not recovered: names follow the existing pins and the
// neighbouring Rva0054034ALocate.cpp.

class Rva0053FDE6
{
public:
	// ??4Rva0053FDE6@@QAEAAV0@ABV0@@Z, folded by retail onto 0x0053FFCE (61B).
	__declspec(noinline) Rva0053FDE6 &operator=(const Rva0053FDE6 &o)
	{
		m_00 = o.m_00;
		m_04 = o.m_04;
		m_08 = o.m_08;
		m_0c = o.m_0c;
		m_10 = o.m_10;
		m_14 = o.m_14;
		m_18 = o.m_18;
		m_1c = o.m_1c;
		m_20 = o.m_20;
		return *this;
	}
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};

class Rva0054000B
{
public:
	Rva0054000B(int v, const Rva0053FDE6 &o);
	int m_00;
	Rva0053FDE6 m_04;
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
		T *begin() { return m_start; }
		T *insert(T *position, const T &x);
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva005402DCListener
{
public:
	virtual void slot0(void *, int);
	virtual void slot1(void *, int);
	virtual void slot2(void *, int);
	virtual void slot3(void *, int);
	virtual void slot4(void *, int);
};

class Rva005402DCList
{
public:
	void forEach(void (Rva005402DCListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005402DCListener **m_begin;
	Rva005402DCListener **m_end;
	Rva005402DCListener **m_capacity;
	unsigned int m_index;
};

class Rva0054034A
{
public:
	bool rva0054034A(int key);
};

class Rva00540B48
{
public:
	void append(int key, const Rva0053FDE6 &value);
private:
	Rva005402DCList m_listeners;										// +0x00
	_STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > m_entries;	// +0x10
	int m_hint;															// +0x1C
};

void Rva00540B48::append(int key, const Rva0053FDE6 &value)
{
	if (key < 0)
		return;
	if (reinterpret_cast<Rva0054034A *>(this)->rva0054034A(key))
	{
		m_listeners.forEach(&Rva005402DCListener::slot2, this, key);
		m_entries.begin()[m_hint].m_04 = value;
		m_listeners.forEach(&Rva005402DCListener::slot4, this, key);
	}
	else
	{
		m_listeners.forEach(&Rva005402DCListener::slot0, this, key);
		Rva0054000B *begin = m_entries.begin();
		m_entries.insert(begin + (m_hint + 1), Rva0054000B(key, value));
		m_listeners.forEach(&Rva005402DCListener::slot3, this, key);
	}
}
