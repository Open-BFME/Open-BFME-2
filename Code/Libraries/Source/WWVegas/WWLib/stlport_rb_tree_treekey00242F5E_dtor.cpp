// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ??1Rva000A79CE@@QAE@XZ, retail 0x000A7BEE, 56 bytes.
// TreeKey00242F5E set destructor: calls rowed clear 0x000A79CE then frees the
// header node via rowed free 0x00030830. Same 56B EH shape as 0x001DDB8E and
// 0x00603AA8. Evidence: chain lane caller of clear; neighbours 0x000A7AA7 and
// 0x000A7C50 share the same tree flags. Base holds the header so the derived
// clear plus inlined base free reproduces the STL _Rb_tree_base EH pattern.
extern "C" void __cdecl free(void *p);

class Rva000A79CEBase
{
public:
	Rva000A79CEBase() {}
	~Rva000A79CEBase() {
		void *header = m_header;
		if (header != 0) {
			free(header);
		}
	}
protected:
	void *m_header;
};

class Rva000A79CE : public Rva000A79CEBase
{
public:
	void rva000A79CE();
	~Rva000A79CE();
private:
	unsigned int m_count;
};

Rva000A79CE::~Rva000A79CE()
{
	rva000A79CE();
}
