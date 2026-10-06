// cl: /MD
struct Rva00287C21Other
{
	unsigned char m_pad[0x49C];
	int m_49C;
};
class FireLogicSystem
{
public:
	void RegisterObject(Rva00287C21Other *o);
	void UnregisterObject(Rva00287C21Other *o);
	void rva00287552(Rva00287C21Other *o, int v);
};
// ?RegisterObject@FireLogicSystem@@QAEXPAURva00287C21Other@@@Z
void FireLogicSystem::RegisterObject(Rva00287C21Other *o)
{
	if (o->m_49C < 0)
		rva00287552(o, 1);
}
// ?UnregisterObject@FireLogicSystem@@QAEXPAURva00287C21Other@@@Z
void FireLogicSystem::UnregisterObject(Rva00287C21Other *o)
{
	if (o->m_49C >= 0)
		rva00287552(o, 0);
}
