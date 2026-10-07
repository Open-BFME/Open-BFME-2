// cl: /O1 /arch:SSE /MD
// ?rva002B2334@Rva002B2334@@QAEXMMH@Z @0x002B2334 41B.
// Float-pair bit store (ret 0xC): the two float params go through union
// temporaries so their bit patterns land in the int slots +0x1C/+0x20;
// the third int param is unused. The union temps are what force the two
// push-ecx slots plus the movss/int-reload pairs (cf. direct bitcast
// which folds to 17B).
//
// Target evidence (game.dat, read-only, capstone): ebp frame, two push-ecx
// temps, movss load/store pairs, int reload for the member stores, leave,
// ret 0xC. Identity unproven: honest address-derived names.
class Rva002B2334
{
public:
	void rva002B2334(float a, float b, int c);

private:
	unsigned char m_pad00[0x1C];
	int m_1C;
	int m_20;
};

void Rva002B2334::rva002B2334(float a, float b, int c)
{
	(void)c;
	float t[2];
	int *bits = (int *)t;
	t[0] = a;
	int x0 = bits[0];
	t[1] = b;
	m_1C = x0;
	m_20 = bits[1];
}
