// One array-owning destructor, verified by masked whole-.text search of the
// compiled body against a single retail address.
//
// Frees an owned array with delete[] only when the pointer at +0x04 is
// non-null AND the ownership byte at +0x0D is set, then clears the ownership
// byte, the count at +0x08, and a trailing field at +0x10. The delete[]
// expands inline -- element count read from base-4, eh vector destructor
// iterator, then the array free -- so this is ordinary source, not a
// compiler-generated vector deleting destructor.
//
// Eight sibling candidates hypothesized from the same masked shape did not
// hold up under placement: two collide (identical bytes, two retail
// addresses, cannot assign either name), two have no retail match at all,
// and four masked-match addresses ALREADY claimed by unrelated,
// differently-named template container methods (VectorClass<...>::~,
// DynamicVectorClassWide<...>::Clear) -- the generic array-free shape
// coincides with their bytes once masked, so none of the eight can be
// claimed without inventing an identity the bytes do not support. Only this
// one produced a single, unclaimed, unambiguous hit.

typedef bool Bool;

// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[](void *block);

class BfmeElementA
{
public:
	~BfmeElementA(void);					// retail 0x00030652

private:
	char m_bfmeBytes[4];
};

class Gen_00930C10
{
public:
	~Gen_00930C10(void);

private:
	char m_bfmeHead[4];
	BfmeElementA *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
	int m_bfmeExtra;					// +0x10
};

// ??1Gen_00930C10@@QAE@XZ
Gen_00930C10::~Gen_00930C10(void)
{
	m_bfmeExtra = 0;

	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}
