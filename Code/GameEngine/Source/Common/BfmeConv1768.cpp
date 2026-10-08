// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
class BfmeBaseCH
{
public:
	~BfmeBaseCH();

	unsigned char m_bfmeHeadCH[0xc];
};

class BfmeMemCH
{
public:
	~BfmeMemCH();

	unsigned char m_bfmeHeadCH[0x10];
};

class BfmeTmpACH : public BfmeBaseCH
{
public:
	BfmeTmpACH(void *value) throw();
	~BfmeTmpACH() {}

	void bfmeUseCH(void *owner) throw();

	BfmeMemCH m_bfmeMemCH;
};

// TeamsInfoRec::operator=, retail 0x0032DDB3 (target): copy-and-swap. The
// temporary is copy-constructed from the source (0x0032D9A4), swapped into
// this through TeamsInfoRec::swap 0x0032B651 and destroyed (0x0032C632). Its
// only caller is SidesList::operator= 0x0032E978, once for each of the two
// TeamsInfoRec members at +0xF44 and +0xF60, as WorldBuilder's twin (wb
// 0xa81000) is called from that operator's twin. The BfmeTmpACH spelling of
// the temporary is the donor's.
class TeamsInfoRec
{
public:
	TeamsInfoRec &operator=(const TeamsInfoRec &that);
};

TeamsInfoRec &TeamsInfoRec::operator=(const TeamsInfoRec &that)
{
	BfmeTmpACH((void *)&that).bfmeUseCH(this);

	return *this;
}
