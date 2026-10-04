// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V04: 75-byte bodies that, for
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
//   0x003A8BD7  0x003A9397  0x2C  0x00C1BF60#0
//   0x003A8C5A  0x003A9397  0x70  0x00C1BF84#0
//   0x003A8E25  0x003A9397  0x30  0x00C1BFFC#0
//   0x003A9057  0x003A9397  0x10  0x00C1C0A0#0
//   0x003A9152  0x003A9397  0x1C  0x00C1C0E8#0
//   0x003A91E3  0x003A9397  0x14  0x00C1C10C#0
//   0x003A9951  0x003A9F8A  0x18  0x00C1C188#0
//   0x003A9A40  0x003AA0C0  0x24  0x00C1C198#0
//   0x003A9B97  0x003A9A8B  0x40  0x00C1C1B8#0
//   0x003A9CF8  0x003A9C39  0x48  0x00C1C1C8#0
//   0x003A9DDE  0x003A9D43  0x14  0x00C1C1E8#0
//   0x003A9F3F  0x003A9E80  0x1C  0x00C1C1F8#0
//   0x003AA02D  0x003A9F8A  0x1C  0x00C1C218#0
//   0x003AA17F  0x003AA0C0  0x28  0x00C1C228#0
//   0x003AA704  0x003AA6BD  0x48  0x00C1C270#0
//   0x003AA7B6  0x003AA76F  0x1C  0x00C1C294#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Rva003A8BD7Vec
{
public:
	virtual ~Rva003A8BD7Vec();
private:
	char m_unmodelled_04[0x2C - 0x04];
};

class Rva003A8C5AVec
{
public:
	virtual ~Rva003A8C5AVec();
private:
	char m_unmodelled_04[0x70 - 0x04];
};

class Rva003A8E25Vec
{
public:
	virtual ~Rva003A8E25Vec();
private:
	char m_unmodelled_04[0x30 - 0x04];
};

class Rva003A9057Vec
{
public:
	virtual ~Rva003A9057Vec();
private:
	char m_unmodelled_04[0x10 - 0x04];
};

class Rva003A9152Vec
{
public:
	virtual ~Rva003A9152Vec();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003A91E3Vec
{
public:
	virtual ~Rva003A91E3Vec();
private:
	char m_unmodelled_04[0x14 - 0x04];
};

class Rva003A9F8A
{
public:
	virtual ~Rva003A9F8A();
private:
	char m_unmodelled_04[0x18 - 0x04];
};

class Rva003AA0C0
{
public:
	virtual ~Rva003AA0C0();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003A9A8B
{
public:
	virtual ~Rva003A9A8B();
private:
	char m_unmodelled_04[0x40 - 0x04];
};

class Rva003A9C39
{
public:
	virtual ~Rva003A9C39();
private:
	char m_unmodelled_04[0x48 - 0x04];
};

class Rva003A9D43
{
public:
	virtual ~Rva003A9D43();
private:
	char m_unmodelled_04[0x14 - 0x04];
};

class Rva003A9E80
{
public:
	virtual ~Rva003A9E80();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003AA02DVec
{
public:
	virtual ~Rva003AA02DVec();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003AA17FVec
{
public:
	virtual ~Rva003AA17FVec();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

class Rva003AA6BD
{
public:
	virtual ~Rva003AA6BD();
private:
	char m_unmodelled_04[0x48 - 0x04];
};

class Rva003AA76F
{
public:
	virtual ~Rva003AA76F();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

// ?<bfmeVectorDeleteAnchorV04> absent-from-retail
void bfmeVectorDeleteAnchorV04()
{
	new Rva003A8BD7Vec[2];
	new Rva003A8C5AVec[2];
	new Rva003A8E25Vec[2];
	new Rva003A9057Vec[2];
	new Rva003A9152Vec[2];
	new Rva003A91E3Vec[2];
	new Rva003A9F8A[2];
	new Rva003AA0C0[2];
	new Rva003A9A8B[2];
	new Rva003A9C39[2];
	new Rva003A9D43[2];
	new Rva003A9E80[2];
	new Rva003AA02DVec[2];
	new Rva003AA17FVec[2];
	new Rva003AA6BD[2];
	new Rva003AA76F[2];
}
