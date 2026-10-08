// cl: /Od
int bfmeMakeOX(void *text);
// Native 28C10..28C3B and 28C40..28C6A call the same thiscall search owner.
// Native +0/+4 range fields supply the needle and its length; the other word
// is an unsigned position. RET8 and the integer result agree with the owned
// 276B0 body. Names remain address-derived: no basic_string identity is claimed.
// BFME1 ba7ddda7 BfmeTwoHundredSixtySix is the range-wrapper semantic lead.
// bfmeMakeOX is the existing binding to the STLport length owner at 6F30.
// Calling that binding avoids emitting an /Od copy of the library function.

struct BfmeRangePF
{
 char *m_bfmeAt;  // +0
 char *m_bfmeEnd; // +4
};

class BfmeThingPF
{
public:
 char *m_begin; // +0
 char *m_end;   // +4
 int rva000276B0(const char *, unsigned, unsigned);
 int rva00028C10(const BfmeRangePF *, unsigned);
 int rva00028C40(char *, unsigned);
};

int BfmeThingPF::rva00028C10(const BfmeRangePF *span, unsigned pos)
{
 return rva000276B0(span->m_bfmeAt, pos, span->m_bfmeEnd - span->m_bfmeAt);
}

int BfmeThingPF::rva00028C40(char *s, unsigned pos)
{
 return rva000276B0(s, pos, bfmeMakeOX(s));
}
