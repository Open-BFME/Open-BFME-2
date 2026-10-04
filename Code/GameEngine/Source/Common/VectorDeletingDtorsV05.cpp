// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V05: 78-byte bodies (element size pushed as imm32) that, for
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
//   0x000025B2  0x0000240E  0x9C  0x00BBB5C8#0
//   0x001FC052  0x001FBF4D  0xD4  0x00BE1A28#0
//   0x003A628B  0x003A6201  0x8C  0x00C1BA70#0
//   0x003A63EE  0x003A6201  0x98  0x00C1BAA0#0
//   0x003A6C0B  0x0049B47C  0x8C  0x00C1BBA0#0
//   0x003A6D11  0x003A6201  0x94  0x00C1BBB0#0
//   0x003A805A  0x0049B47C  0x98  0x00C1BDB0#0
//   0x003A8160  0x003A6201  0xA0  0x00C1BDC0#0
//   0x003A8ACB  0x003A9397  0x8C  0x00C1BF20#0
//   0x003A8B51  0x003A9397  0x98  0x00C1BF40#0
//   0x003A8D6D  0x003A9397  0xA0  0x00C1BFD8#0
//   0x003A9329  0x003A9397  0x94  0x00C1C154#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Rva0000240E
{
public:
	virtual ~Rva0000240E();
private:
	char m_unmodelled_04[0x9C - 0x04];
};

class Rva001FBF4D
{
public:
	virtual ~Rva001FBF4D();
private:
	char m_unmodelled_04[0xD4 - 0x04];
};

class Rva003A628BVecBase0
{
public:
	virtual ~Rva003A628BVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A628BVecBase8
{
public:
	virtual ~Rva003A628BVecBase8();
private:
	char m_unmodelled_04[0x84 - 0x04];
};

class Rva003A628BVec : public Rva003A628BVecBase0, public Rva003A628BVecBase8
{
public:
	virtual ~Rva003A628BVec();
};

class Rva003A63EEVecBase0
{
public:
	virtual ~Rva003A63EEVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A63EEVecBase8
{
public:
	virtual ~Rva003A63EEVecBase8();
private:
	char m_unmodelled_04[0x90 - 0x04];
};

class Rva003A63EEVec : public Rva003A63EEVecBase0, public Rva003A63EEVecBase8
{
public:
	virtual ~Rva003A63EEVec();
};

class Rva003A6C0BVec
{
public:
	virtual ~Rva003A6C0BVec();
private:
	char m_unmodelled_04[0x8C - 0x04];
};

class Rva003A6D11VecBase0
{
public:
	virtual ~Rva003A6D11VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A6D11VecBase8
{
public:
	virtual ~Rva003A6D11VecBase8();
private:
	char m_unmodelled_04[0x8C - 0x04];
};

class Rva003A6D11Vec : public Rva003A6D11VecBase0, public Rva003A6D11VecBase8
{
public:
	virtual ~Rva003A6D11Vec();
};

class Rva003A805AVec
{
public:
	virtual ~Rva003A805AVec();
private:
	char m_unmodelled_04[0x98 - 0x04];
};

class Rva003A8160VecBase0
{
public:
	virtual ~Rva003A8160VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A8160VecBase8
{
public:
	virtual ~Rva003A8160VecBase8();
private:
	char m_unmodelled_04[0x98 - 0x04];
};

class Rva003A8160Vec : public Rva003A8160VecBase0, public Rva003A8160VecBase8
{
public:
	virtual ~Rva003A8160Vec();
};

class Rva003A8ACBVecBase0
{
public:
	virtual ~Rva003A8ACBVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A8ACBVecBase8
{
public:
	virtual ~Rva003A8ACBVecBase8();
private:
	char m_unmodelled_04[0x84 - 0x04];
};

class Rva003A8ACBVec : public Rva003A8ACBVecBase0, public Rva003A8ACBVecBase8
{
public:
	virtual ~Rva003A8ACBVec();
};

class Rva003A8B51VecBase0
{
public:
	virtual ~Rva003A8B51VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A8B51VecBase8
{
public:
	virtual ~Rva003A8B51VecBase8();
private:
	char m_unmodelled_04[0x90 - 0x04];
};

class Rva003A8B51Vec : public Rva003A8B51VecBase0, public Rva003A8B51VecBase8
{
public:
	virtual ~Rva003A8B51Vec();
};

class Rva003A8D6DVecBase0
{
public:
	virtual ~Rva003A8D6DVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A8D6DVecBase8
{
public:
	virtual ~Rva003A8D6DVecBase8();
private:
	char m_unmodelled_04[0x98 - 0x04];
};

class Rva003A8D6DVec : public Rva003A8D6DVecBase0, public Rva003A8D6DVecBase8
{
public:
	virtual ~Rva003A8D6DVec();
};

class Rva003A9329VecBase0
{
public:
	virtual ~Rva003A9329VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class Rva003A9329VecBase8
{
public:
	virtual ~Rva003A9329VecBase8();
private:
	char m_unmodelled_04[0x8C - 0x04];
};

class Rva003A9329Vec : public Rva003A9329VecBase0, public Rva003A9329VecBase8
{
public:
	virtual ~Rva003A9329Vec();
};

// ?<bfmeVectorDeleteAnchorV05> absent-from-retail
void bfmeVectorDeleteAnchorV05()
{
	new Rva0000240E[2];
	new Rva001FBF4D[2];
	new Rva003A628BVec[2];
	new Rva003A63EEVec[2];
	new Rva003A6C0BVec[2];
	new Rva003A6D11Vec[2];
	new Rva003A805AVec[2];
	new Rva003A8160Vec[2];
	new Rva003A8ACBVec[2];
	new Rva003A8B51Vec[2];
	new Rva003A8D6DVec[2];
	new Rva003A9329Vec[2];
}
