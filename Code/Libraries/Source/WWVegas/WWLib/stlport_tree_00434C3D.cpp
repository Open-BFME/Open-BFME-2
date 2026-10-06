// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00434C3D@@QAE@II@Z @0x00434C3D 42B: empty _Rb_tree ctor for map<AsciiString TreeHintOpaque0043671B> calls rowed base 0x00434942 with second arg then zeroes node count and inits header (color 0 parent 0 left/right self). Evidence: chain lane calls 0x00434942 just landed; same 42B shape as NameKey PristineBone 0x00425FEC; unblocks caller 0x00435CEF; next _M_erase 0x00434E94 same tree.
class Rva00434942
{
public:
	Rva00434942(unsigned dummy);
};

struct Rva00434C3DHeader
{
	unsigned char m_color;
	unsigned char m_pad[3];
	Rva00434C3DHeader *m_parent;
	Rva00434C3DHeader *m_left;
	Rva00434C3DHeader *m_right;
};

class Rva00434C3D
{
public:
	Rva00434C3D(unsigned dummy0, unsigned dummy1);
private:
	Rva00434942 m_base;
	unsigned m_count;
};

Rva00434C3D::Rva00434C3D(unsigned, unsigned b) : m_base(b)
{
	m_count = 0;
	(*(Rva00434C3DHeader **)&m_base)->m_color = 0;
	(*(Rva00434C3DHeader **)&m_base)->m_parent = 0;
	(*(Rva00434C3DHeader **)&m_base)->m_left = *(Rva00434C3DHeader **)&m_base;
	(*(Rva00434C3DHeader **)&m_base)->m_right = *(Rva00434C3DHeader **)&m_base;
}
