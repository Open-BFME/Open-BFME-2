// Target bytes at 0x004DD890 (22B), called directly by 0x004DD8A6. It ignores
// null; otherwise it passes the node to the rowed pool method using the
// address-derived global at VA 0x00E049D8 (RVA 0x00A049D8). The pool and
// freed-node identities remain opaque.
extern unsigned int g_Va00E049D8;

class Rva00065964ObjectPool
{
public:
	void FreeObject(void *object);
};

void __cdecl rva004DD890(void *node)
{
	if (node != 0)
		((Rva00065964ObjectPool *)&g_Va00E049D8)->FreeObject(node);
}
