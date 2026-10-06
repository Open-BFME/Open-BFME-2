// ?rva0042B068@Rva0042B068@@QAEHHHH@Z
// partial score=0.91 date=2026-10-06
// cl: /O2 /Oy-
// ?rva0042B068@Rva0042B068@@QAEHHHH@Z @0x0042B068 30B: int wrapper synthesising char.
// Target evidence: pushes [ebp+0x13] [ebp+0x10] [ebp+0xc] plus ecx/overwrite with
// [ebp+8] then tail-call to pinned ?run@Rva0042B068Host@@QAEHHHHPAD@Z 0x0042B038;
// caller 0x0042B0C7; ret 0xc; prev 0x004297BB next 0x0042C083.
class Rva0042B068Host
{
public:
	int run(int a, int b, int c, char *d);
};

class Rva0042B068 : public Rva0042B068Host
{
public:
	int rva0042B068(int a, int b, int c);
};

// ?rva0042B068@Rva0042B068@@QAEHHHH@Z present-unmatched
int Rva0042B068::rva0042B068(int a, int b, int c)
{
	int _a = a;
	int _b = b;
	char *p = (char *)&c + 3;
	return run(_a, _b, c, p);
}
