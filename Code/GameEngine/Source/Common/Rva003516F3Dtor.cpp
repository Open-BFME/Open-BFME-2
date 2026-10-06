// cl: /O1 /MD /EHs
// ??1Rva003516F3@@UAE@XZ retail 0x003516F3 96B
// Own vptr C14CD0; under EH state 1 the object at +0x4C is deleted through
// its slot-0 deleting dtor with flag 0 and the global ??3@YAXPAX@Z (a
// global-scope delete) and cleared when non-null; under state 0 the buffer member at +0x3C
// runs its inline dtor (CRT free of its block); then the pinned base dtor
// ??1Gen_uwm_004d759c@@QAE@XZ 0x004D759C runs. Names address-derived.

extern "C" void __cdecl free(void *block);

class Gen_uwm_004d759c
{
public:
	~Gen_uwm_004d759c();
	virtual void Rva003516F3Slot0();

private:
	unsigned char m_pad04[0x3C - 4];
};

class Rva003516F3Owned
{
public:
	virtual ~Rva003516F3Owned();
};

class Rva003516F3Buffer
{
public:
	~Rva003516F3Buffer()
	{
		if (m_data)
			free(m_data);
	}

	void *m_data; // +0x00
};

class Rva003516F3 : public Gen_uwm_004d759c
{
public:
	virtual ~Rva003516F3();

private:
	Rva003516F3Buffer m_buffer; // +0x3C
	unsigned char m_pad40[0x4C - 0x40];
	Rva003516F3Owned *m_owned; // +0x4C
};

Rva003516F3::~Rva003516F3()
{
	if (m_owned)
	{
		::delete m_owned;
		m_owned = 0;
	}
}
