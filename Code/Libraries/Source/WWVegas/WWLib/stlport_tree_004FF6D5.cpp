// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004FF6D5@@QAE@II@Z @0x004FF6D5 42B: empty _Rb_tree ctor calls rowed base 0x004FF55E with second arg then zeroes node count and inits header (color 0 parent 0 left/right self). Evidence: chain lane calls 0x004FF55E just landed; same 42B shape as Rva004FF6AB 0x004FF6AB; caller 0x004FFEA5.
class Rva004FF55E
{
public:
	Rva004FF55E(unsigned dummy);
};

struct Rva004FF6D5Header
{
	unsigned char m_color;
	unsigned char m_pad[3];
	Rva004FF6D5Header *m_parent;
	Rva004FF6D5Header *m_left;
	Rva004FF6D5Header *m_right;
};

class Rva004FF6D5
{
public:
	Rva004FF6D5(unsigned dummy0, unsigned dummy1);
private:
	Rva004FF55E m_base;
	unsigned m_count;
};

Rva004FF6D5::Rva004FF6D5(unsigned, unsigned b) : m_base(b)
{
	m_count = 0;
	(*(Rva004FF6D5Header **)&m_base)->m_color = 0;
	(*(Rva004FF6D5Header **)&m_base)->m_parent = 0;
	(*(Rva004FF6D5Header **)&m_base)->m_left = *(Rva004FF6D5Header **)&m_base;
	(*(Rva004FF6D5Header **)&m_base)->m_right = *(Rva004FF6D5Header **)&m_base;
}
