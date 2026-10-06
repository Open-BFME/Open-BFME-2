// cl: /DNDEBUG /MD
// ??0Rva00332EC8@@QAE@ABV0@@Z @0x00332EC8 43B
// retail 0x00332EC8 43 bytes chain copy dword at +0 plus two BfmeObject872Header at +4 and +0x14
// via rowed BfmeObject872Header copy 0x002CF108 caller 0x003332A1 unblocks 0x00333295
// neighbours prev 0x00332E9D Object156Copy and next 0x00332EF3 StlportObject156Vector

class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &that) throw();
private:
	char m_data[16];
};

class Rva00332EC8
{
public:
	Rva00332EC8(const Rva00332EC8 &that);
private:
	unsigned int m_key;
	BfmeObject872Header m_a;
	BfmeObject872Header m_b;
};

Rva00332EC8::Rva00332EC8(const Rva00332EC8 &that) : m_key(that.m_key), m_a(that.m_a), m_b(that.m_b)
{
}
