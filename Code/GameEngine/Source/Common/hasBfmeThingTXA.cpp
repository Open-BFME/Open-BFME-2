// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BfmeThingTXA presence test: twelve-byte frameless predicate with one shape:
//
//     xor eax,eax / cmp [slot],eax / setne al / ret
//
// The DEC3DC object slot (proven to hold the global BfmeThingTXA by the
// creator at 0x1185F4) is tested for null. The xor-first order is the /O1
// form (defaults hoist a register load first); per the flag-split law this
// body lives in its own TU so the defaults-built flag helpers are untouched.
// No other flags (appended to the base -O2).
// The slot is ww3d.cpp's private ?Movie@WW3D@@0PAVFrameGrabClass@@A, read
// through a TU-scoped friend view (real decoration, no alias).
class FrameGrabClass;
class WW3D
{
	friend int hasBfmeThingTXA(void);
	static FrameGrabClass *Movie;
};

int hasBfmeThingTXA(void)
{
	return WW3D::Movie != 0;
}
