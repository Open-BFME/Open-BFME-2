// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0BfmeObject544@@QAE@XZ @0x004CAD17 74B.
// Default ctor: three member ctors then zero tail at +0x218/+0x21C.
// Evidence: dtor ??1BfmeObject544@@QAE@XZ at 0x004CACB8 plus deleting dtor at 0x004CACFB prove class name; vector<BfmeObject544> at 0x004CB00D plus caller 0x004CB047 constructing temp then push_back prove default ctor identity; callees rowed 0x00042526 0x00254FE4 plus pin 0x0024613C.
class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	char m_pad[0x4C];
};

class Rva00254FE4Member
{
public:
	Rva00254FE4Member();
	~Rva00254FE4Member();
private:
	char m_pad[0x1C0];
};

class Rva0024613CMember
{
public:
	Rva0024613CMember();
	~Rva0024613CMember();
private:
	char m_pad[0x0C];
};

class BfmeObject544
{
public:
	BfmeObject544();
private:
	Rva0042526Member m_00;
	Rva00254FE4Member m_4C;
	Rva0024613CMember m_20C;
	int m_218;
	unsigned char m_21C;
	char m_tail[3];
};

BfmeObject544::BfmeObject544()
{
	m_218 = 0;
	m_21C = 0;
}
