// cl: /DNDEBUG /MD
//
// ?rva002C9B80@Rva002C9B80Owner@@QAEMPAXM@Z @0x002C9B80 67B: unit-float array
// plus two-stage call. Retail fills a 6-float stack array with 1.0f via rep
// stosd (push 6 / pop ecx count), calls the pinned
// ?rva002C9A6F@Rva002C9B80Owner@@QAEXPAXHPAX@Z at 0x002C9A6F (REL32 read at
// 0x002C9BA2) with (arg1, 0, arr), then calls the pinned
// ?rva002C995D@BfmeRangedWeaponTemplate@@QAEMPAX0M@Z at 0x002C995D (REL32 read
// at 0x002C9BB8; Ghidra 103B range target) on the +0x04 member with
// (arg1, arr, arg2) and returns its float: retail leaves the callee's st0
// in place (no fstp), and callers store it (CanApproachToTarget 0x002FA2DC
// does fstp right after the call; WorldBuilder's twin likewise). The +0x04
// member is the same weapon-template view 0x002C99C4 calls 0x002C995D on.
// ebp frame with 0x18 locals; ret 8.
// Owner layout beyond +0x04 is unclaimed pad. Honest address-derived names.

class BfmeRangedWeaponTemplate
{
public:
	float rva002C995D(void *a, void *arr, float b);
};

class Rva002C9B80Owner
{
public:
	void rva002C9A6F(void *a, int b, void *arr);
	float rva002C9B80(void *a, float b);
private:
	void *m_pad00; // +0x00 unclaimed
	BfmeRangedWeaponTemplate *m_m04; // +0x04
};

// ?rva002C9B80@Rva002C9B80Owner@@QAEMPAXM@Z
float Rva002C9B80Owner::rva002C9B80(void *a, float b)
{
	float arr[6];
	for (int i = 0; i < 6; ++i)
		arr[i] = 1.0f;
	rva002C9A6F(a, 0, arr);
	return m_m04->rva002C995D(a, arr, b);
}
