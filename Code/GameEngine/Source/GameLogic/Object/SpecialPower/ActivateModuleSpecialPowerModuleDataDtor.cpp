// cl: /O1 /MD /DNDEBUG /EHsc
//
// ??1ActivateModuleSpecialPowerModuleData@@UAE@XZ, retail 0x0025714A, 93 bytes.
// Target evidence: the audited scalar deleting dtor 0x0025712E calls this
// body (registration ActivateModuleSpecialPower -> factory 0x00256DC5 ->
// ctor 0x00256DA1). Body: installs vtable 0x00BF3F60, clears the 8-byte POD
// vector at +0xC8 through the rowed erase 0x002571A7 (begin, end), frees its
// buffer inline (0x00030830), then calls the module-data base dtor
// 0x0044ECCE (Rva0044ECCE, 0xC8 prefix). Vector modelled with the rowed
// Rva002571A7Vector view; element type unrecovered.

// C++-linkage free (pinned ?free@@YAXPAX@Z) as STLport compiles against: a
// direct call that may throw, so the member teardown gets its EH state.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva002571A7Elem
{
	int m_a;
	int m_b;
};

class Rva002571A7Vector
{
public:
	~Rva002571A7Vector()
	{
		if (m_begin)
			free(m_begin);
	}
	Rva002571A7Elem *begin() { return m_begin; }
	Rva002571A7Elem *end() { return m_finish; }
	void clear() { erase(begin(), end()); }
	Rva002571A7Elem *erase(Rva002571A7Elem *first, Rva002571A7Elem *last);

private:
	Rva002571A7Elem *m_begin;
	Rva002571A7Elem *m_finish;
	Rva002571A7Elem *m_end;
};

class Xfer;

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;

private:
	unsigned char m_tail[0xC8 - 4];
};

class ActivateModuleSpecialPowerModuleData : public Rva0044ECCE
{
public:
	virtual ~ActivateModuleSpecialPowerModuleData();

private:
	Rva002571A7Vector m_vectorC8;	// +0xC8
};

ActivateModuleSpecialPowerModuleData::~ActivateModuleSpecialPowerModuleData()
{
	m_vectorC8.clear();
}
