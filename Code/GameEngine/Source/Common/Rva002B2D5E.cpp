// cl: /O1 /MD
// ?rva002B2D5E@@YA_NPAX0@Z @0x002B2D5E 52B.
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_00DFEF10;

class Rva0030F4EA
{
public:
	static void *__stdcall rva0030F4EA(void *p);
};

class Rva002B2579Host
{
public:
	void *rva002B2579(void *p);
};

class Rva004E0625
{
public:
	void *rva004E0625();
};

bool __cdecl rva002B2D5E(void *o, void *p)
{
	void *t = Rva0030F4EA::rva0030F4EA(p);
	void *u = ((Rva002B2579Host *)g_00DFEF10)->rva002B2579(*(void **)t);
	if (u == 0)
		return false;
	void *r = ((Rva004E0625 *)u)->rva004E0625();
	*(void **)o = r;
	return r != 0;
}
