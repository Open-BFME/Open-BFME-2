// cl: /MD /EHsc
//
// Copy ctors for the Rva003B31DF/Rva003B3204 leaf chains at 0x003B3221
// (86B, ??0Rva003B31DF@@QAE@ABV0@@Z) and 0x003B3277 (86B,
// ??0Rva003B3204@@QAE@ABV0@@Z). Each leaf is 0xC bytes (next at +0 plus
// two ints at +4/+8, read off the retail new size and the two tail
// stores); the copy deep-copies the next chain via a recursive new then
// copies the two ints. Together they are the callees of the Rva003B4071
// holder copy at 0x003B3FCD (first head via 0x3221, second via 0x3277),
// mirroring how ?clear@Rva003B4071@@QAEXXZ at 0x003B4071 drains the same
// two chains second-then-first. Address-derived names; identity follows
// the rowed clear leaves in Rva003BClearLeaves.cpp and the double helper
// in OpaqueScalarDeletingDtors.cpp. Callers: 0x003B4003/0x003B4032 in
// 0x003B3FCD plus self-recursion. Flags are the neighbour leaf TU plus
// /EHsc for the retail EH prolog.

class Rva003B31DF
{
public:
	Rva003B31DF(const Rva003B31DF &other);

private:
	Rva003B31DF *m_next;
	int m_a;
	int m_b;
};

Rva003B31DF::Rva003B31DF(const Rva003B31DF &other)
{
	m_next = other.m_next ? new Rva003B31DF(*other.m_next) : 0;
	m_a = other.m_a;
	m_b = other.m_b;
}

class Rva003B3204
{
public:
	Rva003B3204(const Rva003B3204 &other);

private:
	Rva003B3204 *m_next;
	int m_a;
	int m_b;
};

Rva003B3204::Rva003B3204(const Rva003B3204 &other)
{
	m_next = other.m_next ? new Rva003B3204(*other.m_next) : 0;
	m_a = other.m_a;
	m_b = other.m_b;
}
