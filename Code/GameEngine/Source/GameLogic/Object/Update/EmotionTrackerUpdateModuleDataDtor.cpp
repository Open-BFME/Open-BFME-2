// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD
//
// ??1EmotionTrackerUpdateModuleData@@UAE@XZ, retail 0x004B1285, 157 bytes.
// EmotionTrackerUpdateModuleData destructor over the ctor TU layout
// (vtable 0x00C56530, four filter members at +0x10/+0x14/+0x18/+0x1C,
// entry-pointer vector at +0x34). The body destroys vector elements with
// a custom loop (each non-null entry through the rowed 0x004DC9ED record
// dtor plus the pinned scalar delete); implicit member destruction then
// frees the storage through the rowed _free inside the inline entry-vector
// destructor, tears down the filters through the pinned 0x00360D26 dtor
// with descending EH states, and restores the Snapshot base vtable
// 0x00BBB554. The ??_G at 0x004B15AE calls this body directly. EH arms
// count live tracked members (5/4/3/2/1/0).

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();

private:
	int m_handle;
};

class Rva004DC9EDEntry
{
public:
	~Rva004DC9EDEntry();
};

extern "C" void free(void *block) throw(...);

struct EntryVec
{
	~EntryVec()
	{
		if (m_start != 0)
			free(m_start);
	}

	Rva004DC9EDEntry **m_start;
	Rva004DC9EDEntry **m_finish;
	Rva004DC9EDEntry **m_end;
};

class EmotionTrackerUpdateModuleData : public Snapshot
{
public:
	virtual ~EmotionTrackerUpdateModuleData();

private:
	int m_unused04; // +0x04, retail never stores it
	float m_value08; // +0x08
	int m_flags0C; // +0x0C
	Rva003623E5Filter m_filter0; // +0x10
	Rva003623E5Filter m_filter1; // +0x14
	Rva003623E5Filter m_filter2; // +0x18
	Rva003623E5Filter m_filter3; // +0x1C
	float m_value20; // +0x20
	float m_value24; // +0x24
	float m_value28; // +0x28
	bool m_flag2C; // +0x2C
	int m_immuneToFearLevel; // +0x30
	EntryVec m_entries; // +0x34
};

// ??1EmotionTrackerUpdateModuleData@@UAE@XZ @0x004B1285
EmotionTrackerUpdateModuleData::~EmotionTrackerUpdateModuleData()
{
	Rva004DC9EDEntry **it = m_entries.m_start;
	Rva004DC9EDEntry **finish = m_entries.m_finish;
	if (it != finish)
	{
		do
		{
			Rva004DC9EDEntry *entry = *it;
			if (entry != 0)
			{
				entry->~Rva004DC9EDEntry();
				operator delete(entry);
			}
			++it;
		} while (it != m_entries.m_finish);
	}
}
