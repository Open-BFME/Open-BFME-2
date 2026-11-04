// cl: /MD /Ireference/shims/moduledata
// stlport
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// PerTurnStats snapshot transfer, retail 0x004EE15B.
// The canonical Xfer overloads preserve retail's slot-0x28 version call
// and three slot-0x84 short transfers at +0x04/+0x06/+0x08. Keep the
// existing field storage pending reconciliation with the full Snapshot view.
#include "AIXferTypes.h"
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/LivingWorldScoreKeeper.h"
class LivingWorldScoreKeeper::PerTurnStats
{
public:
	virtual ~PerTurnStats();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
private:
	char m_4[2];
	char m_6[2];
	int m_8;
};

void LivingWorldScoreKeeper::PerTurnStats::xfer(Xfer *o)
{
	char scratch[2] = { 1, 1 };
	(*o) == *reinterpret_cast<Xfer::Version *>(scratch);
	(*o) == *reinterpret_cast<short *>(m_4);
	(*o) == *reinterpret_cast<short *>(m_6);
	(*o) == *reinterpret_cast<short *>(&m_8);
}
