// ?rva003591F4@Rva003591F4@@QAEXH_N@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva003591F4@Rva003591F4@@QAEXHH@Z @0x003591F4 33B.
// Void ID gate (thiscall, int plus int): slides this by 0x18 or 0xC on the
// flag, then routes (id, adjusted-this) through the rowed Rva00358DC2 erase
// unless the id already matches the slot. The odd push-ecx-plus-overwrite
// is how MSVC passes the register id around the slot load.
struct Rva00358DC2Node;

class Rva00358DC2
{
public:
	void rva00358DC2(Rva00358DC2Node *n);
};

class Rva003591F4
{
public:
	void rva003591F4(int id, bool flag);
};

void Rva003591F4::rva003591F4(int id, bool flag)
{
	char *p = (char *)this;
	if (flag != 0)
		p += 0x18;
	else
		p += 0xC;
	if (id != *(int *)p)
		((Rva00358DC2 *)p)->rva00358DC2((Rva00358DC2Node *)id);
}
