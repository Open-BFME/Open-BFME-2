// cl: /DNDEBUG /MD
//
// ?q4Notify002CCB04@@YAXPAXPAVMade002CCB04@@HH@Z @0x0050B42C (77B).
// EmotionWeaponNugget field parser: same two-add 77B shape as the OpenGate
// q4Notify002CCAA1 at 0x0050B23B (sibling, same page, same /O1), differing
// only by the second DIR32 table (0x00864CD0 here vs 0x00864C74 there) and the
// Made type. First add via the rowed ?Rva00507552Get@@YAHXZ plus index 0,
// second via DIR32 plus index 0, both through the rowed
// ?add@MultiIniFieldParse@@QAEXPBUFieldParse@@I@Z, then the pin-only
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z. Caller is
// ?parseEmotionWeaponNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCB49.

class Made002CCB04;

struct FieldParse;
extern const FieldParse EmotionFieldTable;

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

void q4Notify002CCB04(void *ini, Made002CCB04 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	tmp.add((FieldParse *)Rva00507552Get(), 0);
	tmp.add(&EmotionFieldTable, 0);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
