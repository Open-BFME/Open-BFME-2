// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?setShader@Rva00075655@@SAHHH@Z @0x00075655 64B.
// Static shader-cache check: when both args match the cached pair return 1,
// otherwise refresh the cache, fetch the slot object from the table at
// 0x009E1F24, return 0 for an empty slot, else return its slot-0 virtual
// called with the second arg. Called from W3DShroudMaterialPass install.

extern int g_00DE1F54;
extern int g_00DE1F18;

struct ShaderSlotObj
{
	virtual int slot00(int b);
};

extern ShaderSlotObj * volatile g_00DE1F24[];

class Rva00075655
{
public:
	static int setShader(int a, int b);
};

int Rva00075655::setShader(int a, int b)
{
	if (a == g_00DE1F54 && b == g_00DE1F18)
		return 1;
	g_00DE1F54 = a;
	g_00DE1F18 = b;
	if (g_00DE1F24[a] != 0)
		return g_00DE1F24[a]->slot00(b);
	return 0;
}
