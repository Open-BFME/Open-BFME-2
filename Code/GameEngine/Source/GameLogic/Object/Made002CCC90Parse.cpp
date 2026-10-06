// cl: /DNDEBUG /MD
//
// ?q4Notify002CCC90@@YAXPAXPAVMade002CCC90@@HH@Z @0x0050BBEB (58B).
// LuaEventNugget field parser: same MultiIni init tail as the DOT/StealMoney
// q4Notify pair (53B at 0x0050B13A/0x0050B5F6) but builds its one-entry table
// via MultiIniFieldParse::add (rowed 0x0002BC6E) with the FieldParse at
// 0x00864F18 (DIR32) and index 0, instead of the shared buildFieldParse static.
// Caller is ?parseLuaEventNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at
// 0x002CCCD5 (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp),
// news 0x134. The four relocs (ctor/add/init/EH none) are gate-filled.

class Made002CCC90;

struct FieldParse;
extern const FieldParse LuaEventFieldTable;

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

void q4Notify002CCC90(void *ini, Made002CCC90 *m, int c, int d)
{
	MultiIniFieldParse tmp;
	tmp.add(&LuaEventFieldTable, 0);
	((INI *)ini)->initFromINIMulti(m, tmp);
}
