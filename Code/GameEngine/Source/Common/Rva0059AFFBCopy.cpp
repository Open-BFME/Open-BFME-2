// cl: /DNDEBUG /MD
// ?Rva0059AFFBCopy@@YAPAURva0059AFFBOut@@PAU1@PAURva0059AFFBIn@@PBD@Z @0x0059AFFB 59B
// unlock free function building 28B record from 20B src plus 8B Pair init by rowed 0x000B3F84
// Target evidence: caller 0x0059B561 in 0x0059B4FF; callee rowed 0x000B3F84 init; neighbours 0x0059AFC2 0x0059B060; sibling 0x0059AFC2 same flags
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair *init(const char *s);
private:
	const char *m_ptr;
	int m_len;
};
struct Rva0059AFFBIn
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
};
struct Rva0059AFFBOut
{
	Rva0059AFFBIn m_in;
	Rva000B3F84Pair m_pair;
};
Rva0059AFFBOut *__cdecl Rva0059AFFBCopy(Rva0059AFFBOut *dst, Rva0059AFFBIn *src, const char *name)
{
	Rva000B3F84Pair p;
	p.init(name);
	Rva0059AFFBOut tmp;
	tmp.m_in = *src;
	tmp.m_pair = p;
	*dst = tmp;
	return dst;
}
