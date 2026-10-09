// cl: /MD
// ?rva00527AEB@Rva00527AEB@@QAEXABUTreeHintRef00217D4C@@@Z, retail 0x00527AEB, 24 bytes.
// Chain from 0x005278DD: call Hide-reset then assign TreeHint at +0x1c. Evidence: packet disassembly, caller context, callees rowed.
class InGameHelpBoxMovieClip
{
public:
	void rva005278DD();
};

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &that);
};

class Rva00527AEB
{
public:
	void rva00527AEB(const TreeHintRef00217D4C &v);
};

void Rva00527AEB::rva00527AEB(const TreeHintRef00217D4C &v)
{
	((InGameHelpBoxMovieClip *)this)->rva005278DD();
	*(TreeHintRef00217D4C *)((char *)this + 0x1C) = v;
}
