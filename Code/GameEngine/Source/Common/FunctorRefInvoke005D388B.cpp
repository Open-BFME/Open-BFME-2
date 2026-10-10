// cl: /O1 /EHsc /MD /D_CRTIMP=
//
// ?invoke@Rva005D388BRef@@QAE?AURva005D388BValue@@XZ, retail 0x005D388B,
// 61B. Null-guard functor dispatch in the FunctorNotSet family (siblings
// 0x0057CC15 and 0x001531F2): with no operation (+0x00) it throws
// FunctorNotSet (shared throw info 0x00D0B644), built inline here through
// the imported std::exception ctor and vtable 0x00BD3B54; otherwise the
// operation's virtual slot 1 returns a one-word value by hidden pointer.
// Retail's zeroed [ebp-4] is the returned-object flag MSVC keeps for a
// value type with a destructor. Caller 0x005D3AB2 passes a local result.
// The value type and owner stay address-derived.
class exception
{
public:
	__declspec(dllimport) exception();
	virtual ~exception();
private:
	const char *m_what;
	int m_doFree;
};
class FunctorNotSet : public exception
{
public:
	FunctorNotSet() {}
};
struct Rva005D388BValue
{
	Rva005D388BValue() : m_ptr(0) {}
	~Rva005D388BValue();
	void *m_ptr;
};
class Rva005D388BOp
{
public:
	virtual ~Rva005D388BOp();
	virtual Rva005D388BValue invoke();
};
class Rva005D388BRef
{
public:
	Rva005D388BValue invoke();
private:
	Rva005D388BOp *m_op;
};
Rva005D388BValue Rva005D388BRef::invoke()
{
	Rva005D388BOp *op = m_op;
	if (op == 0)
		throw FunctorNotSet();
	return op->invoke();
}
