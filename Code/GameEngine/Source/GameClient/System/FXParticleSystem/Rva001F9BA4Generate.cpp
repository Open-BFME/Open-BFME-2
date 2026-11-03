// flags: region default (reverse/retail_inventory/flag_regions.csv)
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva001F9BA4@ParticleSystem@FXParticleSystem@@QAEXPAXH@Z
// Retail 0x001F9BA4..0x001F9C73 (207 bytes) RET8: the particle generation
// loop of an FX particle system. The slave system template is looked up by
// the name at +0x78 (none when empty); then, while the generator at +0xA4
// still accepts (virtual slot 4), each of the requested particles gets its
// start values from generateNewParticleStartValues (0x001F55A8, named by
// WorldBuilder; rowed as ParticleSystem::rva001F55A8 in ParticleSys.cpp,
// whose record view is Rva001F55A8Info) into a local Rva001F376E record and
// is emitted through this
// system's virtual slot 5 -- unless the system emits above ground only
// (+0x81) and the start position lies below the terrain height plus 0.01.
// Evidence: WorldBuilder twin 0x00B12C90 (unnamed; its callees named),
// retail offsets and callees. The method name is address-derived.
#include "ascii_string.h"

// The out-of-line non-throwing isEmpty body 0x00001E2F (as the sibling
// ParticleSystemManagerMappedTextureUVs.cpp binds it).
template <> bool StringBase<char>::isEmpty() const throw();

typedef float Real;
struct Coord3D;

// The local record is a Snapshot-derived FX info (Rva001F376ECtor.cpp gives
// the table evidence). Its destructor, called only by the unwind funclet
// 0x0076B651, is the Snapshot-family fold 0x0049B47C: the own-table store is
// dead behind the expanded base destructor, leaving mov [ecx],0x00BBB554.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva001F376E : public Snapshot
{
public:
	Rva001F376E();
	virtual ~Rva001F376E() {}
	// Table slots 1-3 (0x000B3FD0, 0x001F37BE, 0x001F37C4), declared so the
	// local can be built; this unit emits no table, so nothing references them.
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
	float m_04, m_08, m_0c, m_10, m_14, m_18;
	float m_x;	// +0x1C
	float m_y;	// +0x20
	float m_z;	// +0x24
	float m_28, m_2c, m_30;
	int m_34;
	unsigned char m_38;
};

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};
extern ParticleSystemManager *TheParticleSystemManager;

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

struct Rva001F55A8Info;
class ParticleSystem
{
public:
	void rva001F55A8(Rva001F55A8Info *info, int particleNum, int particleCount);	// 0x001F55A8
};

class Rva001F9BA4Generator
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual bool canGenerate();
};

namespace FXParticleSystem {

class ParticleSystem
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0C(); virtual void v10();
	virtual void emitParticle(Rva001F376E *info, void *context, ParticleSystemTemplate *slave, int flags);

	void rva001F9BA4(void *context, int count);

private:
	unsigned char m_pad04[0x78 - 0x04];
	AsciiString m_slaveSystemName;		// +0x78
	unsigned char m_pad7c[0x81 - 0x7C];
	bool m_aboveGroundOnly;			// +0x81
	unsigned char m_pad82[0xA4 - 0x82];
	Rva001F9BA4Generator *m_generator;	// +0xA4
};

void ParticleSystem::rva001F9BA4(void *context, int count)
{
	ParticleSystemTemplate *slave = ((const StringBase<char> *)&m_slaveSystemName)->isEmpty() ? 0 : TheParticleSystemManager->findTemplate(m_slaveSystemName);
	Rva001F376E info;
	if (m_generator) {
		for (int i = 0; i < count; ++i) {
			if (!m_generator->canGenerate())
				break;
			reinterpret_cast<::ParticleSystem *>(this)->rva001F55A8(
				reinterpret_cast<Rva001F55A8Info *>(&info), i, count);
			if (m_aboveGroundOnly) {
				Real height = info.m_z + 0.01f;
				if (!(height >= TheTerrainLogic->getGroundHeight(info.m_x, info.m_y, 0)))
					continue;
			}
			emitParticle(&info, context, slave, 0);
		}
	}
}

}
