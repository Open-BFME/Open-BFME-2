// cl: /DNDEBUG /MD

class Rva008A48D0Item
{
public:
	virtual void unused0();
	virtual void release();
};

// BFME 2: Open-BFME-1's body (submodule 10af19f44a, BFME 1 0x008A48D0),
// byte-identical in game.dat at 0x006F1380. bfme1_sweep lists it as ambiguous
// with its twin Rva008B2BD0ReleaseGlobals (rowed at 0x006E8F40): the two
// differ only in the six globals they release. 0x006E8F40 reads the twin's
// (VA 0xe18174..0xe18188), so this is the copy that reads VA 0xe18204..0xe18218.
// They are defined here (zero-filled .bss); no other unit references them.
Rva008A48D0Item *g_rva008A48D0_0;	// VA 0x00e18204
Rva008A48D0Item *g_rva008A48D0_1;	// VA 0x00e18208
Rva008A48D0Item *g_rva008A48D0_2;	// VA 0x00e1820c
Rva008A48D0Item *g_rva008A48D0_3;	// VA 0x00e18210
Rva008A48D0Item *g_rva008A48D0_4;	// VA 0x00e18214
Rva008A48D0Item *g_rva008A48D0_5;	// VA 0x00e18218

void rva008A48D0ReleaseGlobals()
{
	Rva008A48D0Item *z = 0;
	if (g_rva008A48D0_0 != z)
	{
		g_rva008A48D0_0->release();
		g_rva008A48D0_0 = z;
	}
	if (g_rva008A48D0_1 != z)
	{
		g_rva008A48D0_1->release();
		g_rva008A48D0_1 = z;
	}
	if (g_rva008A48D0_2 != z)
	{
		g_rva008A48D0_2->release();
		g_rva008A48D0_2 = z;
	}
	if (g_rva008A48D0_3 != z)
	{
		g_rva008A48D0_3->release();
		g_rva008A48D0_3 = z;
	}
	if (g_rva008A48D0_4 != z)
	{
		g_rva008A48D0_4->release();
		g_rva008A48D0_4 = z;
	}
	if (g_rva008A48D0_5 != z)
	{
		g_rva008A48D0_5->release();
		g_rva008A48D0_5 = z;
	}
}
