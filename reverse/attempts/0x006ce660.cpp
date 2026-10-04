// ?rva006CE660@Rva006CE660Vec@@QAEXH@Z
// partial score=0.68 date=2026-10-04
// cl: /O1 /MD
// ?rva006CE660@@YAXH@Z @ 0x006CE660 (251B).
//
// Address-derived Apt value-vector growth, next to the rowed
// ?Rva006CE630@@QAEPAXI@Z (0x006CE630) and using the same 8-byte element
// layout the matched Rva006CD5A0Copy (0x006CD5A0) pins: EAStringC at +0 and
// int at +4, so an element is `lea [eax + ecx*8]` indexed by element count.
//
// Class layout, all reads proven by the body:
//   +0x00 m_count   (int)   -- element index high; used as the *8 stride
//   +0x04 m_size    (int)   -- current capacity, compared against the request
//   +0x08 m_first   (elem*) -- first element pointer, stored to the old buffer
//   +0x0C m_last    (elem*) -- one-past-end, i.e. the begin()+size pointer
//
// Retail:
//   if (want <= m_size) return;                       // no growth needed
//   if (want <= 1)   { m_size = want; return; }       // clamp-only tail
//   n = want + 1;                                        // growth is want+1
//   newFirst = Rva00893B30ResizeItems(0, 0, n)          // rowed, 3 cdecl args
//   // two temporaries, both EAStringC, built in-place 12 bytes each and
//   // passed by hidden return pointer to the unknown 0x006CDE00
//   first = m_first; oldLast = m_last;
//   Rva006CDE00(&tmpA, &tmpB, newFirst + n, oldLast, newFirst);
//   m_size = want;
//   if (oldLast != &m_last) Rva00893B30ResizeItems(oldLast, 0, 0);
//   m_first = newFirst;
//   newLast = newFirst + m_count;
//   tmpA.rva006D3030(tmpB);                             // rowed operator=
//   newLast->m_name = tmpA.m_pData;                     // +4 of the tail elem
//   tmpA.~EAStringC();                                  // rowed 0x006D3010
//
// The SEH tricycle here is the same 3-push form as 0x006CCA50
// (push -1 / push scope 0x00BA8248 / push fs:[0]) and this body DOES balance
// it, so it is a balanced frame rather than 0x006CCA50's handler-restored one.
//
// 0x006CDE00 is UNROWED: called with a hidden return pointer and two 12-byte
// temporaries, so it is an out-parameter pair constructor. It is declared
// address-derived here; identity is not proven. The two temporaries are
// initialised by three dword stores each from (newFirst+n, oldLast, newFirst),
// which is an EAStringC-shaped pair rather than plain text.
//
// Identity is address-derived throughout; the element layout and the
// rowed callees come from the matched neighbours cited above.

class EAStringC
{
public:
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();
	void *m_pData;
};

struct Rva006CD5A0Elem
{
	EAStringC m_name;
	int m_value;
};

struct Rva00892640Item
{
	int m_pad;
};

// Rowed allocator: 0x006CDBF0 is ?Rva00893B30ResizeItems@@YAPAURva00892640Item@@PAU1@HH@Z
void *__cdecl Rva00893B30ResizeItems(Rva00892640Item *first,
	Rva00892640Item *last, int newSize);

// Address-derived out-parameter pair constructor (unknown callee). Retail
// passes the hidden return pointer first, then two 12-byte temporaries.
void __cdecl rva006CDE00(EAStringC *outA, EAStringC *outB,
	Rva006CD5A0Elem *end, Rva006CD5A0Elem *oldLast, void *newFirst);

class Rva006CE660Vec
{
public:
	void rva006CE660(int want);
	int m_count;                                        // +0x00 stride *8
	int m_size;                                         // +0x04 capacity
	Rva006CD5A0Elem *m_first;                           // +0x08
	Rva006CD5A0Elem *m_last;                            // +0x0C
};

void Rva006CE660Vec::rva006CE660(int want)
{
	if (want <= m_size)
		return;
	if (want <= 1) {
		m_size = want;
		return;
	}

	int n = want + 1;
	Rva006CD5A0Elem *newFirst = (Rva006CD5A0Elem *)
		Rva00893B30ResizeItems(0, 0, n);
	Rva006CD5A0Elem *oldLast = m_last;
	EAStringC tmpA;
	EAStringC tmpB;
	rva006CDE00(&tmpA, &tmpB, newFirst + n, oldLast, newFirst);
	m_size = want;
	if (oldLast != m_last)
		Rva00893B30ResizeItems((Rva00892640Item *)oldLast, 0, 0);
	m_first = newFirst;
	Rva006CD5A0Elem *newLast = newFirst + m_count;
	tmpA = tmpB;
	newLast->m_name.m_pData = tmpA.m_pData;
}