// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003193D1@Rva003193D1@@QAEXXZ @0x003193D1 27B
// Thiscall method syncing via rowed 0x00318F64 then forwarding 0 to the
// object at +0x88 via rowed 0x003FDE8C when present. Evidence: packet
// disasm with two rowed callees plus pin, prev/next rows share flags,
// caller 0x002B7C37, unblocks 0x002B7BFB.
class Rva00318F64
{
public:
	void rva00318F64();
};

class Rva003FDE8C
{
public:
	void rva003FDE8C(unsigned char v);
};

class Rva003193D1
{
public:
	void rva003193D1();
private:
	char m_pad[0x88];
	Rva003FDE8C *m_88;
};

void Rva003193D1::rva003193D1()
{
	((Rva00318F64 *)this)->rva00318F64();
	if (m_88)
		m_88->rva003FDE8C(0);
}
