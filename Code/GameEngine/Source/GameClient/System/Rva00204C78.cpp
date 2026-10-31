// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva00204C78@Rva00204C78@@QAEXPBD@Z, retail 0x00204C78 (238 bytes, RET 4):
// a vtable slot (table 0x007E3A24) of the particle holder whose sibling
// 0x00204C21 stops a named system. It releases the held system (rowed
// 0x0020453C), looks the named template up (findTemplate) and creates a
// system from it (createParticleSystem, with slaves); a created system's
// ID (+0xA8) and flag (+0x1A2) are kept at +4/+8 and it is placed at
// (200, 200) 100 units above the ground (TheTerrainLogic slot +0x18), through
// the null-safe system access (Make001FCBD7) and the rowed position setter
// 0x001F3899. Handle spelling from ParticleSystemTemplateCreateSlave.cpp.
#include "ascii_string.h"

struct Coord3D;
class ParticleSystemTemplate;

class ParticleSystem
{
public:
	unsigned char m_pad000[0xA8];
	int m_id;		// +0xA8
	unsigned char m_pad0AC[0x1A2 - 0xAC];
	bool m_1A2;		// +0x1A2
};
ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &);
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw();
	void rva0004CBC0() throw();
	void *ptr; int prev, next;
};
class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle() : ptr(0), prev(0), next(0) {}
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &x) { ((RvaSmartPtr12 *)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12 *)&x); }
	~BfmeParticleSystemHandle() { if (ptr) ((RvaSmartPtr12 *)this)->rva0004CBC0(); }
	void *ptr; int prev, next;
};

class BFMERetailAsciiString;
class Rva000427195;
class Rva000411084
{
public:
	void *m_node;
	Rva000427195 *m_table;
	void *next();
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iterator);
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *tmpl, bool createSlaves);
	void bfmeStopCW(const BFMERetailAsciiString &name);
	unsigned char m_pad[0x88];
	Rva000427195 m_templateMap;	// +0x88
};
extern ParticleSystemManager *TheParticleSystemManager;

struct Rva001F3899Arg
{
	float x, y, z;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &pos);
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual void s03(); virtual void s04(); virtual void s05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);	// +0x18
};
extern TerrainLogic *TheTerrainLogic;

class Rva0020453CHolderBase
{
public:
	~Rva0020453CHolderBase() { release(); }
	virtual void holderSlot0();
	void release();

protected:
	int m_systemID;		// +0x04
	bool m_flag;		// +0x08
};

struct Rva00204C78 : Rva0020453CHolderBase
{
	void rva00204C78(const char *name);
};

void Rva00204C78::rva00204C78(const char *name)
{
	release();
	ParticleSystemTemplate *particleSystemTemplate = TheParticleSystemManager->findTemplate(AsciiString(name));
	if (!particleSystemTemplate)
		return;
	BfmeParticleSystemHandle handle = TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true);
	if (handle.ptr)
	{
		ParticleSystem *created = (ParticleSystem *)handle.ptr;
		m_systemID = created->m_id;
		m_flag = created->m_1A2;
		Rva001F3899Arg pos;
		pos.y = 200.0f;
		pos.x = 200.0f;
		pos.z = TheTerrainLogic->getGroundHeight(200.0f, 200.0f, 0) + 100.0f;
		ParticleSystem *system = (ParticleSystem *)handle.ptr;
		if (!system)
			system = Make001FCBD7();
		((Rva001F3899Slot *)system)->set(pos);
	}
}
