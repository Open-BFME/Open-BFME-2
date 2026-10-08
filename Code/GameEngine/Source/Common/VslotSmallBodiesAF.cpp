// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AF. As in VslotSmallBodiesA-AE, classes and methods are address-derived
// unless the ledger already names them, and model only what each body
// touches. Meanings are not recovered.

typedef int Int;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	T *erase(T *first, T *last);
	T *begin() { return _M_start; }
	T *end() { return _M_finish; }
	void clear() { erase(begin(), end()); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

// 0x005174E4: clears +0x27C, releases the +0x290 interface (virtual slot 2)
// and forgets it, global-deletes every entry of the +0x280 pointer vector
// and clears it (pinned vector<void*>::erase), then sets +0x2B8.
class Rva005174E4Entry
{
public:
	virtual ~Rva005174E4Entry();
};
class Rva005174E4Iface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
};
class Rva005174E4
{
public:
	void rva005174E4();
private:
	char m_pad00[0x27C];
	bool m_27C;
	char m_pad27D[0x03];
	_STL::vector<void *, _STL::allocator<void *> > m_280;
	char m_pad28C[0x04];
	Rva005174E4Iface *m_290;
	char m_pad294[0x24];
	bool m_2B8;
};
void Rva005174E4::rva005174E4()
{
	m_27C = false;
	if (m_290)
	{
		m_290->v02();
		m_290 = 0;
	}
	for (void **it = m_280.begin(); it != m_280.end(); ++it)
		::delete (Rva005174E4Entry *)*it;
	m_280.clear();
	m_2B8 = true;
}

// 0x00518557 (table VA 0x00C6669C): message 0x15 with byte argument 1
// answers 1; with bit 0 of the third argument, state 1 at +0x27C runs the
// rowed 0x0051847B(0) and state 2 first asks the Apt target at VA
// 0x00DFE4CC to invoke "CloseAdvancedSettings" on the +0x274 movie.
class Rva00222A8BTarget
{
public:
	Int invoke(void *movie, const char *name, Int a, const char *b, void *c, void *d, void *e, void *f);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0051847B
{
public:
	void rva0051847B(Int a);
	Int rva00518557(Int msg, unsigned char b, Int c);
private:
	char m_pad00[0x274];
	void *m_274;
	char m_pad278[0x04];
	Int m_27C;
};
Int Rva0051847B::rva00518557(Int msg, unsigned char b, Int c)
{
	if (msg != 0x15)
		return 0;
	switch (b)
	{
	case 1:
		break;
	default:
		return 0;
	}
	if (c & 1)
	{
		switch (m_27C)
		{
		case 1:
			rva0051847B(0);
			break;
		case 2:
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_274, "CloseAdvancedSettings", 0, 0, 0, 0, 0, 0);
			rva0051847B(0);
			break;
		}
	}
	return 1;
}

// 0x00589722 (interface at +0x20): on the owning object and then on the
// argument, swaps model condition 82 for 83 (the word array at Object
// +0x10C, as in ObjectWeaponSetFlags.cpp), notifying through the pinned
// Object 0x0028AE6D whenever 82 is set or 83 is not.
typedef unsigned int UnsignedInt;
class Rva0010CConditionBits
{
public:
	UnsignedInt test(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(UnsignedInt bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[20];
};
class Object
{
public:
	void rva0028AE6D();
	__forceinline void clearAndSetCondition(UnsignedInt clr, UnsignedInt set)
	{
		if (m_conditionBits.test(clr) || !m_conditionBits.test(set))
		{
			m_conditionBits.clear(clr);
			m_conditionBits.set(set);
			rva0028AE6D();
		}
	}
private:
	char m_pad00[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
class Rva00589722Primary
{
public:
	virtual void primarySlot();
protected:
	Int m_04;
	Object *m_object; // +0x08
	char m_pad0C[0x14];
};
class Rva00589722Iface
{
public:
	virtual void rva00589722(Object *other) = 0;
};
class Rva00589722 : public Rva00589722Primary, public Rva00589722Iface
{
public:
	void rva00589722(Object *other);
};
void Rva00589722::rva00589722(Object *other)
{
	m_object->clearAndSetCondition(82, 83);
	other->clearAndSetCondition(82, 83);
}
