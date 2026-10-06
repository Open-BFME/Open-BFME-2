// ?Rva001117B4IsPow2@@YGEH@Z
// cl: /MD
//
// 0x001117B4 47B power-of-two test for 1..64. Retail keeps a single `mov al,1`
// true block at +9; the first test (cmp 0x40) falls into it and every later
// test branches back to it. ?Rva001117B4IsPow2@@YGEH@Z present-unmatched
unsigned char __stdcall Rva001117B4IsPow2(int v)
{
	unsigned char r;
	if (v == 0x40) {
		r = 1;
	} else if (v == 0x20) {
		r = 1;
	} else if (v == 0x10) {
		r = 1;
	} else if (v == 8) {
		r = 1;
	} else if (v == 4) {
		r = 1;
	} else if (v == 2) {
		r = 1;
	} else {
		r = (v == 1);
	}
	return r;
}
