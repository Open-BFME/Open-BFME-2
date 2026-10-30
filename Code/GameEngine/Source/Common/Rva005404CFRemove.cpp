// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
//
// ?rva005404CF@Rva0054034A@@QAEXH@Z @ 0x005404CF 72B
// The free-camera channel's guarded key removal, the 0x28-stride twin of
// the rowed 0x00541883 (Rva00541883Remove.cpp, same spelling): rejects
// non-positive keys, validates the hint through the pinned locator
// 0x0054034A, notifies the +0x00 listener list through rowed forEach
// 0x005402DC with the member-function pointer (MSVC vcall thunks
// ??_9@$BCA@AE / ??_9@$BBI@AE, slots +0x20 / +0x18), erases the hinted
// element through the rowed BfmePod40 vector erase 0x005401B4 over a
// minimal view, then notifies again. Names are generated.
#include <vector>

struct BfmePod40
{
	int m_00;
	char m_pad04[0x24];
};


namespace _STL
{
	// Bind vector<BfmePod40>::erase to the rowed worker at 0x005401B4.
	// Declaration only: the definition lives in the row owner.
	template <class _Tp, class _Alloc> class vector;
	template <> class vector<BfmePod40, allocator<BfmePod40> >
	{
	public:
		BfmePod40 *erase(BfmePod40 *__pos);
	private:
		BfmePod40 *_M_start;
		BfmePod40 *_M_finish;
		BfmePod40 *_M_end;
	};
}

class Rva005402DCListener
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
	void rva005404CF(int key);
private:
	Rva005402DCList m_list00;
	BfmePod40 *m_begin10;
	BfmePod40 *m_end14;
	int m_pad18;
	int m_hint1C;
};

void Rva0054034A::rva005404CF(int key)
{
	if (key <= 0)
		return;
	if (!rva0054034A(key))
		return;
	m_list00.forEach(&Rva005402DCListener::notify20, this, key);
	((_STL::vector<BfmePod40, _STL::allocator<BfmePod40> > *)&m_begin10)->erase(&m_begin10[m_hint1C]);
	m_list00.forEach(&Rva005402DCListener::notify18, this, key);
}
