// cl: /DNDEBUG /MD
//
// ?q4Notify002CC907@@YAXPAXPAVMade002CC907@@HH@Z @0x0050A7E5 (77B).
// GrabNugget field parser: same two-add 77B shape as EmotionWeapon sibling.
// First add via rowed ?Rva00507552Get@@YAHXZ plus index 0, second via DIR32
// 0x00864A30 plus index 0, both through rowed add, then pin-only initFromINIMulti.
// Caller parseGrabNugget at 0x002CC94C.

class Made002CC907;

struct FieldParse;
extern const FieldParse GrabFieldTable;

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

void q4Notify002CC907(void *ini, Made002CC907 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	tmp.add((FieldParse *)Rva00507552Get(), 0);
	tmp.add(&GrabFieldTable, 0);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
