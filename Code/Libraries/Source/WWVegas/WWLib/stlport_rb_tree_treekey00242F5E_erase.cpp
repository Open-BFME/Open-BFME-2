// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva000A7941@Rva000A7941@@QAEXPAX@Z, retail 0x000A7941, 53 bytes.
// Rb-tree _M_erase for the TreeKey00242F5E set (unsigned id at +0 plus
// AsciiString at +4): recurse on right child at node+0x0C then loop on left
// at node+0x08 destroying the value at node+0x10 and freeing the node.
// The value teardown calls 0x0029D7C2 rowed as ??1CameraMarker@@QAE@XZ whose
// identical 8B uint-plus-AsciiString bytes serve the TreeKey dtor (ICF twin
// ??1TreeKey00242F5E pinned at the same address); node release is the rowed
// _free at 0x00030830. Same 53B shape as Rva0032EAA1 at 0x0032EAA1 and the
// BfmeRecord001DD3BC erase at 0x001DD894. Caller 0x000A79DC in 0x000A79CE
// clear passes the root; landing this unblocks 0x000A79CE.
extern "C" void free(void *p);

struct TreeKey00242F5E
{
	~TreeKey00242F5E();
	unsigned int m_id;
	void *m_name;
};

struct Rva000A7941Node
{
	int m_color;
	Rva000A7941Node *m_parent;
	Rva000A7941Node *m_left;
	Rva000A7941Node *m_right;
	TreeKey00242F5E m_value;
};

class Rva000A7941
{
public:
	void rva000A7941(void *p);
};

void Rva000A7941::rva000A7941(void *p)
{
	Rva000A7941Node *cur = (Rva000A7941Node *)p;
	while (cur != 0) {
		rva000A7941(cur->m_right);
		Rva000A7941Node *left = cur->m_left;
		cur->m_value.~TreeKey00242F5E();
		free(cur);
		cur = left;
	}
}
