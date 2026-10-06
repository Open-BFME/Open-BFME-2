// cl: /MD
// ?Rva002CFA30Clone@@YGPAURva002CFA30Node@@PBU1@@Z @0x002CFA30 30B.
// Node clone for the anonymous Rva002CF120-node tree: clones the value at
// src+0x10 through the rowed stdcall 0x002CF84D, copies the color byte,
// zeroes links +8/+0xc, returns the node, ret 4. Same 30B shape as the NoCase
// _M_clone_node 0x002CFE27; the tree template identity is unproven so the
// node is an honest Rva struct (cf. Rva005E7198 precedent). The 16-byte
// header is redeclared locally (same size as BfmeObject872Header) to avoid
// pulling STL headers into this TU. Callers at 0x002CFC88 0x002CFCB8.
struct BfmeObject872Header
{
	unsigned char m_bytes[16];
};

struct Rva002CF120
{
	BfmeObject872Header m_header;
	int m_field10;
};

void *__stdcall Rva002CF84DCreate(const Rva002CF120 *src);

struct Rva002CFA30Node
{
	unsigned char m_color;
	unsigned char m_pad01[7];
	unsigned int m_link08;
	unsigned int m_link0C;
	Rva002CF120 m_value;
};

Rva002CFA30Node *__stdcall Rva002CFA30Clone(const Rva002CFA30Node *src)
{
	Rva002CFA30Node *node = (Rva002CFA30Node *)Rva002CF84DCreate(&src->m_value);
	node->m_color = src->m_color;
	node->m_link08 = 0;
	node->m_link0C = 0;
	return node;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva002CFA30@Rva002CFC7B@@QAEPAURva002CFA30Node@@PBU2@@Z=?Rva002CFA30Clone@@YGPAURva002CFA30Node@@PBU1@@Z")
