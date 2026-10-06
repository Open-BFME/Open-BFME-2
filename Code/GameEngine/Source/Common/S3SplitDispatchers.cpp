// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S3SplitDispatchers.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only this one placed
// body is defined here; the donor's Gen_00360880 stays out, so the
// unmatched-definition gate passes.
//
// 0x004655B0 reads a function pointer at +0x1EC and, when it is set, calls it
// with this and both arguments through a cdecl frame the caller cleans -- the
// same shape as 0x00477D30 one argument wider. A null pointer is the only way
// it answers false. It returns int: mov eax,1 and xor eax,eax, not the
// two-byte al forms.

class Gen_004655b0;

typedef void (__cdecl *BfmeTwoArgHandler)(Gen_004655b0 *owner, void *first, void *second);

class Gen_004655b0
{
public:
	int bfmeDispatch(void *first, void *second);

private:
	char m_bfmeHead[0x1EC];
	BfmeTwoArgHandler m_bfmeHandler;				// +0x1EC
};

// ?bfmeDispatch@Gen_004655b0@@QAEHPAX0@Z 0x0008FF56
int Gen_004655b0::bfmeDispatch(void *first, void *second)
{
	if (m_bfmeHandler)
	{
		m_bfmeHandler(this, first, second);

		return 1;
	}

	return 0;
}
