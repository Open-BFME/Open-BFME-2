// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
class BfmeSubDDB
{
public:
	int bfmeTailDDB();
	unsigned char m_bfmeHead[0x39];
	bool m_affect;
};

class BfmeThingDDB
{
public:
	int bfmeGoDDB();
	unsigned char m_bfmeHead[0x64];
	BfmeSubDDB *m_bfmeSub;
};

int BfmeThingDDB::bfmeGoDDB()
{
	BfmeSubDDB *s = m_bfmeSub;
	if (s != 0 && s->m_affect)
		return s->bfmeTailDDB();
	return 0;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x00271898 -> ?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ
#pragma comment(linker, "/alternatename:?bfmeTailDDB@BfmeSubDDB@@QAEHXZ=?rva00271898@Rva00271826@@QAEPBURva00271898Color@@XZ")
