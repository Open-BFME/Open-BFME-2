// cl: /O1 /MD /EHsc
// ??1Rva00A86CE@@UAE@XZ retail 0x000A86CE 64B
// No vptr store at all (novtable): the handle at +0xC is torn down through
// the rowed ??1Rva00690FF0Handle@@QAE@XZ 0x000A8A37 (EH state 0), then the
// holder at +4 releases the ref at +0x88 of its pointee through the rowed
// ?Release_Ref@OpaqueRefCounted 0x00050ED3 when set. Caller: rowed
// ??_GRva00A86CE 0x00051139. Names address-derived.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva00A86CEOwner
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref; // +0x88
};

class Rva00A86CEHolder
{
public:
	~Rva00A86CEHolder()
	{
		if (m_owner)
			m_owner->m_ref.Release_Ref();
	}

	Rva00A86CEOwner *m_owner;
};

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();

private:
	void *m_handle;
};

class __declspec(novtable) Rva00A86CE
{
public:
	virtual ~Rva00A86CE();

private:
	Rva00A86CEHolder m_04; // +0x04
	int m_08;
	Rva00690FF0Handle m_0C; // +0x0C
};

Rva00A86CE::~Rva00A86CE()
{
}
