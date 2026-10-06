// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000682B8@Rva000682B8@@QAEX_N@Z retail 0x000682B8 41B chain lane.
// Evidence: forwards the same bool arg to two members at +0x3850/+0x3854;
// rowed callees ?rva000EA21A@Rva000EA21A@@QAEX_N@Z and
// ?rva000E6FE3@Rva000E6FE3@@QAEX_N@Z; tail-jmp to second.
class Rva000EA21A
{
public:
	void rva000EA21A(bool v);
};

class Rva000E6FE3
{
public:
	void rva000E6FE3(bool v);
};

class Rva000682B8
{
public:
	void rva000682B8(bool v);
private:
	unsigned char m_pad[0x3850];
	Rva000EA21A *m_a;
	Rva000E6FE3 *m_b;
};

void Rva000682B8::rva000682B8(bool v)
{
	if (m_a)
		m_a->rva000EA21A(v);
	if (m_b)
		m_b->rva000E6FE3(v);
}
