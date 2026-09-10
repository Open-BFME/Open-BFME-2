// cl: /Od
//
// bfmeFindQH, retail 0x000245A0, 34 bytes.
// Kept out of BfmeTwoHundredNinetyTwo.cpp so bfmeSwapQH cannot see
// this body (matching.md callee-visibility trap). /Od matches the
// retail ebp frame. Walks a pointer chain until *at == how.

int *bfmeFindQH(int *at, int how)
{
	while (at != 0 && *at != how)
		at = (int *)*at;
	return at;
}
