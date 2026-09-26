// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ?invoke@Rva001531F2Ref@@QAEHHH@Z, retail 0x001531F2 (49 bytes). Null-guard
// functor dispatch in the FunctorNotSet family (TimedOperationRef::update
// 0x003FE6A0 plus 7 sites): the frame holds a 0x0C-byte exception slot
// (sub esp,0x0C, lea ecx,[ebp-0x0C]) default-constructed through the rowed
// ??0FunctorNotSet@@QAE@XZ at 0x002035E2, then _CxxThrowException with the
// shared 0x00D0B644 throw info; the live path forwards two int args to
// virtual slot 1 (call dword ptr [eax+4], ret 8). Callers at 0x001532C6
// (in 0x0015326D vector-loop) and 0x0057C2AC (in 0x0057C26C) pass dwords.
// Gap between 0x001531C9 and 0x00153223 of
// stlport_pod_vector_malloc_bodies.cpp, same // cl: fits (no STL use).
// Class/method names address-derived (identity beyond Functor family
// unproven); FunctorNotSet is the proven throw type; op layout (ptr at +0)
// and slot-1 signature (int,int)->int evidenced by the two pushes and
// call [eax+4].
class FunctorNotSet
{
public:
	FunctorNotSet();
	virtual ~FunctorNotSet();
private:
	char m_pad[0x0C - 4];
};
class Rva001531F2Op
{
public:
	virtual ~Rva001531F2Op();
	virtual int invoke(int a, int b);
};
class Rva001531F2Ref
{
public:
	int invoke(int a, int b);
private:
	Rva001531F2Op *m_op;
};
int Rva001531F2Ref::invoke(int a, int b)
{
	Rva001531F2Op *op = m_op;
	if (op == 0) {
		throw FunctorNotSet();
	}
	return op->invoke(a, b);
}
