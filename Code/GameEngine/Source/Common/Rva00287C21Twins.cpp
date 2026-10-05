// cl: /O1 /MD
struct Rva00287C21Other
{
	unsigned char m_pad[0x49C];
	int m_49C;
};
class Rva00287C21Host
{
public:
	void rva00287C21(Rva00287C21Other *o);
	void rva00287C39(Rva00287C21Other *o);
	void rva00287552(Rva00287C21Other *o, int v);
};
// ?rva00287C21@Rva00287C21Host@@QAEXPAURva00287C21Other@@@Z
void Rva00287C21Host::rva00287C21(Rva00287C21Other *o)
{
	if (o->m_49C < 0)
		rva00287552(o, 1);
}
// ?rva00287C39@Rva00287C21Host@@QAEXPAURva00287C21Other@@@Z
void Rva00287C21Host::rva00287C39(Rva00287C21Other *o)
{
	if (o->m_49C >= 0)
		rva00287552(o, 0);
}
