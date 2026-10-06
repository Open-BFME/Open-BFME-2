// cl: /MD

// ?rva0035D3B4@Rva0035D352@@UAEXH@Z, retail 0x0035D3B4, 19 bytes.
// Slot 1 (offset 0x4) of vtable 0x00816478 installed by rowed dtor 0x0035D352.
// Sets m_08=0 m_09=1 then tail-calls slot 2 (offset 0x8) with m_10 at +0x10.
// Layout from retail immediates (head flags at +8/+9 plus lo at +0x10).

class Rva001DBAC3
{
public:
	virtual ~Rva001DBAC3();
};

class Rva0035D352 : public Rva001DBAC3
{
public:
	virtual ~Rva0035D352();
	virtual void rva0035D3B4(int unused);
	virtual void slot2(int val);

private:
	char m_pad00[4];
	bool m_08;
	bool m_09;
	char m_pad0A[6];
	int m_10;
	int m_14;
	char m_pad18;
	bool m_18;
	bool m_19;
};

void Rva0035D352::rva0035D3B4(int unused)
{
	(void)unused;
	m_09 = true;
	m_08 = false;
	slot2(m_10);
}
