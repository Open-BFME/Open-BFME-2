// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004FF6AB@@QAE@II@Z @0x004FF6AB 42B: empty _Rb_tree ctor calls rowed base 0x004FF4F1 with second arg then zeroes node count and inits header (color 0 parent 0 left/right self). Evidence: chain lane calls 0x004FF4F1 just landed; same 42B shape as Rva00434C3D 0x00434C3D; caller 0x00501228; unblocks 0x00501219.
class Rva004FF4F1
{
public:
	Rva004FF4F1(unsigned dummy);
};

struct Rva004FF6ABHeader
{
	unsigned char m_color;
	unsigned char m_pad[3];
	Rva004FF6ABHeader *m_parent;
	Rva004FF6ABHeader *m_left;
	Rva004FF6ABHeader *m_right;
};

class Rva004FF6AB
{
public:
	Rva004FF6AB(unsigned dummy0, unsigned dummy1);
private:
	Rva004FF4F1 m_base;
	unsigned m_count;
};

Rva004FF6AB::Rva004FF6AB(unsigned, unsigned b) : m_base(b)
{
	m_count = 0;
	(*(Rva004FF6ABHeader **)&m_base)->m_color = 0;
	(*(Rva004FF6ABHeader **)&m_base)->m_parent = 0;
	(*(Rva004FF6ABHeader **)&m_base)->m_left = *(Rva004FF6ABHeader **)&m_base;
	(*(Rva004FF6ABHeader **)&m_base)->m_right = *(Rva004FF6ABHeader **)&m_base;
}
