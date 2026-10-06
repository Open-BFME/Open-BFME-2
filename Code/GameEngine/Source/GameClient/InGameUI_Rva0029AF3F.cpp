// cl: /DNDEBUG /MD /EHsc
//
// InGameUI slot 91: component-wise bounds merge over two int pairs. Slot
// evidence from the InGameUI vtable at 0x7BE810 (slots 88-89 are the landed
// selectMatching pair and slots 99-100 the landed max-setter pair, so the
// table is proven): slot 91 points at 0x0029AF3F. The body ignores `this`
// and merges through three pointer arguments with a shared max-store tail
// (the min stores in-branch, the max reloads and stores once). Leaf with
// no calls and no pins. Semantic name unproven so it rides an
// address-derived InGameUI-scoped name; opaque behavior.

class InGameUI
{
public:
	virtual void mergeRva0029AF3F(const int *a, const int *b, int *out);
};

// ?mergeRva0029AF3F@InGameUI@@UAEXPBH0PAH@Z
void InGameUI::mergeRva0029AF3F(const int *a, const int *b, int *out)
{
	int hi;
	if (a[0] < b[0]) {
		out[0] = a[0];
		hi = b[0];
	} else {
		out[0] = b[0];
		hi = a[0];
	}
	out[2] = hi;
	if (a[1] < b[1]) {
		out[1] = a[1];
		hi = b[1];
	} else {
		out[1] = b[1];
		hi = a[1];
	}
	out[3] = hi;
}
