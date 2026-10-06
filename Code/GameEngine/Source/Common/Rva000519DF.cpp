// cl: /MD
//
// ?rva000519DF@Rva000519DF@@QAEPAV1@PAPAXABVBfmePoolRef10@@@Z @0x000519DF 29B
// Pool-ref pair setter returning this. Evidence: __thiscall via ecx plus
// ret-8 two stack args; deref arg1 plus store to [this] plus copy-ctor
// rowed BfmePoolRef10 0x00051950 for [this+4] from arg2; 1 caller plus
// 1 unblock; name stays address-derived.
class BfmePoolRef10
{
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
};

class Rva000519DF
{
public:
	Rva000519DF *rva000519DF(void **a1, const BfmePoolRef10 &a2);

private:
	void *m_ptr0;
	BfmePoolRef10 m_ref4;
};

Rva000519DF *Rva000519DF::rva000519DF(void **a1, const BfmePoolRef10 &a2)
{
	m_ptr0 = *a1;
	m_ref4.BfmePoolRef10::BfmePoolRef10(a2);
	return this;
}
