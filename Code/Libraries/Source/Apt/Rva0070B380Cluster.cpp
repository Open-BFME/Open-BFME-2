// cl: /MD
// Address-derived Apt hash lookup helper at 0x0070B380 (133B). The body hashes
// the key through the rowed ?rva006D3D10@EAStringC@@QBEGXZ (0x006D3D10), and
// when the +4 map exists looks the key up through the private callee pinned at
// 0x0070AF90, returning its +4 payload. Otherwise two magic ids (0x699, 0x6bbd)
// gate compares against the rowed #Rva0070B4F0GetString table entries 0x78 and
// 0, returning the +0xc and +8 fields. Names are address-derived.

class EAStringC
{
public:
	unsigned short rva006D3D10() const;
	bool rva006D3560(const EAStringC *other) const;
};

class Rva0070B4F0GetString_t;
EAStringC *Rva0070B4F0GetString(int index);

class Rva0070B380
{
public:
	void *rva0070AF90(const EAStringC &key);
	void *lookup(const EAStringC &key);

private:
	char m_pad[4];
	void *m_field4;
	void *m_field8;
	void *m_fieldC;
};

void *Rva0070B380::lookup(const EAStringC &key)
{
	int id = key.rva006D3D10();
	if (m_field4)
	{
		void **found = (void **)rva0070AF90(key);
		if (found)
			return found[1];
	}
	if (id == 0x699)
	{
		if (key.rva006D3560(Rva0070B4F0GetString(0x78)))
			return m_fieldC;
	}
	else if (id == 0x6bbd)
	{
		if (key.rva006D3560(Rva0070B4F0GetString(0)))
			return m_field8;
	}
	return 0;
}
