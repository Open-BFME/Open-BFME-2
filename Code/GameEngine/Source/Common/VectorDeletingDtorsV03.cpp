// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V03: 75-byte bodies that, for
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
//   0x003A64F0  0x003A6201  0x10  0x00C1BAF0#0
//   0x003A66B2  0x0049B47C  0x14  0x00C1BB30#0
//   0x003A679D  0x003A6201  0x1C  0x00C1BB50#0
//   0x003A6833  0x0049B47C  0x0C  0x00C1BB60#0
//   0x003A690D  0x003A6201  0x14  0x00C1BB80#0
//   0x003A69B4  0x0049B47C  0x20  0x00C1BB00#0
//   0x003A70D1  0x0049B47C  0x28  0x00C1BC00#0
//   0x003A71D4  0x003A6201  0x30  0x00C1BC10#0
//   0x003A72AC  0x0049B47C  0x10  0x00C1BC30#0
//   0x003A73AD  0x003A6201  0x18  0x00C1BC40#0
//   0x003A7532  0x0049B47C  0x1C  0x00C1BC90#0
//   0x003A77A7  0x0049B47C  0x24  0x00C1BCB0#0
//   0x003A7853  0x003A6201  0x2C  0x00C1BCC0#0
//   0x003A795A  0x0049B47C  0x68  0x00C1BCE0#0
//   0x003A7A06  0x003A6201  0x70  0x00C1BCF0#0
//   0x003A7B9F  0x003A6201  0x0C  0x00C1BD60#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Rva003A64F0VecBase0
{
public:
	virtual ~Rva003A64F0VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A64F0VecBase8
{
public:
	virtual ~Rva003A64F0VecBase8();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

class Rva003A64F0Vec : public Rva003A64F0VecBase0, public Rva003A64F0VecBase8
{
public:
	virtual ~Rva003A64F0Vec();
};

class Rva003A66B2Vec
{
public:
	virtual ~Rva003A66B2Vec();
private:
	char m_unmodelled_04[0x14 - 0x04];
};

class Rva003A679DVecBase0
{
public:
	virtual ~Rva003A679DVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A679DVecBase8
{
public:
	virtual ~Rva003A679DVecBase8();
private:
	char m_unmodelled_04[0x14 - 0x04];
};

class Rva003A679DVec : public Rva003A679DVecBase0, public Rva003A679DVecBase8
{
public:
	virtual ~Rva003A679DVec();
};

class Rva003A6833Vec
{
public:
	virtual ~Rva003A6833Vec();
private:
	char m_unmodelled_04[0xC - 0x04];
};

class Rva003A690DVecBase0
{
public:
	virtual ~Rva003A690DVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A690DVecBase8
{
public:
	virtual ~Rva003A690DVecBase8();
private:
	char m_unmodelled_04[0xC - 0x04];
};

class Rva003A690DVec : public Rva003A690DVecBase0, public Rva003A690DVecBase8
{
public:
	virtual ~Rva003A690DVec();
};

class Rva003A69B4Vec
{
public:
	virtual ~Rva003A69B4Vec();
private:
	char m_unmodelled_04[0x20 - 0x04];
};

class Rva003A70D1Vec
{
public:
	virtual ~Rva003A70D1Vec();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

class Rva003A71D4VecBase0
{
public:
	virtual ~Rva003A71D4VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A71D4VecBase8
{
public:
	virtual ~Rva003A71D4VecBase8();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

class Rva003A71D4Vec : public Rva003A71D4VecBase0, public Rva003A71D4VecBase8
{
public:
	virtual ~Rva003A71D4Vec();
};

class Rva003A72ACVec
{
public:
	virtual ~Rva003A72ACVec();
private:
	char m_unmodelled_04[0x10 - 0x04];
};

class Rva003A73ADVecBase0
{
public:
	virtual ~Rva003A73ADVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A73ADVecBase8
{
public:
	virtual ~Rva003A73ADVecBase8();
private:
	char m_unmodelled_04[0x10 - 0x04];
};

class Rva003A73ADVec : public Rva003A73ADVecBase0, public Rva003A73ADVecBase8
{
public:
	virtual ~Rva003A73ADVec();
};

class Rva003A7532Vec
{
public:
	virtual ~Rva003A7532Vec();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003A77A7Vec
{
public:
	virtual ~Rva003A77A7Vec();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003A7853VecBase0
{
public:
	virtual ~Rva003A7853VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A7853VecBase8
{
public:
	virtual ~Rva003A7853VecBase8();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003A7853Vec : public Rva003A7853VecBase0, public Rva003A7853VecBase8
{
public:
	virtual ~Rva003A7853Vec();
};

class Rva003A795AVec
{
public:
	virtual ~Rva003A795AVec();
private:
	char m_unmodelled_04[0x68 - 0x04];
};

class Rva003A7A06VecBase0
{
public:
	virtual ~Rva003A7A06VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A7A06VecBase8
{
public:
	virtual ~Rva003A7A06VecBase8();
private:
	char m_unmodelled_04[0x68 - 0x04];
};

class Rva003A7A06Vec : public Rva003A7A06VecBase0, public Rva003A7A06VecBase8
{
public:
	virtual ~Rva003A7A06Vec();
};

class Rva003A7B9FVecBase0
{
public:
	virtual ~Rva003A7B9FVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A7B9FVecBase8
{
public:
	virtual ~Rva003A7B9FVecBase8();
};

class Rva003A7B9FVec : public Rva003A7B9FVecBase0, public Rva003A7B9FVecBase8
{
public:
	virtual ~Rva003A7B9FVec();
};

// ?<bfmeVectorDeleteAnchorV03> absent-from-retail
void bfmeVectorDeleteAnchorV03()
{
	new Rva003A64F0Vec[2];
	new Rva003A66B2Vec[2];
	new Rva003A679DVec[2];
	new Rva003A6833Vec[2];
	new Rva003A690DVec[2];
	new Rva003A69B4Vec[2];
	new Rva003A70D1Vec[2];
	new Rva003A71D4Vec[2];
	new Rva003A72ACVec[2];
	new Rva003A73ADVec[2];
	new Rva003A7532Vec[2];
	new Rva003A77A7Vec[2];
	new Rva003A7853Vec[2];
	new Rva003A795AVec[2];
	new Rva003A7A06Vec[2];
	new Rva003A7B9FVec[2];
}
