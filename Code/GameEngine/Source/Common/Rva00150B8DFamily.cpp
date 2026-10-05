// cl: /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: contiguous 0x150B8D-0x150F19 container family plus the
// 0x150A8B growers they forward to. One subsystem: vector-like holders with a
// vtable at +0 and a {first,last} member pair at +4, grown through small
// per-variant wrapper/grower pairs.
//
// Family evidence so far:
// - 0x150C97/0x150CD0/0x150D09 (57B): resize over 8-byte elements
//   (`[first+i*8+4] = i`), early-out `if (n < size)`, recompute size, forward
//   to the matching 41B grow wrapper (0x150BF9/0x150C22/0x150C4B).
// - 0x150D42 (72B): resize over 0x4C-byte elements (`[first+i*0x4C+4] = i`)
//   with an explicit `if (old >= n) return` after the grow call, forwarding to
//   the 0x150C74 adapter.
// - 0x150C74 (35B): builds an 84-byte stack temp, inits it through 0x14DB9F,
//   then forwards (this, n) to the 108B 0x150B8D grower, which reads the temp
//   in place as its by-value fill element (its `ret 0x50` cleans the 80 bytes
//   the caller never pushed; the caller's `leave` rescues esp).
// - The 41B wrappers and 86B growers (0x150A8B/0x150AE1/0x150B37) plus the 87B
//   subclass ctors (0x150D8A/0x150DFD/0x150F19) and 0x150B8D need the
//   `mov eax,scope; call __EH_prolog` recipe and land after these.
// - 0x211E58 (Vector_base ctor pin, ICF-folded) and the rowed 0x15068C /
//   0x150659 (vector erase) / 0x150959 (fill-insert) / 0x14D1E3 (dtor) siblings
//   live in neighbouring TUs (Rva0015068CFinish.cpp, Rva00150959Insert.cpp,
//   StlportVectorEraseRangeFamily.cpp).

struct Rva00150C97Elem
{
	int m_00;
	int m_index;
};
struct Rva00150D42Elem
{
	char m_pad[4];
	int m_index;
};

// 41B grow wrappers (0x150BF9/0x150C22/0x150C4B): pinned until their bodies
// land below. thiscall (int), ret 4.
class Rva00150BF9
{
public:
	void rva00150BF9(int n);
	int size() const { return (m_last - m_first) >> 3; }
	int m_first;
	int m_last;
};
class Rva00150C22
{
public:
	void rva00150C22(int n);
	int size() const { return (m_last - m_first) >> 3; }
	int m_first;
	int m_last;
};
class Rva00150C4B
{
public:
	void rva00150C4B(int n);
	int size() const { return (m_last - m_first) >> 3; }
	int m_first;
	int m_last;
};

// 0x150C97 family owner: +0 untouched here (subclass ctors install 0xBD3Axx
// vtables), +4 is the {first,last} pair the resize walks.
class Rva00150C97
{
public:
	void rva00150C97(int n);
private:
	int m_00;
	Rva00150BF9 m_vec;
};
class Rva00150CD0
{
public:
	void rva00150CD0(int n);
private:
	int m_00;
	Rva00150C22 m_vec;
};
class Rva00150D09
{
public:
	void rva00150D09(int n);
private:
	int m_00;
	Rva00150C4B m_vec;
};

// ?rva00150C97@Rva00150C97@@QAEXH@Z
// ?rva00150C97@Rva00150C97@@QAEXH@Z
void Rva00150C97::rva00150C97(int n)
{
	if ((unsigned int)n < (unsigned int)m_vec.size())
		return;
	int *pair = (int *)&m_vec;
	int oldCount = (pair[1] - pair[0]) >> 3;
	m_vec.rva00150BF9(n);
	for (; oldCount < n; ++oldCount)
		((Rva00150C97Elem *)m_vec.m_first)[oldCount].m_index = oldCount;
}

// ?rva00150CD0@Rva00150CD0@@QAEXH@Z
// ?rva00150C97@Rva00150C97@@QAEXH@Z
void Rva00150CD0::rva00150CD0(int n)
{
	if ((unsigned int)n < (unsigned int)m_vec.size())
		return;
	int *pair = (int *)&m_vec;
	int oldCount = (pair[1] - pair[0]) >> 3;
	m_vec.rva00150C22(n);
	for (; oldCount < n; ++oldCount)
		((Rva00150C97Elem *)m_vec.m_first)[oldCount].m_index = oldCount;
}

// ?rva00150D09@Rva00150D09@@QAEXH@Z
// ?rva00150C97@Rva00150C97@@QAEXH@Z
void Rva00150D09::rva00150D09(int n)
{
	if ((unsigned int)n < (unsigned int)m_vec.size())
		return;
	int *pair = (int *)&m_vec;
	int oldCount = (pair[1] - pair[0]) >> 3;
	m_vec.rva00150C4B(n);
	for (; oldCount < n; ++oldCount)
		((Rva00150C97Elem *)m_vec.m_first)[oldCount].m_index = oldCount;
}

// 0x150C74 adapter and 0x150B8D grower share one {first,last} object: the
// adapter builds a 76-byte scratch element through 0x14DB9F, then forwards
// (this, n) to the grower, which reads the scratch in place as its by-value
// fill element (hence its ret 0x50 against 4 pushed bytes; this frame's leave
// rescues esp). The grower is declared (int) here to reproduce the retail
// call shape; its true (int, element) signature lands with its body.
class Rva0014DB9F
{
	char m_bytes[76];
public:
	Rva0014DB9F();
	// Declared, never defined in this TU (same device the matched
	// Rva00427130Vector::resize uses: its BfmeItemERF declares copy and
	// dtor without defining them here): the invisible copy forces MSVC to
	// construct the by-value temporary directly in the outgoing arg slot
	// instead of building it aside and rep-movs copying it.
	Rva0014DB9F(const Rva0014DB9F &other);
	~Rva0014DB9F();
};
class Rva00150B8D
{
public:
	void rva00150B8D(int n, Rva0014DB9F fill);
	void rva00150C74(int n);
	int size() const { return (m_last - m_first) / 76; }
	int m_first;
	int m_last;
};

// 0x150D42 owner: +0 untouched here, +4 is the grower object above.
class Rva00150D42
{
public:
	void rva00150D42(int n);
private:
	int m_00;
	Rva00150B8D m_grow;
};

// ?rva00150C74@Rva00150B8D@@QAEXH@Z
void Rva00150B8D::rva00150C74(int n)
{
	rva00150B8D(n, Rva0014DB9F());
}

// ?rva00150D42@Rva00150D42@@QAEXH@Z
void Rva00150D42::rva00150D42(int n)
{
	if ((unsigned int)n < (unsigned int)m_grow.size())
		return;
	int *pair = (int *)&m_grow;
	int oldCount = (pair[1] - pair[0]) / 76;
	m_grow.rva00150C74(n);
	if (oldCount >= n)
		return;
	int off = oldCount * 76;
	do {
		((Rva00150D42Elem *)((char *)m_grow.m_first + off))->m_index = oldCount;
		++oldCount;
		off += 76;
	} while (oldCount < n);
}
