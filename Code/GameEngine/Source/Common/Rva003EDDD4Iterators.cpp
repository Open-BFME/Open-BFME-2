// cl: /DNDEBUG /MD
//
// Adjacent same-shape thiscall iterators from dump range 18 (2x33B). Each
// walks the pointer array [this+0x1C, this+0x20) and invokes its callee on
// every element with the caller's int argument. The callees differ, so each
// method gets its own honest opaque owner class (the Rva002D352C-family
// idiom); no shared-class claim is made.
//
// ?rva003EDDD4@Rva003EDDD4@@QAEXH@Z @0x003EDDD4: callee 0x0056A4AA (pinned).
// ?rva003EDDF5@Rva003EDDF5@@QAEXH@Z @0x003EDDF5: callee 0x00569373 (pinned).
class Rva0056A4AA
{
public:
	void rva0056A4AA(int arg);
};

class Rva003EDDD4
{
public:
	void rva003EDDD4(int arg);
private:
	char m_pad[0x1C];
	Rva0056A4AA **m_first1C;
	Rva0056A4AA **m_end20;
};

void Rva003EDDD4::rva003EDDD4(int arg)
{
	for (Rva0056A4AA **pp = m_first1C; pp != m_end20; ++pp)
		(*pp)->rva0056A4AA(arg);
}

class Rva00569373
{
public:
	void rva00569373(int arg);
};

class Rva003EDDF5
{
public:
	void rva003EDDF5(int arg);
private:
	char m_pad[0x1C];
	Rva00569373 **m_first1C;
	Rva00569373 **m_end20;
};

void Rva003EDDF5::rva003EDDF5(int arg)
{
	for (Rva00569373 **pp = m_first1C; pp != m_end20; ++pp)
		(*pp)->rva00569373(arg);
}
