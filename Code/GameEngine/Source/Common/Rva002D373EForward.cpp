// cl: /O1 /DNDEBUG /MD
//
// ?rva002D373E@Rva002D37Owner@@QAEXH@Z @0x002D373E 24B: guarded sub-object
// tailcall (thiscall, int arg, void). Retail returns when the arg is null,
// else tail-jumps with the +0x10 member plus 0xC0 as receiver into the pinned
// callee at 0x00525A80. Honest address-derived name. Sibling 0x002D3726
// already on master under a real name; this file carries only the free twin.

struct Rva002D37Sub
{
	// ?rva00525A80@Rva002D37Sub@@QAEXH@Z: thiscall void (int); retail REL32.
	void rva00525A80(int x);
};

class Rva002D37Owner
{
public:
	void rva002D373E(int x);
private:
	char m_pad00[0x10]; // +0x00..+0x10 unclaimed
	void *m_p10; // +0x10
};

// ?rva002D373E@Rva002D37Owner@@QAEXH@Z
void Rva002D37Owner::rva002D373E(int x)
{
	if (x == 0)
		return;
	return ((Rva002D37Sub *)((char *)m_p10 + 0xC0))->rva00525A80(x);
}
