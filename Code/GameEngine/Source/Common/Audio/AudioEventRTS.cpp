// cl: /O1
// Audio/AudioEventRTS.cpp: three address-named forwarders retail links from this
// TU (tu_map approved by address contiguity), folded from split units with
// these exact flags, in retail order.

// ?rva002D9AD4@Rva002D9AD4@@QAEAAVBfmePoolRef10@@ABV2@@Z @ 0x002D9AD4 8B
// Tail-jmp assign forwarder: return m_pool = other where m_pool is BfmePoolRef10 at +0x10.
// Evidence: honest address name; add ecx 0x10 jmp to rowed ??4BfmePoolRef10@@QAEAAV0@ABV0@@Z; callers in FUN_0045a451 and FUN_0045dd40; neighbours BfmeStringTailRecord144 dtor and CDManager getPath.
class BfmePoolRef10
{
public:
	BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
};
class Rva002D9AD4
{
public:
	BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other);
	char m_pad[0x10];
	BfmePoolRef10 m_pool;
};
BfmePoolRef10 &Rva002D9AD4::rva002D9AD4(const BfmePoolRef10 &other)
{
	return m_pool = other;
}

// ?rva002D9BDC@Rva002D9BDC@@QAEXMM@Z @ 0x002D9BDC 43B
// Evidence: honest address method; thiscall void(float float) ret 8; member float at +0x64 clamped via rowed clamp<float>(lo val hi); callers at 0x0005AAC2 0x0005D60F; neighbours AsciiStringRvoGetters and Rva002D9C2FAssign.
template <class NUM>
NUM clamp(NUM lo, NUM val, NUM hi);

class Rva002D9BDC
{
	char m_pad[0x64];
	float m_64;

public:
	void rva002D9BDC(float lo, float hi);
};

void Rva002D9BDC::rva002D9BDC(float lo, float hi)
{
	m_64 = clamp(lo, m_64, hi);
}

// ?rva002D9C2F@Rva002D9C2F@@QAEAAUOpaqueRefElement4@@ABU2@@Z @ 0x002D9C2F 8B
// Tail-jmp assign forwarder: return m_ref = other where m_ref is OpaqueRefElement4 at +8.
// Evidence: honest address name; add ecx 8 jmp to rowed ??4OpaqueRefElement4@@QAEAAU0@ABU0@@Z; callers in FUN_0045a451 and others; neighbours CDManager getPath and BfmeStringTailRecord144 deleting dtor.
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
class Rva002D9C2F
{
public:
	OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other);
	char m_pad[8];
	OpaqueRefElement4 m_ref;
};
OpaqueRefElement4 &Rva002D9C2F::rva002D9C2F(const OpaqueRefElement4 &other)
{
	return m_ref = other;
}

// ?rva002D9AC3@Rva002D9AC3@@QAEPBDXZ @ 0x002D9AC3 17B
// Honest address-named thiscall getter: if ptr at +8 is null return empty
// string else return ptr+8. Evidence: 17B shape mov eax [ecx+8] test je
// add 8 ret mov empty ret; compiler empty-string literal; callers at
// 0x00054777 0x000547BC 0x00055ED8 0x00055F5E 0x0005BC43 0x002D9D8D;
// neighbours 0x002D9A43 dtor and 0x002D9AD4 forwarder in this TU.
class Rva002D9AC3
{
public:
	const char *rva002D9AC3();
	char m_pad[8];
	char *m_ptr;
};

const char *Rva002D9AC3::rva002D9AC3()
{
	if (m_ptr != 0)
		return m_ptr + 8;
	return "";
}
