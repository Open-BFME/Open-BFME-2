// cl: /DNDEBUG /MD /GX-
// ??0Made002CC9D4@@QAE@XZ, retail 0x0050AEAB, 57 bytes.
// Evidence: pin ??0Made002CC9D4@@QAE@XZ; rowed base Rva00507823 0x0050775B;
// vtable 0x00864BB0 plus dword +0x128=0 plus two 0x1C members at +0x12c/+0x148
// via rowed 0x0024C7B3 plus dword +0x164=1; caller parseDamageContainedNugget
// 0x002CC9F9 news 0x168; sibling Made002CCBCA precedent for base+members.
class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	char m_pad04[0x128 - 4];
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
private:
	char m_bytes[0x1C];
};

class Made002CC9D4 : public Rva00507823
{
public:
	Made002CC9D4();
private:
	int m_128;
	Rva0024C7B3Member m_12c;
	Rva0024C7B3Member m_148;
	int m_164;
};

Made002CC9D4::Made002CC9D4()
	: m_128(0)
	, m_164(1)
{
}
