// cl: /O1 /MD
// ?rva00447B58@Rva00447B0E@@QAEAAU1@ABU1@@Z, retail 0x00447B58, 69 bytes.
// Copy-assign of Rva00447B0E (0x1D0): base BfmeSaveElement002295D7 at +0 via
// rowed 0x002DBAB9, Rva004479FD at +0x1AC via rowed 0x004479FD, StringBase at
// +0x1C8 via set 0x366F0, dword at +0x1CC. Layout from Rva00447B0EDtor.cpp
// (base 0x1AC, 0x1C at +0x1AC, StringBase at +0x1C8). Evidence: chain caller of
// just-landed 0x002DBAB9; neighbours share /O1; unblocks 0x00448352.
template <typename T> class StringBase
{
public:
	void set(const StringBase &o);
private:
	T *m_data;
};

struct BfmeSaveElement002295D7
{
	virtual ~BfmeSaveElement002295D7();
	char _pad[0x1AC - 4];
	BfmeSaveElement002295D7 &rva002DBAB9(const BfmeSaveElement002295D7 &o);
};

struct Rva004479FD
{
	StringBase<unsigned short> m_00;
	StringBase<unsigned short> m_04;
	StringBase<unsigned short> m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	Rva004479FD &rva004479FD(const Rva004479FD &o);
};

struct Rva00447B0E
{
	BfmeSaveElement002295D7 m_base00;
	Rva004479FD m_1AC;
	StringBase<char> m_1C8;
	int m_1CC;
	Rva00447B0E &rva00447B58(const Rva00447B0E &o);
};
typedef char Rva00447B0ESizeCheck[sizeof(Rva00447B0E) == 0x1D0 ? 1 : -1];

Rva00447B0E &Rva00447B0E::rva00447B58(const Rva00447B0E &o)
{
	m_base00.rva002DBAB9(o.m_base00);
	m_1AC.rva004479FD(o.m_1AC);
	m_1C8.set(o.m_1C8);
	m_1CC = o.m_1CC;
	return *this;
}
