// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva00229811@@QAE@XZ, retail 0x00229811, 47 bytes.
// Evidence: retail zeroes the dword at +0, enters unwind state 0, constructs
// the member at +4 through 0x002DD173 and returns this. State 0's funclet
// destroys the +0 object through 0x005B804B, so +0 is a pointer-sized object
// with an inline null ctor and an out-of-line dtor; its name is generated.
// The +4 member is BfmeSubobject0022CE19, whose rowed dtor sits at 0x002DD1E9
// directly after 0x002DD173; that default ctor is pinned here, not claimed
// (its own recovery is blocked in re_attempts.log).

class Rva005B804B
{
public:
	Rva005B804B() : m_ptr(0) {}
	~Rva005B804B();

private:
	void *m_ptr;
};

class BfmeSubobject0022CE19
{
public:
	BfmeSubobject0022CE19();
	virtual ~BfmeSubobject0022CE19();
};

class Rva00229811
{
public:
	Rva00229811();

private:
	Rva005B804B m_at00;
	BfmeSubobject0022CE19 m_at04;
};

Rva00229811::Rva00229811()
{
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??0TreeHintOpaque0043671B@@QAE@XZ=??0Rva00229811@@QAE@XZ")
