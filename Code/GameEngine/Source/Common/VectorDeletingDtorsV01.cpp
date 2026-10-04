// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V01: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot
//   0x003A7ABD  0x0049B47C  0x04  0x00BE1584#0
//   0x003A85CC  0x003A9397  0x0C  0x00C1BE20#0
//   0x003A743E  0x003A9397  0x18  0x00C1C020#0
//   0x003A6AAA  0x003A6201  0x28  0x00C1BB20#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
};

class Rva003A9397
{
public:
	virtual ~Rva003A9397();
private:
	char m_unmodelled_04[0xC - 0x04];
};

class Rva003A743EVec
{
public:
	virtual ~Rva003A743EVec();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

class Rva003A6201
{
public:
	virtual ~Rva003A6201();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

// ?<bfmeVectorDeleteAnchorV01> absent-from-retail
void bfmeVectorDeleteAnchorV01()
{
	new Rva0049B47C[2];
	new Rva003A9397[2];
	new Rva003A743EVec[2];
	new Rva003A6201[2];
}
