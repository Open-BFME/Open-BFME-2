// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030B31ASwap@@YAXPAURegion2D@@0@Z, retail 0x0030B31A, 41 bytes.
// Swap two 16-byte Region2D via temp copy ctor rowed 0x0004254E plus movsd.
// Evidence: callers at 0x0030B785 with Region2D at +0x0C and 0x005386CD swapping +0x0C then float+byte; prev no-flags next vector /O1 /EHsc.

struct Region2D
{
	Region2D(const Region2D &that);
	~Region2D() {}
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

void __cdecl Rva0030B31ASwap(Region2D *a, Region2D *b)
{
	Region2D tmp(*a);
	*a = *b;
	*b = tmp;
}
