// ?rva0028F2C4@Rva0028F2C4Host@@QAEPAURva0028F2C4Entry@@H@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /MD
struct Rva0028F2C4Aux
{
	unsigned char m_pad[4];
	int m_id;
};
struct Rva0028F2C4Entry
{
	unsigned char m_pad[4];
	Rva0028F2C4Aux *m_aux;
};
class Rva0028F2C4Host
{
public:
	Rva0028F2C4Entry *rva0028F2C4(int id);
private:
	unsigned char m_pad[0x244];
	Rva0028F2C4Entry **m_array;
};
// ?rva0028F2C4@Rva0028F2C4Host@@QAEPAURva0028F2C4Entry@@H@Z
Rva0028F2C4Entry *Rva0028F2C4Host::rva0028F2C4(int id)
{
	int localId = id;
	Rva0028F2C4Entry **p = m_array;
	Rva0028F2C4Entry *e;
	while ((e = *p) != 0)
	{
		if (localId == e->m_aux->m_id)
			break;
		p++;
	}
	return e;
}
