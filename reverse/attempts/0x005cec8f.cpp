// ?Rva005CEC8FCreate@@YAPAVRva005CEC8F@@PAV1@PBUPayload@Rva005CEAE6@@@Z
// partial score=0.8052 date=2026-10-06
// ?Rva005CEC8FCreate@@YAPAVRva005CEC8F@@PAV1@PBUPayload@Rva005CEAE6@@@Z
// partial score=0.92 date=2026-10-04
// Rva005CEC8FCreate, retail 0x005CEC8F, 50 bytes.
// Free __cdecl creator: guarded new of the payload class with +4 refcount and
// 3-dword payload from *src, stores to out+0 with AddRef inc, returns out.
// Evidence: packet disassembly, push size call ??2@YAPAXI@Z row, test je xor null
// path, push arg call Rva005CEAE6 row, store to [ecx] with inc [eax+4], leave ret.
// new (std::nothrow) at /O1 /Oy- reaches 51B (one over); retail's guard is
// push ecx + and [ebp-4],0 around a single operator new call.
// cl: /O1 /MD /Oy-
#include <new>

class Rva005CEAE6
{
public:
	struct Payload { int v[3]; };
	Rva005CEAE6(const Payload *src) throw();
	virtual ~Rva005CEAE6() throw() {}
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CEC8F
{
public:
	Rva005CEAE6 *m_00;
};

// ?Rva005CEC8FCreate@@YAPAVRva005CEC8F@@PAV1@PBUPayload@Rva005CEAE6@@@Z present-unmatched
Rva005CEC8F * __cdecl Rva005CEC8FCreate(Rva005CEC8F *out, const Rva005CEAE6::Payload *src)
{
	Rva005CEAE6 *p = new (std::nothrow) Rva005CEAE6(src);
	out->m_00 = p;
	if (p != 0)
		p->m_ref++;
	return out;
}
