// cl: /O1 /MD
//
// Scalar deleting destructors for the Rva003B31DF/Rva003B3204 leaf chain
// classes (see Rva003BClearLeaves.cpp for clear()). Each inlined destructor
// just clears its chain, so the scalar deleting destructor is clear plus a
// flags-tested operator delete:
// ?rva00396A5C pattern does not apply; these are vanilla ??_G bodies.
// ?_GRva003B31DF (0x003B33C2) and ?_GRva003B3204 (0x003B33DE), 28B each.
// Evidence: each calls its rowed clear (0x003B31DF / 0x003B3204) then the
// rowed operator delete at 0x0002FD60 under the low flags bit.

class Rva003B31DF
{
public:
	~Rva003B31DF() { clear(); }
	void clear();

private:
	Rva003B31DF *m_next;
};

class Rva003B3204
{
public:
	~Rva003B3204() { clear(); }
	void clear();

private:
	Rva003B3204 *m_next;
};

// ?Rva003BDeleteAnchor absent-from-retail
void Rva003BDeleteAnchor(Rva003B31DF *a, Rva003B3204 *b)
{
	delete a;
	delete b;
}
