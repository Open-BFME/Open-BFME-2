// cl: /DNDEBUG /MD

class Rva008B2BD0Item
{
public:
	virtual void unused0();
	virtual void release();
};

extern Rva008B2BD0Item *g_rva008B2BD0_0;
// g_rva008B2BD0_0: matched references place it at VA 0xe18174 (zero-filled .bss).
Rva008B2BD0Item * g_rva008B2BD0_0;
extern Rva008B2BD0Item *g_rva008B2BD0_1;
// g_rva008B2BD0_1: matched references place it at VA 0xe18178 (zero-filled .bss).
Rva008B2BD0Item * g_rva008B2BD0_1;
extern Rva008B2BD0Item *g_rva008B2BD0_2;
// g_rva008B2BD0_2: matched references place it at VA 0xe1817c (zero-filled .bss).
Rva008B2BD0Item * g_rva008B2BD0_2;
extern Rva008B2BD0Item *g_rva008B2BD0_3;
// g_rva008B2BD0_3: matched references place it at VA 0xe18180 (zero-filled .bss).
Rva008B2BD0Item * g_rva008B2BD0_3;
extern Rva008B2BD0Item *g_rva008B2BD0_4;
// g_rva008B2BD0_4: matched references place it at VA 0xe18184 (zero-filled .bss).
Rva008B2BD0Item * g_rva008B2BD0_4;
extern Rva008B2BD0Item *g_rva008B2BD0_5;
// g_rva008B2BD0_5: matched references place it at VA 0xe18188 (zero-filled .bss).
Rva008B2BD0Item * g_rva008B2BD0_5;

void rva008B2BD0ReleaseGlobals()
{
	Rva008B2BD0Item *z = 0;
	if (g_rva008B2BD0_0 != z)
	{
		g_rva008B2BD0_0->release();
		g_rva008B2BD0_0 = z;
	}
	if (g_rva008B2BD0_1 != z)
	{
		g_rva008B2BD0_1->release();
		g_rva008B2BD0_1 = z;
	}
	if (g_rva008B2BD0_2 != z)
	{
		g_rva008B2BD0_2->release();
		g_rva008B2BD0_2 = z;
	}
	if (g_rva008B2BD0_3 != z)
	{
		g_rva008B2BD0_3->release();
		g_rva008B2BD0_3 = z;
	}
	if (g_rva008B2BD0_4 != z)
	{
		g_rva008B2BD0_4->release();
		g_rva008B2BD0_4 = z;
	}
	if (g_rva008B2BD0_5 != z)
	{
		g_rva008B2BD0_5->release();
		g_rva008B2BD0_5 = z;
	}
}
