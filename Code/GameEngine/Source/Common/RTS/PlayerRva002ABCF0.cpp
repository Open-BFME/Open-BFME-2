// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002ABCF0@Player@@QAEHEPAH@Z, RVA 0x002ABCF0, size 45: Player iterate with byte flag and int result via iterateObjects.
// Evidence: ecx pass-through to Player::iterateObjects pinned at 0x002AB08B; callback at 0x002AB01C (FUN_006ab01c) with 8B userdata {flag result}; caller 0x003BCEA7 passes flag and out pointer with Player in ecx and uses return; neighbours PlayerRva002ABD1D.cpp.

class Object;
typedef void (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	void iterateObjects(ObjectIterateFunc func, void *userData) const;
	int rva002ABCF0(unsigned char flag, int *out);
};

void __cdecl Rva002AB01C(Object *obj, void *userData);

struct Rva002ABCF0Context
{
	unsigned char m_flag;
	int m_result;
};

int Player::rva002ABCF0(unsigned char flag, int *out)
{
	Rva002ABCF0Context ctx;
	ctx.m_result = 0;
	ctx.m_flag = flag;
	iterateObjects(Rva002AB01C, &ctx);
	if (out)
		*out = ctx.m_result;
	return ctx.m_result;
}
