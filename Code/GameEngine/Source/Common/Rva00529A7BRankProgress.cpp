// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00529A7B@Rva00529A7B@@QAEXM@Z 185B @0x00529A7B
// Rank progress Apt updater: Show/HideRankProgress around a clamped
// SetRankProgressBar from arg*scale. Evidence: strings ShowRankProgress
// SetRankProgressBar HideRankProgress; float at +0x14 and void* at +0;
// callee rows 0x00222A8B 0x002D4531 and pin-free; globals TheRva00222A8BTarget
// g_00BCF9B0 as -100.0f literal (retail -1e+02f per Rva002E0C2BMethod; literal loads v first);
// caller at 0x00529D8A unclaimed so owner address-derived.
class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &arg);

class Rva00529A7B
{
public:
	void rva00529A7B(float v);
private:
	void *m00; // +0x00 passed as level to invoke
	unsigned char m04_pad[0x10]; // +0x04
	float m14; // +0x14
};

void Rva00529A7B::rva00529A7B(float v)
{
	bool this_ge0 = m14 >= 0.0f;
	bool arg_ge0 = v >= 0.0f;
	if (arg_ge0)
	{
		if (!this_ge0)
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m00, "ShowRankProgress", 0, 0, 0, 0, 0, 0);
		int iv = 1 - (int)(v * -100.0f);
		if (iv < 1)
			iv = 1;
		else if (iv > 100)
			iv = 100;
		Rva002D4531Invoke((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m00, "SetRankProgressBar", iv);
	}
	else
	{
		if (this_ge0)
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m00, "HideRankProgress", 0, 0, 0, 0, 0, 0);
	}
	m14 = v;
}
