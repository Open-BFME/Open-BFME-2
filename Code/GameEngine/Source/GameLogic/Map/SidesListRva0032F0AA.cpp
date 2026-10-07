// cl: /O1 /EHsc /MD
// ?rva0032F0AA@SidesList@@QAE_NAAVDataChunkInput@@PAX@Z, retail 0x0032F0AA, 146 bytes.
// Temp SidesList load: ctor SidesList, readInt count, loop readDict plus TeamsInfoRec::addTeam at +0xF44, swap via SidesList::rva0032B7A7, dtor Rva0032EC63, return true.
// Evidence: local size 0x11B0 plus Dict matches 0x11B4 probe; ctor pin SidesList 0x0032EE24 plus dtor pin Rva0032EC63 0x0032EC63 on same temp; callers as constants at 0x000AF459 and 0x0032F546; teamrec offset from SidesListRva0032B7A7 and SidesListSwap layouts.
class Dict
{
public:
	~Dict() { releaseData(); }
private:
	void releaseData();
	void *m_data;
};

class DataChunkInput
{
public:
	int readInt();
	Dict readDict();
};

class TeamsInfoRec
{
public:
	int addTeam(const Dict *dict);
private:
	char m_body[0x1C];
};

class Rva0032EC63
{
public:
	virtual ~Rva0032EC63();
public:
	char m_pad0[0xF44 - 4];
	TeamsInfoRec m_teamrec;
	char m_tail[0x11B0 - 0xF44 - 0x1C];
};

class SidesList : public Rva0032EC63
{
public:
	SidesList();
	void rva0032B7A7(SidesList *other);
	bool rva0032F0AA(DataChunkInput &file, void *userData);
};

bool SidesList::rva0032F0AA(DataChunkInput &file, void *userData)
{
	SidesList tmp;
	int count = file.readInt();
	if (count > 0)
	{
		for (int i = count; i > 0; --i)
		{
			Dict d = file.readDict();
			tmp.m_teamrec.addTeam(&d);
		}
	}
	this->rva0032B7A7(&tmp);
	return true;
}
