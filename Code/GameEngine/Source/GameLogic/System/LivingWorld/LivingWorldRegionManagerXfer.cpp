// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// WB B590C0/B59670 name LivingWorldRegionManager::XferRegions/DoXfer and
// System/LivingWorld/LivingWorldRegionManager.cpp. Complete native bounds
// 20EFA0..20F0B8 (280B) and210202..2102CA (200B) prove accessed fields,
// campaign region-vector2C, region name14/id12C, and virtual transfer slot3.
// Existing SelectCampaign20F1F3 and lookup20EAF6 independently corroborate
// the same receiver/current-campaign and region-vector layouts. BF1 ba7ddda
// LivingWorldRegionManager_Rva003C8D50.cpp supplies the clean region-transfer
// semantic guide and LivingWorldRegionManagerDestructor the ownership lead;
// target extents/offsets come from BF2 and full application layouts remain open.
// Canonical BFME2 AsciiString preserves direct releaseBuffer cleanup.
// Native Xfer table7BB910 proves Version10/AsciiString27/int31; the region-
// and battle-ID helpers retain their existing void-pointer declarations.
// Both complete emitted bodies and exception-unwind tables reproduce retail.
#include <vector>
#include "ascii_string.h"
struct XferVersionFields
{
	unsigned char minimum, current;
};
union XferVersion
{
	XferVersionFields fields;
	unsigned value;
};
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

struct Rva003EFE82Obj;
int Rva003EFE82Get(Rva003EFE82Obj *, void *);
void XferLivingWorldBattleID(Xfer *, void *);

// Snapshot call view and accessed prefix only; no full region layout or
// additional vtable definitions are emitted.
class RegionSnapshotTransferView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void DoXfer(Xfer *);
	char unknown04[0x10];
	AsciiString name;
	char unknown18[0x12C - 0x18];
	int id;
};
class Rva0020E89C;
#include "../../../../Include/GameLogic/Rva0020EAF6View.h"
#include "../../../../Include/GameLogic/Rva0020EE29.h"
struct RegionCampaignView
{
	AsciiString name;
	char unknown04[0x28];
	_STL::vector<RegionSnapshotTransferView *> regions;
};
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../Include/Common/RegionTurnObserverView.h"
class LivingWorldRegionManager : public Snapshot, public RegionTurnObserverView
{
public:
	void SelectCampaign(const StringBase<char> &);
	void XferRegions(Xfer *);
	virtual ~LivingWorldRegionManager();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
	virtual void BeginTurn(int, int);
	virtual void OnTurnEnding(int, int);

	RegionCampaignView *current;
	int battle0C, battle10;
	char unknown14[0x18];
	int field2C, battle30;
};

void LivingWorldRegionManager::XferRegions(Xfer *xfer)
{
	xfer->Version1();
	_STL::vector<RegionSnapshotTransferView *> &regions = current->regions;
	if (xfer->IsLoading()) {
		int count;
		(*xfer == count);
		for (int i = 0; i < count; ++i) {
			AsciiString name;
			(*xfer == name);
			int id;
			Rva003EFE82Get(reinterpret_cast<Rva003EFE82Obj *>(xfer), &id);
			RegionSnapshotTransferView *region = reinterpret_cast<RegionSnapshotTransferView *>(
				reinterpret_cast<Rva0020EAF6View *>(this)->rva0020EAF6(id));
			if (region) region->DoXfer(xfer);
		}
	} else {
		int count = regions.size();
		(*xfer == count);
		for (int i = 0; i < count; ++i) {
			AsciiString name = regions[i]->name;
			(*xfer == name);
			int id = regions[i]->id;
			Rva003EFE82Get(reinterpret_cast<Rva003EFE82Obj *>(xfer), &id);
			regions[i]->DoXfer(xfer);
		}
	}
}

void LivingWorldRegionManager::xfer(Xfer *xfer)
{
	XferVersion version;
	version.fields.minimum = 1;
	version.fields.current = 1;
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	(*xfer == field2C);
	XferLivingWorldBattleID(xfer, &battle30);
	AsciiString name;
	if (xfer->IsLoading()) {
		current = 0;
		(*xfer == name);
		SelectCampaign(*reinterpret_cast<StringBase<char> *>(&name));
	} else {
		name = current->name;
		(*xfer == name);
	}
	XferRegions(xfer);
	reinterpret_cast<Rva0020EE29 *>(this)->rva002101C6(xfer);
	XferLivingWorldBattleID(xfer, &battle0C);
	XferLivingWorldBattleID(xfer, &battle10);
	xfer->IsLoading();
}
