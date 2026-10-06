// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva000A79CE@Rva000A79CE@@QAEXXZ, retail 0x000A79CE, 41 bytes.
// _Rb_tree clear for the TreeKey00242F5E set: if node count at +4 is nonzero,
// erase the root at header+4 via rowed 0x000A7941, then header->left=header,
// header->parent=0, header->right=header and count=0. Header layout is the
// standard node-base {color,parent,left,right}. Evidence: callers at 0x000A7A10
// in 0x000A79F7 and 0x000A7C03 in 0x000A7BEE; neighbours 0x000A799B and
// 0x000A7AA7 share the same cl flags.
class Rva000A7941
{
public:
	void rva000A7941(void *p);
};

struct Rva000A79CEHeader
{
	int m_color;
	void *m_parent;
	Rva000A79CEHeader *m_left;
	Rva000A79CEHeader *m_right;
};

class Rva000A79CE
{
public:
	void rva000A79CE();
private:
	Rva000A79CEHeader *m_header;
	unsigned int m_count;
};

void Rva000A79CE::rva000A79CE()
{
	if (m_count != 0) {
		((Rva000A7941 *)this)->rva000A7941(m_header->m_parent);
		m_header->m_left = m_header;
		m_header->m_parent = 0;
		m_header->m_right = m_header;
		m_count = 0;
	}
}
