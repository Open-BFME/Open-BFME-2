// cl: /O1 /EHs /MD
//
// ??1Rva00500804@@QAE@XZ @0x00500E05 56B: STLport _Rb_tree destructor shape for
// the tree whose rowed subtree erase is 0x00500804 and clear is 0x00500ACF:
// clear() then the header base frees the header node (null-checked free) under
// one EH state. Caller 0x005016C3 destroys it at +0x4C. Names are
// address-derived; the element type is not recovered.
//
// ??1Rva005011BC@@QAE@XZ @0x005011BC 5B: holder whose offset-0 member is that
// tree; its empty destructor tail-jumps to the member destructor. No REL32
// caller found.
// ??1Rva00500804Header@@QAE@XZ present-unmatched (inline base dtor emitted for EH unwind)

extern "C" void __cdecl free(void *block);

struct Rva00500804Header
{
	void *m_header;
	~Rva00500804Header()
	{
		if (m_header)
			free(m_header);
	}
};

class Rva00500804 : public Rva00500804Header
{
public:
	void rva00500ACF();
	~Rva00500804();

private:
	int m_count;
};

Rva00500804::~Rva00500804()
{
	rva00500ACF();
}

class Rva005011BC
{
public:
	~Rva005011BC();

private:
	Rva00500804 m_tree;
};

Rva005011BC::~Rva005011BC()
{
}
