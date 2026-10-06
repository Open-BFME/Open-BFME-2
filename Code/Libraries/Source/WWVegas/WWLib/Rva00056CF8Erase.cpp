// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva00056CF8@Rva00056CF8@@QAEXPAUHashNode00056CF8@@@Z, retail 0x00056CF8 (53B).
// Honest-address twin of the rowed ?_M_erase at 0x00056CC3 (identical bytes
// through div-free tail; only the self-call reloc differs). Rb-tree node with
// AsciiString value at +0x10: recurse right+0x0C, destroy value via rowed
// AsciiString dtor at 0x0048BA39, free via rowed _free, loop left+0x08.
// Caller at 0x00057B82 clears the same way; owner unproven.

// Retail calls the rowed AsciiString dtor at 0x0048BA39 from this erase
// body. Keep its one-pointer layout but leave the dtor out of line here so
// this TU binds to that row instead of emitting the header's inline copy.
// class-gate: allow AsciiString TU-local 4-byte view binds the proven rowed destructor at 0x0048BA39.
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_text;
};

extern "C" void __cdecl free(void *block);

struct HashNode00056CF8
{
	void *m_pad00;
	void *m_pad04;
	HashNode00056CF8 *m_left;
	HashNode00056CF8 *m_right;
	AsciiString m_value;
};

class Rva00056CF8
{
public:
	void rva00056CF8(HashNode00056CF8 *node);
};

void Rva00056CF8::rva00056CF8(HashNode00056CF8 *node)
{
	while (node != 0) {
		rva00056CF8(node->m_right);
		HashNode00056CF8 *left = node->m_left;
		node->m_value.~AsciiString();
		free(node);
		node = left;
	}
}
