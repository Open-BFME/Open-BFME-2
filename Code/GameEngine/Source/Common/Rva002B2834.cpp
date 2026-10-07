// cl: /O1 /MD
// ?rva002B2834@Rva002B280C@@QAEXPAUArg54@@PAX@Z @0x002B2834 36B.
// Guarded chain (thiscall, ret 8): bail when the Arg54 pointer is null or
// the rowed 0x002B280C check on this fails it, else run pinned 0x00319831
// on the Arg54 pointer with the second arg. The 0x2B280C call forwards the
// ambient this with no mov ecx of its own, which is ordinary thiscall
// behavior (cf. the 0x2B2CE7 family where the plain ret forces the issue;
// here ret 8 agrees).
//
// Target evidence (game.dat, read-only, capstone): frameless, null check,
// bare push+call into 0x2B280C, al gate, push-second plus mov ecx from the
// first param into 0x319831, ret 8. Arg54 view follows the rowed 2B280C TU.
// Identity unproven: honest address-derived names.
struct Arg54
{
	void rva00319831(void *extra);
};

class Rva002B280C
{
public:
	bool rva002B280C(Arg54 *arg);
	void rva002B2834(Arg54 *arg, void *extra);
};

void Rva002B280C::rva002B2834(Arg54 *arg, void *extra)
{
	if (arg == 0)
		return;
	if (!rva002B280C(arg))
		return;
	arg->rva00319831(extra);
}
