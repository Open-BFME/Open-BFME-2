// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: x87 float-forwarding twins at 0x1E7C2B/0x1E9045 (33B
// each). Each forwards (a,b,c,d) with this to its callee (0x1E7053 /
// 0x1E8C1B). Only c/d travel via fld/fstp into two push-ecx temps; a/b are
// dword-pushed directly, so the first two params are int-sized and the last
// two are float. Address-derived names; callee types unproven (pins).

class Rva001E7053
{
public:
	void rva001E7053(int a, int b, float c, float d);
};
class Rva001E8C1B
{
public:
	void rva001E8C1B(int a, int b, float c, float d);
};
class Rva001E7C2B
{
public:
	void rva001E7C2B(int a, int b, float c, float d);
};
class Rva001E9045
{
public:
	void rva001E9045(int a, int b, float c, float d);
};

// ?rva001E7C2B@Rva001E7C2B@@QAEXHHMM@Z
void Rva001E7C2B::rva001E7C2B(int a, int b, float c, float d)
{
	((Rva001E7053 *)this)->rva001E7053(a, b, c, d);
}

// ?rva001E9045@Rva001E9045@@QAEXHHMM@Z
void Rva001E9045::rva001E9045(int a, int b, float c, float d)
{
	((Rva001E8C1B *)this)->rva001E8C1B(a, b, c, d);
}
