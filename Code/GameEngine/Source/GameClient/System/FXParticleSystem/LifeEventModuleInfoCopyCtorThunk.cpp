// cl: /DNDEBUG /MD /EHsc /DBFME_STRINGBASE_PUBLIC_COPY

// Open-BFME5: LifeEventModuleInfo copy constructor.

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
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

struct LifeEventValueBlock
{
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

class LifeEventModuleInfo : public Snapshot
{
public:
	LifeEventModuleInfo(const LifeEventModuleInfo &);
	virtual ~LifeEventModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

private:
	BFMERetailAsciiString m_name;
	LifeEventValueBlock m_values;
	unsigned int m_eventType;
};

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
LifeEventModuleInfo::LifeEventModuleInfo(const LifeEventModuleInfo &that)
	: Snapshot(that),
	  m_name(that.m_name),
	  m_values(that.m_values),
	  m_eventType(that.m_eventType)
{
}

}
