// cl: /DNDEBUG /MD /EHsc /DBFME_STRINGBASE_PUBLIC_COPY

// Open-BFME5: TerrainCollisionModuleInfo copy constructor.

#include "../../../../../../reference/shims/bfme2_ascii/string_base.h"

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &that)
		: StringBase<char>(that)
	{
	}
};

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

struct TerrainCollisionValueBlock
{
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

class TerrainCollisionModuleInfo : public Snapshot
{
public:
	TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &);
	virtual ~TerrainCollisionModuleInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(::Xfer &);

private:
	BFMERetailAsciiString m_eventName;
	TerrainCollisionValueBlock m_eventTime;
	bool m_flag;
	unsigned int m_cached;
};

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
TerrainCollisionModuleInfo::TerrainCollisionModuleInfo(
	const TerrainCollisionModuleInfo &that)
	: Snapshot(that),
	  m_eventName(that.m_eventName),
	  m_eventTime(that.m_eventTime),
	  m_flag(that.m_flag),
	  m_cached(that.m_cached)
{
}

}
