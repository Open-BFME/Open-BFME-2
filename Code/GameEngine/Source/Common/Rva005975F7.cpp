// cl: /MD
//
// ?rva005975F7@Rva005975F7@@QAEXXZ 27B @0x005975F7: pushes Player* at +0x14
// into global g_00DFEEF8's rowed rva002A8F24, then passes the returned
// pointer as this into rowed rva004DFEC8 with this (as ModuleData) as arg.
// Evidence: two E8 callees with row names in packet, global VA 0x00DFEEF8,
// second callee takes PBVModuleData so owner is a ModuleData; callers at
// 0x004EBFA4 0x004EBFCD. Owner identity unproven so honest address name.

class Player;
class ModuleData;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *p);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004DFEC8
{
public:
	void rva004DFEC8(const ModuleData *m);
};

class Rva005975F7
{
public:
	void rva005975F7();
private:
	char m_pad[0x14];
	Player *m_14;
};

void Rva005975F7::rva005975F7()
{
	void *p = g_00DFEEF8->rva002A8F24(m_14);
	((Rva004DFEC8 *)p)->rva004DFEC8((const ModuleData *)this);
}
