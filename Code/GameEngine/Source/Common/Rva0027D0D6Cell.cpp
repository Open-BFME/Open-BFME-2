// cl: /MD
// ?rva0027D0D6@Rva0027D0D6@@QAEHPAM@Z, retail 0x0027D0D6 206B. Unlock: clamp xy to bounds from vtable slot10 then grid index via floor.
// Evidence: callees rowed floor and slot10 virtual; caller 0x00283642 unclaimed; honest address name.
extern "C" __declspec(dllimport) double __cdecl floor(double);

class Rva0027D0D6
{
public:
	virtual void _v0();
	virtual void _v1();
	virtual void _v2();
	virtual void _v3();
	virtual void _v4();
	virtual void _v5();
	virtual void _v6();
	virtual void _v7();
	virtual void _v8();
	virtual void _v9();
	virtual void fetchBounds(void *out);
	int rva0027D0D6(float *src);
};

struct Bounds
{
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
};

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline long fast_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

int Rva0027D0D6::rva0027D0D6(float *src)
{
	float x = src[0];
	float y = src[1];
	Bounds b;
	fetchBounds(&b);
	if (b.minX > x)
		x = b.minX;
	if (b.minY > y)
		y = b.minY;
	if (x > b.maxX)
		x = b.maxX;
	if (y > b.maxY)
		y = b.maxY;
	x = fast_floor((x - b.minX) / (b.maxX - b.minX) * 49.9f);
	int ix = fast_round(x);
	float fy = fast_floor((y - b.minY) / (b.maxY - b.minY) * 49.9f);
	int iy = fast_round(fy);
	return iy * 50 + ix;
}
