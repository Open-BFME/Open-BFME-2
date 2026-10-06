// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
//
// ?rva004BAF2D@EvacuateDamage@@QAEXPAX@Z @ 0x004BAF2D 40B
// EvacuateDamage post-evacuation cleanup with AI command. Evidence: sole
// caller 0x004BAFD9 (EvacuateDamage::onDamage 0x004BAF55) passes Object* from
// rowed findObjectByID 0x00049DC5; list at +0x14 via rowed ctor 0x004BAE1D and
// rowed sum 0x004BADC1; Object+0x258 holder with Rva at +0x20 via rowed
// rva0047ED64 0x0047ED64 with CommandSourceType 2; List_base clear via rowed
// 0x0023DAA5 ICF alias.

#include <list>

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1,
	CMD_SOURCE_2 = 2
};

class Rva0047ED64
{
public:
	void rva0047ED64(void *obj, CommandSourceType src);
};

struct Holder
{
	unsigned char m_pad[0x20];
	Rva0047ED64 m_cmd;
};

class Object
{
public:
	unsigned char m_pad[0x258];
	Holder *m_holder;
};

struct EvacuationRecord
{
	unsigned int m_data[2];
};

class EvacuateDamage
{
public:
	void rva004BAF2D(void *obj);
private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[8];
	std::list<EvacuationRecord> m_pendingEvacuations;
};

void EvacuateDamage::rva004BAF2D(void *obj)
{
	Holder *holder = m_object->m_holder;
	if (holder)
	{
		m_pendingEvacuations.clear();
		holder->m_cmd.rva0047ED64(obj, (CommandSourceType)2);
	}
}
