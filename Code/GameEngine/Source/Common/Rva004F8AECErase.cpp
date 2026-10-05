// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004F8AEC@Rva004F8AEC@@QAEXPAURva004F8AECNode@@@Z retail 0x004F8AEC 53B
// Rb _M_erase: recurse-right via +12 walk-left via +8 destroy value at +16 via pinned Rva004F7DD4 dtor 0x004F7DD4 and free 0x30830 ret 4.
// Evidence: callees 0x004F7DD4 pin plus 0x30830 rowed; caller clear 0x004F8DD4 pushes root at +4 and resets header; same 53B shape as landed erases 0x003833BB and 0x00502610.
extern "C" void __cdecl free(void *block);

struct Rva004F7DD4
{
	~Rva004F7DD4();
};

struct Rva004F8AECNode
{
	unsigned int m_color;
	Rva004F8AECNode *m_parent;
	Rva004F8AECNode *m_left;
	Rva004F8AECNode *m_right;
};

class Rva004F8AEC
{
public:
	void rva004F8AEC(Rva004F8AECNode *node);
};

void Rva004F8AEC::rva004F8AEC(Rva004F8AECNode *node)
{
	while (node)
	{
		rva004F8AEC(node->m_right);
		Rva004F8AECNode *left = node->m_left;
		((Rva004F7DD4 *)(node + 1))->~Rva004F7DD4();
		free(node);
		node = left;
	}
}
