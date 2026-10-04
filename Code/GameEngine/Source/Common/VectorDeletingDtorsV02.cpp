// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V02: 75-byte bodies that, for
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
//   0x003A6E82  0x0049B47C  0x30  0x00C1BBD0#0
//   0x003A6F85  0x003A6201  0x38  0x00C1BBE0#0
//   0x003A7614  0x003A6201  0x24  0x00C1BC70#0
//   0x003A8681  0x003A9397  0x38  0x00C1BEA0#0
//   0x003A8FAC  0x003A9397  0x24  0x00C1C058#0
//   0x003A9286  0x003A9397  0x28  0x00C1C0C4#0
//   0x003A93D4  0x003A9397  0x50  0x00C1BFB8#0
//   0x00001EAE  0x00001F18  0x08  0x00BBB58C#0
//   0x00001F64  0x00001F18  0x0C  0x00BBB59C#0
//   0x001F3574  0x0049B47C  0x08  0x00BE1548#0
//   0x001F36C3  0x0049B47C  0x48  0x00BE15A4#0
//   0x001F4540  0x003A6201  0x50  0x00BE16C8#0
//   0x002B3105  0x002A983D  0x2C  0x00BFDFD4#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Rva003A6E82Vec
{
public:
	virtual ~Rva003A6E82Vec();
private:
	char m_unmodelled_04[0x30 - 0x04];
};

class Rva003A6F85Vec
{
public:
	virtual ~Rva003A6F85Vec();
private:
	char m_unmodelled_04[0x38 - 0x04];
};

class Rva003A7614Vec
{
public:
	virtual ~Rva003A7614Vec();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003A8681Vec
{
public:
	virtual ~Rva003A8681Vec();
private:
	char m_unmodelled_04[0x38 - 0x04];
};

class Rva003A8FACVec
{
public:
	virtual ~Rva003A8FACVec();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003A9286Vec
{
public:
	virtual ~Rva003A9286Vec();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

class Rva003A93D4Vec
{
public:
	virtual ~Rva003A93D4Vec();
private:
	char m_unmodelled_04[0x50 - 0x04];
};

class Rva00001F18
{
public:
	virtual ~Rva00001F18();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

class Rva00001F64Vec
{
public:
	virtual ~Rva00001F64Vec();
private:
	char m_unmodelled_04[0xC - 0x04];
};

class Rva001F3574Vec
{
public:
	virtual ~Rva001F3574Vec();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

class Rva001F36C3Vec
{
public:
	virtual ~Rva001F36C3Vec();
private:
	char m_unmodelled_04[0x48 - 0x04];
};

class Rva001F4540Vec
{
public:
	virtual ~Rva001F4540Vec();
private:
	char m_unmodelled_04[0x50 - 0x04];
};

class Rva002A983D
{
public:
	virtual ~Rva002A983D();
private:
	char m_unmodelled_04[0x2C - 0x04];
};

// ?<bfmeVectorDeleteAnchorV02> absent-from-retail
void bfmeVectorDeleteAnchorV02()
{
	new Rva003A6E82Vec[2];
	new Rva003A6F85Vec[2];
	new Rva003A7614Vec[2];
	new Rva003A8681Vec[2];
	new Rva003A8FACVec[2];
	new Rva003A9286Vec[2];
	new Rva003A93D4Vec[2];
	new Rva00001F18[2];
	new Rva00001F64Vec[2];
	new Rva001F3574Vec[2];
	new Rva001F36C3Vec[2];
	new Rva001F4540Vec[2];
	new Rva002A983D[2];
}
