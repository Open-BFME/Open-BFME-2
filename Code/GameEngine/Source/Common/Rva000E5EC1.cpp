// cl: /MD
// ?rva000E5EC1@Rva000E5EC1@@QBE_NHABV?$StringBase@D@@@Z @0x000E5EC1 36B
// Target facts: 36B matcher called by 0x000E5EE5/0x000E5F60/0x000E6135; reads int at +0x4C
// and StringBase<char> at +0x8C, calls rowed ?compare@?$StringBase@D@@QBEHABV1@@Z (0x000069D6).
// Not established: owning class identity; address-derived honest name and layout.

template <typename T> class StringBase
{
public:
	int compare(const StringBase<T> &other) const;
private:
	void *m_data;
};

class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const;
private:
	char m_pad0[0x4C];
	int m_id;
	char m_pad1[0x8C - 0x4C - 4];
	StringBase<char> m_name;
};

bool Rva000E5EC1::rva000E5EC1(int id, const StringBase<char> &name) const
{
	return id == m_id && m_name.compare(name) == 0;
}
