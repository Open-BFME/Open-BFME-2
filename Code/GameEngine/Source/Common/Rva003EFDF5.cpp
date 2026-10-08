// cl: /O1 /MD
// ?rva003EFDF5@Rva003EFDF5Host@@QAEXPAX@Z @0x003EFDF5 73B. Leaf via caller
// 0x0020E37C (Rva002104C7::rva0020E374 forwards a1 as object and a2 as arg).
// Stores low byte of void* arg at this+0x1A2 and inner(this+0x198)+0x2C; when
// zero runs g_009FEF10->m_B0->rva0020EA22(this+0x12C); then if
// g_009FE1C8->m_268 non-null runs it->SyncRegion((int)this). Types follow
// rowed callees and g_ externs in use.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0020EA22Outer
{
public:
	void rva0020EA22(int v);
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xB0];
	Rva0020EA22Outer *m_B0;
};

class LivingWorldRegionEffectsManager
{
public:
	void SyncRegion(int value);
};

class Rva0021294A
{
public:
	char m_pad[0x268];
	LivingWorldRegionEffectsManager *m_268;
};

extern Rva0021294A *g_009FE1C8;

struct Rva003EFDF5Inner
{
	char m_pad[0x2C];
	unsigned char m_2C;
};

class Rva003EFDF5Host
{
public:
	void rva003EFDF5(void *a);
private:
	char m_pad00[0x12C];
	int m_12C;
	char m_pad130[0x198 - 0x130];
	Rva003EFDF5Inner *m_198;
	char m_pad19C[0x1A2 - 0x19C];
	unsigned char m_1A2;
};

void Rva003EFDF5Host::rva003EFDF5(void *a)
{
	unsigned char v = (unsigned char)(unsigned int)a;
	Rva003EFDF5Inner *inner = m_198;
	m_1A2 = v;
	inner->m_2C = v;
	if (v == 0)
		(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_B0->rva0020EA22(m_12C);
	LivingWorldRegionEffectsManager *obj = g_009FE1C8->m_268;
	if (obj)
		obj->SyncRegion((int)this);
}
