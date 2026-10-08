// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Identity repair: native SidesList music loader 0x0032FD8E and WB
// 0x00A86AD0 construct and destroy the same objects, with TeamsInfoRec
// at 28 bytes and the LibraryMapCache vector header at 12 bytes.
// Existing member/base provider declarations are preserved; this is not
// a claim that all private class views or inherited template pins agree.
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

class TeamsInfoRec : public BfmeBaseCH
{
public:
	TeamsInfoRec(const TeamsInfoRec &value) throw();
	TeamsInfoRec &operator=(const TeamsInfoRec &that);
	~TeamsInfoRec() {}

	void swap(TeamsInfoRec *owner) throw();

	BfmeMemCH m_bfmeMemCH;
};

TeamsInfoRec &TeamsInfoRec::operator=(const TeamsInfoRec &that)
{
	TeamsInfoRec(that).swap(this);

	return *this;
}
