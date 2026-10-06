// cl: /O1 /MD /arch:SSE
//
// ?rva0039ADB9@Rva0039ADB9@@QAEMMH@Z @0x0039ADB9 51B: float min against an
// int lookup, range-17 dump lane.
//
// The Rva00288CFA global resolves an int through the pinned 0x00288CA6
// lookup (outer this plus int arg plus 0); the float arg wins when smaller,
// else the int as float. The computed float reuses the dead int-arg slot;
// /arch:SSE for the cvtsi2ss/movss/comiss shape.

class Rva00288CFA
{
public:
	int rva00288CA6(void *outer, int n, int zero);
};

extern Rva00288CFA *g_00DFECC4;

class Rva0039ADB9
{
public:
	float rva0039ADB9(float v, int n);
};

// ?rva0039ADB9@Rva0039ADB9@@QAEMMH@Z
float Rva0039ADB9::rva0039ADB9(float v, int n)
{
	int r = g_00DFECC4->rva00288CA6(this, n, 0);
	float f = (float)r;
	return *((v > f) ? &f : &v);
}
