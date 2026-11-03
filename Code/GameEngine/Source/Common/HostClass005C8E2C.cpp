// cl: /EHsc /MD
// ?rva005C8E2C@HostClass005C8E0A@@QAE?AVBfmePoolRef10@@XZ @0x005C8E2C 135B
// Take the pool ref at +8: if null return null, else copy to a local,
// clear the member, clear byte +0x46, adjust via LargeGroupAudioGridCell(false) and
// HostClass005C8E0A::method_005C8E0A, then return the saved ref.
// Evidence: calls to 0x51950 copy-ctor, 0x519BD clear, 0x5C87F8 bool,
// 0x5C8E0A method, Release_Ref at 0x50ED3; caller 0x56A430.

#include "../../Include/Common/BfmePoolRef10.h"

class LargeGroupAudioGridCell
{
public:
	void setOverlappedLocking(bool flag);
};

struct Element005C8E0A;
class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	void method_005C9069();
	void rva005C8F17();
	BfmePoolRef10 rva005C8E2C();
	char m_pad00[0x8];
private:
	BfmePoolRef10 m_pool08; // +0x08
	char m_pad0C[0x2C];
public:
	Element005C8E0A *m_start; // +0x38
	Element005C8E0A *m_finish; // +0x3C
	char m_pad40[0x6];
private:
	unsigned char m_byte46; // +0x46
	char m_pad47[0x1];
};

BfmePoolRef10 HostClass005C8E0A::rva005C8E2C()
{
	if (m_pool08.m_target == 0)
		return BfmePoolRef10();
	BfmePoolRef10 tmp = m_pool08;
	m_pool08.rva000519BD();
	m_byte46 = 0;
	((LargeGroupAudioGridCell *)this)->setOverlappedLocking(false);
	method_005C8E0A();
	return tmp;
}
