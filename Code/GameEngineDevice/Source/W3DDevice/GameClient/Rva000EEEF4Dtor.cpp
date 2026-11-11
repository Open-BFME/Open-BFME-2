// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1W3DPropBuffer@@UAE@XZ, retail 0x000EEEF4..0x000EEFE6 (242 bytes, EH):
// W3DPropBuffer's destructor. It installs table 0x00BCEECC, the table the
// rowed W3DPropBuffer constructor 0x000EF008 installs (slot 2 returns the
// "W3DPropBuffer" literal, slot 3 is the rowed xfer). It releases and clears the
// reference at the head of each of its first m_count2EE04 records (+4,
// 0x30 bytes each), of each of its 96 entries (+0x2EE18, 0x18 bytes each)
// and its two loose references (+0x2F724, +0x2F71C). Then its parts die
// (retail's unwind map): the 96 entries (element destructor releases the
// AsciiString at +4, folded at 0x0029D7C2), the +0x2EE0C vector wrapper
// (inline destructor running rowed 0x0008B470, unwind copy 0x0008B4CD), the
// 4000 records (element destructor is the bare return 0x000B3FD0) and
// Snapshot (table 0x00BBB554). The member types' identities are not established.
// Retail slot 2 is the snapshot-name getter, so this unit uses that slot spelling.
#define BFME_SNAPSHOT_NAME_SLOT
#include "ascii_string.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva000EEEF4Ref
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

struct Rva000EEEF4Record
{
	// Empty: retail destroys the records through the bare return 0x000B3FD0.
	~Rva000EEEF4Record() {}
	Rva000EEEF4Ref *m_ref;
	unsigned char m_pad04[0x30 - 4];
};

class Rva0008B470
{
public:
	~Rva0008B470();
private:
	void *m_data[3];
};

#include "../../../Include/W3DDevice/GameClient/Rva0008B4CD.h"

struct Rva000EEEF4Entry
{
	Rva000EEEF4Ref *m_ref;
	AsciiString m_name;
	unsigned char m_pad08[0x18 - 8];
};

class W3DPropBuffer : public Snapshot
{
public:
	virtual ~W3DPropBuffer();
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	Rva000EEEF4Record m_records[0xFA0];		// +0x4
	int m_count2EE04;				// +0x2EE04
	int m_2EE08;
	Rva0008B4CD m_member2EE0C;			// +0x2EE0C
	Rva000EEEF4Entry m_entries[0x60];		// +0x2EE18
	Rva000EEEF4Ref *m_ref2F718;			// +0x2F718
	Rva000EEEF4Ref *m_ref2F71C;			// +0x2F71C
	Rva000EEEF4Ref *m_ref2F720;			// +0x2F720
	Rva000EEEF4Ref *m_ref2F724;			// +0x2F724
};

W3DPropBuffer::~W3DPropBuffer()
{
	int i;
	for (i = 0; i < m_count2EE04; ++i)
	{
		if (m_records[i].m_ref)
		{
			m_records[i].m_ref->Release_Ref();
			m_records[i].m_ref = 0;
		}
	}
	for (i = 0; i < 0x60; ++i)
	{
		if (m_entries[i].m_ref)
		{
			m_entries[i].m_ref->Release_Ref();
			m_entries[i].m_ref = 0;
		}
	}
	if (m_ref2F724)
	{
		m_ref2F724->Release_Ref();
		m_ref2F724 = 0;
	}
	if (m_ref2F71C)
	{
		m_ref2F71C->Release_Ref();
		m_ref2F71C = 0;
	}
}
