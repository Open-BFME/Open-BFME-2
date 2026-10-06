// cl: /DNDEBUG /MD
//
// ?q4Notify002CC971@@YAXPAXPAVMade002CC971@@HH@Z @0x0050AAEA (77B).
// SlaveAttackNugget field parser: same two-add 77B shape as Grab sibling.
// First add via rowed ?Rva00507552Get@@YAHXZ plus index 0, second via DIR32
// 0x0086BB18 plus index 0, both through rowed add, then pin-only initFromINIMulti.
// Caller parseSlaveAttackNugget at 0x002CC9B6.

class Made002CC971;

struct FieldParse;
extern const FieldParse SlaveAttackFieldTable;

int Rva00507552Get();

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *p, unsigned int u);

	char m_pad[0x84];
};

class INI
{
public:
	void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};

void q4Notify002CC971(void *ini, Made002CC971 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	tmp.add((FieldParse *)Rva00507552Get(), 0);
	tmp.add(&SlaveAttackFieldTable, 0);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
