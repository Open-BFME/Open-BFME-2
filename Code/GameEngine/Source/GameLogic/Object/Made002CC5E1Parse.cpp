// cl: /DNDEBUG /MD
//
// ?q4Notify002CC5E1@@YAXPAXPAVMade002CC5E1@@HH@Z @0x005088F0 (53B).
// DamageNugget field parser: MultiIni tmp, buildFieldParse via rowed
// 0x005088CE, then INI initFromINIMulti via pin. Caller
// parseDamageNugget at 0x002CC626. Same tail as sibling q4Notify002CC64B
// 0x0050893A but with adds factored into buildFieldParse.
class Made002CC5E1;
class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	char m_pad[0x84];
};
class Rva005088CE
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};
class INI
{
public:
	void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};
void __cdecl q4Notify002CC5E1(void *ini, Made002CC5E1 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	Rva005088CE::buildFieldParse(tmp);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
