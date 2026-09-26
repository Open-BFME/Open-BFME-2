// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1RankInfo@@UAE@XZ, retail 0x00200236, 74 bytes. RankInfo dtor over the
// same layout as the rowed ctor 0x0020010B in RankInfoCtor.cpp (Overridable
// base 0x10 with vptr 0xBDDC48 shared with the pinned base dtor at 0x1E3624,
// UnicodeString at +0x10 via wide releaseBuffer pin 0x36E70, words
// +0x14..+0x34, int-vector storage at +0x38 via _free 0x30830). Teardown is
// vector storage (state 1) then string release (state 0) then the base
// through the pinned 0x1E3624 body. Caller is the slot-0 ??_G at 0x0020021A
// (vtable 0x7E26E0). Donor: BFME1 RankInfo.cpp empty dtor plus
// RankInfoDestructors store shape. New TU beside the ctor so the ctor's
// trivial StringBase does not change; the inline string dtor here emits the
// releaseBuffer call and the inline vector dtor emits the test-free.

typedef int Int;

void free(void *p);

class Rva001E3624
{
public:
	virtual ~Rva001E3624();

private:
	Rva001E3624 *m_next; // +0x04
	unsigned char m_isAllocated; // +0x08
	unsigned char m_pad09[3];
	Int m_extra0C; // +0x0C
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

struct IntVector
{
	~IntVector()
	{
		if (m_start)
			free(m_start);
	}

	int *m_start;
	int *m_finish;
	int *m_end;
};

class __declspec(novtable) RankInfo : public Rva001E3624
{
public:
	virtual ~RankInfo();

private:
	StringBase<unsigned short> m_rankName; // +0x10
	Int m_skillPointsNeeded; // +0x14
	Int m_bfme18; // +0x18
	Int m_bfme1C; // +0x1C
	Int m_bfme20; // +0x20
	Int m_bfme24; // +0x24
	Int m_bfme28; // +0x28
	Int m_bfme2C; // +0x2C
	Int m_bfme30; // +0x30
	Int m_sciencePurchasePointsGranted; // +0x34
	IntVector m_sciencesGranted; // +0x38
};

RankInfo::~RankInfo()
{
}
