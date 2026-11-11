// cl: /MD
//
// ?ac26Slot1@Rva0056ACDF@@UAE_NXZ @0x0056AB97 41B.
// Guarded flag-set: false when the +0x14 record fails pinned 0x0056A989,
// else set byte +0x20 on the +0x10 record, notify the rowed 0x0029B1A1
// singleton, and return true. Honest address-derived names.
class InGameUI;
extern InGameUI *TheInGameUI;
class Rva0056A989
{
public:
	bool rva0056A989();
};

class Rva0029B1A1
{
public:
	void rva0029B1A1();
};

struct Rva0056AB97Inner
{
	char m_pad[0x20];
	unsigned char m_flag20;
};

class Rva0056ACDF
{
public:
	virtual ~Rva0056ACDF();
	virtual bool ac26Slot1();
private:
	char m_pad04[0x0C];
	Rva0056AB97Inner *m_10;	// +0x10
	Rva0056A989 *m_14;	// +0x14
};

bool Rva0056ACDF::ac26Slot1()
{
	if (m_14->rva0056A989()) {
		m_10->m_flag20 = true;
		(*(Rva0029B1A1 **)&TheInGameUI)->rva0029B1A1();
		return true;
	}
	return false;
}
