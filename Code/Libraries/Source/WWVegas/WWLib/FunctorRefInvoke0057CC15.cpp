// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ?invoke@Rva0057CC15Ref@@QAEXH@Z, retail 0x0057CC15, 46B. Null-guard functor
// dispatch in the FunctorNotSet family (sibling of 0x001531F2 49B two-int
// version): frame holds 0x0C-byte exception slot default-constructed via rowed
// ??0FunctorNotSet@@QAE@XZ with shared 0xD0B644 throw info; live path forwards
// one int arg to virtual slot 1 (call dword [eax+4] ret 4). Caller 0x223D83
// ignores return (void); op layout ptr at +0 proven by mov ecx,[ecx].

class FunctorNotSet
{
public:
	FunctorNotSet();
	virtual ~FunctorNotSet();
private:
	char m_pad[0x0C - 4];
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_p(0) {}
	RefCountPtr(T *p) : m_p(p) { if (p) ++p->m_refs; }
	~RefCountPtr() { if (m_p) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_p); }
	T *operator->() const { return m_p; }
	T *get() const { return m_p; }

private:
	T *m_p;
};


class Rva0057CC15Op
{
public:
	virtual ~Rva0057CC15Op();
	virtual void invoke(int a);

	int m_refs;	// +0x04
};
class Rva0057CC15Ref
{
public:
	void invoke(int a);

	RefCountPtr<Rva0057CC15Op> m_op;
};
void Rva0057CC15Ref::invoke(int a)
{
	Rva0057CC15Op *op = m_op.get();
	if (op == 0) {
		throw FunctorNotSet();
	}
	op->invoke(a);
}
