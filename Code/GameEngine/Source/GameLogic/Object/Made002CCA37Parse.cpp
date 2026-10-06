// cl: /DNDEBUG /MD
//
// ?q4Notify002CCA37@@YAXPAXPAVMade002CCA37@@HH@Z @0x0050B13A (53B).
// DOTNugget field parser: builds a 0x84-byte MultiIniFieldParse on the stack
// through the rowed ??0MultiIniFieldParse@@QAE@XZ, runs the rowed static
// ?buildFieldParse@Rva0050B107@@SAXAAVMultiIniFieldParse@@@Z, then
// forwards the Made (as void*) plus the table through the pin-only
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z. Caller is
// ?parseDOTNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCA7C
// (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp), which
// declares this q4Notify (c/d unused, matching retail ignoring [ebp+16]/+20).
// Sibling of the FireLogic q4Notify pattern; pop-ecx cleanup for the static
// call is the /O1 size idiom.

class Made002CCA37;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();

	char m_pad[0x84];
};

class Rva0050B107
{
public:
	static void buildFieldParse(MultiIniFieldParse &m);
};

class INI
{
public:
	void initFromINIMulti(void *p, const MultiIniFieldParse &m);
};

void q4Notify002CCA37(void *ini, Made002CCA37 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	Rva0050B107::buildFieldParse(tmp);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
