// cl: /O1 /MD /EHs
//
// ??1BfmeOpaqueOwnedRecord1432@@QAE@XZ, retail 0x0038A1F2, 150B: the
// destructor of the 1432-byte record the PeerThread rows around it copy and
// destroy, under the name its 22 matched callers use. Target evidence: an
// empty body whose members tear down in reverse order -- five 12-byte
// owned buffers at +0x58C/+0x574/+0x568/+0x55C/+0x550 (free the start
// pointer when set; EH states 4..0 as each later member is done), then the
// +0x08 member through its rowed destructor 0x00385371. The gap at +0x580
// holds no destructor. Member names are placeholders; the five buffer
// destructors in retail are inline, the unwind funclets call them.
extern "C" void __cdecl free(void *block);

class Gen_uw_00385371
{
public:
	~Gen_uw_00385371();		// 0x00385371
	unsigned char m_bytes[0x540];
};

struct BfmeOwnedBuffer12
{
	// ?BfmeOwnedBuffer12::~BfmeOwnedBuffer12 present-unmatched (inline in the body; this unit emits a copy for its unwind funclets)
	void *m_start;
	void *m_finish;
	void *m_end;
	~BfmeOwnedBuffer12()
	{
		if (m_start != 0)
			free(m_start);
	}
};

class BfmeOpaqueOwnedRecord1432
{
public:
	~BfmeOpaqueOwnedRecord1432();
private:
	unsigned char m_pad0[8];
	Gen_uw_00385371 m_x8;			// +0x008
	unsigned char m_pad548[0x550 - 0x548];
	BfmeOwnedBuffer12 m_x550;		// +0x550
	BfmeOwnedBuffer12 m_x55C;		// +0x55C
	BfmeOwnedBuffer12 m_x568;		// +0x568
	BfmeOwnedBuffer12 m_x574;		// +0x574
	unsigned char m_pad580[0x58C - 0x580];
	BfmeOwnedBuffer12 m_x58C;		// +0x58C
};

BfmeOpaqueOwnedRecord1432::~BfmeOpaqueOwnedRecord1432()
{
}
