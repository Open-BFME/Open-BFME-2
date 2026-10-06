// cl: /DNDEBUG /MD
//
// ?q4Notify002CCB67@@YAXPAXPAVMade002CCB67@@HH@Z @0x0050B5F6 (53B).
// StealMoneyNugget field parser: same 53B MultiIni pattern as the DOTNugget
// q4Notify002CCA37 at 0x0050B13A (sibling in the same page, same /O1 shape),
// differing only by the buildFieldParse callee (rowed
// ?buildFieldParse@Rva0050B5CFBuildFieldParse@@SAXAAVMultiIniFieldParse@@@Z at
// 0x0050B5CF) and the Made type. Caller is
// ?parseStealMoneyNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCBAC
// (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp), news 0x12C.

class Made002CCB67;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();

	char m_pad[0x84];
};

class Rva0050B5CFBuildFieldParse
{
public:
	static void buildFieldParse(MultiIniFieldParse &m);
};

class INI
{
public:
	void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};

void q4Notify002CCB67(void *ini, Made002CCB67 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	Rva0050B5CFBuildFieldParse::buildFieldParse(tmp);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
