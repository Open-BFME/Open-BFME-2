// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004FF6FF@@QAE@II@Z @0x004FF6FF 42B: empty _Rb_tree ctor calls rowed base 0x004FF515 with second arg then zeroes node count and inits header (color 0 parent 0 left/right self). Evidence: chain lane calls 0x004FF515 just landed; same 42B shape as Rva004FF6AB 0x004FF6AB; caller 0x00502D57; unblocks 0x00502D48.
class Rva004FF515
{
public:
	Rva004FF515(unsigned dummy);
};

struct Rva004FF6FFHeader
{
	unsigned char m_color;
	unsigned char m_pad[3];
	Rva004FF6FFHeader *m_parent;
	Rva004FF6FFHeader *m_left;
	Rva004FF6FFHeader *m_right;
};

class Rva004FF6FF
{
public:
	Rva004FF6FF(unsigned dummy0, unsigned dummy1);
private:
	Rva004FF515 m_base;
	unsigned m_count;
};

Rva004FF6FF::Rva004FF6FF(unsigned, unsigned b) : m_base(b)
{
	m_count = 0;
	(*(Rva004FF6FFHeader **)&m_base)->m_color = 0;
	(*(Rva004FF6FFHeader **)&m_base)->m_parent = 0;
	(*(Rva004FF6FFHeader **)&m_base)->m_left = *(Rva004FF6FFHeader **)&m_base;
	(*(Rva004FF6FFHeader **)&m_base)->m_right = *(Rva004FF6FFHeader **)&m_base;
}
