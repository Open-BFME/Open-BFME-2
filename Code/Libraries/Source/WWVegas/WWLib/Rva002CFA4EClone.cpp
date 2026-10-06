// cl: /MD
// ?Rva002CFA4EClone@@YGPAURva002CFA4ENode@@PBU1@@Z @0x002CFA4E 30B.
// Node clone for the Rva002CF13B tree: clones the value at src+0x10 through
// the rowed stdcall 0x002CF86F, copies the color byte, zeroes links +8/+0xc,
// returns the node, ret 4. Same 30B shape as the rowed 0x002CFA30 clone.
// Callers at 0x002CFCFB 0x002CFD2B unblocks 0x002CFCEE.
struct Rva002CF13B
{
	unsigned char m_bytes[8];
};

void *__stdcall Rva002CF86FCreate(const Rva002CF13B *src);

struct Rva002CFA4ENode
{
	unsigned char m_color;
	unsigned char m_pad01[7];
	unsigned int m_link08;
	unsigned int m_link0C;
	Rva002CF13B m_value;
};

Rva002CFA4ENode *__stdcall Rva002CFA4EClone(const Rva002CFA4ENode *src)
{
	Rva002CFA4ENode *node = (Rva002CFA4ENode *)Rva002CF86FCreate(&src->m_value);
	node->m_color = src->m_color;
	node->m_link08 = 0;
	node->m_link0C = 0;
	return node;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva002CFA4E@Rva002CFCEE@@QAEPAURva002CFA4ENode@@PBU2@@Z=?Rva002CFA4EClone@@YGPAURva002CFA4ENode@@PBU1@@Z")
