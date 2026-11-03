// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small constructors that install their own vtable beside a few cleared
// members, with no direct caller (out-of-line copies; their classes are
// built inline elsewhere). Classes are address-named; the virtual is
// declared inline and empty so the vtable the compiler emits resolves in
// this unit (the Rva0059B7CBCtor.cpp recipe). Retail stores establish the
// members; the vtables are VA 0x00BC6F20 and 0x00C59EA8.

// 0x0040C92D (15B, ret 4): clears +4; the argument is not read.
class Rva0040C92D
{
public:
	Rva0040C92D(int unused);
	virtual void slot00() {}
private:
	int m_04;
};

Rva0040C92D::Rva0040C92D(int)
{
	m_04 = 0;
}

// 0x004BB391 (22B, ret 4): clears +4 and stores the byte argument at +8.
class Rva004BB391
{
public:
	Rva004BB391(bool flag);
	virtual void slot00() {}
private:
	int m_04;
	bool m_flags;
};

Rva004BB391::Rva004BB391(bool flag)
{
	m_04 = 0;
	m_flags = flag;
}
