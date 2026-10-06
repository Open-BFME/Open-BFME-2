// cl: /DNDEBUG /MD
// ?Rva0059AFC2Copy@@YAPAURva0059AFC2Out@@PAU1@PAURva0059AFC2In@@PBD@Z @0x0059AFC2 57B
// unlock free function building 20B record from 12B src plus 8B Pair init by rowed 0x000B3F84
// Target evidence: callers 0x00510548 0x0059B554 0x0059B5F5 0x0059B6EC 0x005E37A9 in 0x005103A3 0x0059B4FF 0x0059B5A3 0x005E3753; callee rowed 0x000B3F84 init; neighbours 0x0059A85C 0x0059B060
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair *init(const char *s);
private:
	const char *m_ptr;
	int m_len;
};
struct Rva0059AFC2In
{
	int m_a;
	int m_b;
	int m_c;
};
struct Rva0059AFC2Out
{
	Rva0059AFC2In m_in;
	Rva000B3F84Pair m_pair;
};
Rva0059AFC2Out *__cdecl Rva0059AFC2Copy(Rva0059AFC2Out *dst, Rva0059AFC2In *src, const char *name)
{
	Rva000B3F84Pair p;
	p.init(name);
	Rva0059AFC2Out tmp;
	tmp.m_in = *src;
	tmp.m_pair = p;
	*dst = tmp;
	return dst;
}
