// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// ?DoXfer@LivingWorldBuildPlot@@UAEXPAVXfer@@@Z retail 0x004FC57F..0x004FC807 (648B)
// WorldBuilder 0x01311F20 names LivingWorldBuildPlot::DoXfer in
// System/LivingWorld/LivingWorldBuildPlot.cpp (asserts 306..327). Retail
// vtable 0x00863528 slot 5 holds this body (RET 4). Version 1: plot ID +18
// then Coord2D +28 then build frames +30 then hidden flag +34; loading
// resolves the region ID through TheLivingWorldLogic's region table and
// rebuilds the building from its template name (emergency backup template
// clears the holder again) then restores the icon by name; saving writes the
// region ID and building ID plus template name and snapshot and the icon
// template name unless CRC. Layout matches LivingWorldBuildPlot.cpp's view.
// Callee rows: XferLivingWorldBuildPlotID 0x004FC14B / region and building ID
// xfers 0x003EFE82 0x004E075F / region lookup 0x0020EAF6 / template Lookup
// 0x002B931C and backup 0x004E0D4E / LivingWorldBuilding ctor pin 0x004E119C /
// holder set 0x00575674 and clear 0x000AD6F4 / CreateIcon 0x004FC185.
#include "ascii_string.h"
#include "Coord2D.h"
#include "../../../../Include/GameLogic/LivingWorldBuildPlot.h"

class Snapshot;
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

struct BuildPlotXferVersion
{
	BuildPlotXferVersion(unsigned char m, unsigned char c) : minimum(m), current(c) {}
	unsigned char minimum;
	unsigned char current;
};

void XferLivingWorldBuildPlotID(Xfer *xfer, void *id);
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *o, int a);
struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(struct Rva003EFE82Obj *obj, void *out);

class LivingWorldRegion;
class Rva0020E89C;
#include "../../../../Include/GameLogic/Rva0020EAF6View.h"
#include "../../../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;
// The region table read through an inline call, as retail's caller did.
static inline Rva0020EAF6View *livingWorldRegions() { return (Rva0020EAF6View *)TheLivingWorldLogic->fieldB0; }

struct Rva0059E647Entry;
#include "../../../../Include/GameLogic/Rva0059E647Factory.h"
class LivingWorldBuildingTemplate;
class LivingWorldBuildingTemplateStore
{
public:
	const LivingWorldBuildingTemplate *getEmergencyBackupTemplateForBadLoads();
};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;

#include "../../../../Include/GameLogic/LivingWorldBuilding.h"

class Object;
#include "../../../../Include/Common/Rva00575674.h"
#include "../../../../Include/Common/Rva000AD6F4.h"

// Keep the typed holder access local to this consumer.
static inline LivingWorldBuilding *GetBuildPlotBuilding(const Rva000AD6F4 &holder)
{
	return (LivingWorldBuilding *)holder.m_ptr;
}

struct BuildPlotIconView
{
	char m_pad00[0x14];
	const AsciiString *m_template;
};

struct BuildPlotRegionView
{
	char m_pad00[0x12C];
	int m_id;
};

// These accessors stay local: the pointer holders expose the canonical storage.
static inline int GetBuildPlotRegionID(const LivingWorldBuildPlot &plot)
{
	if (plot.field1C) return ((BuildPlotRegionView *)plot.field1C)->m_id;
	return -1;
}

static inline int GetBuildPlotBuildingID(const LivingWorldBuildPlot &plot)
{
	if (plot.field20.m_ptr) return ((LivingWorldBuilding *)plot.field20.m_ptr)->field18;
	return 0;
}

void LivingWorldBuildPlot::DoXfer(Xfer *xfer)
{
	BuildPlotXferVersion version(1, 1);
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	XferLivingWorldBuildPlotID(xfer, &field18);
	(*xfer == field28);
	(*xfer == field30);
	(*xfer == field34);
	if (xfer->IsLoading()) {
		int regionId;
		Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionId);
		field1C = 0;
		if (TheLivingWorldLogic)
			field1C = (LivingWorldRegion *)livingWorldRegions()->rva0020EAF6(regionId);
		int buildingId;
		Rva004E075FGet((Rva004E075FObj *)xfer, (int)&buildingId);
		if (buildingId != 0) {
			AsciiString templateName;
			(*xfer == templateName);
			const Rva003F1BD3TemplateView *buildingTemplate = (const Rva003F1BD3TemplateView *)
				((Rva0059E647Factory *)TheLivingWorldBuildingTemplateStore)->Lookup((int *)&templateName);
			if (buildingTemplate) {
				((Rva00575674 *)&field20)->rva00575674((Object *)new LivingWorldBuilding(field1C, field28, buildingTemplate, buildingId));
				(*xfer == *reinterpret_cast<Snapshot *>(GetBuildPlotBuilding(field20)));
			} else {
				buildingTemplate = (const Rva003F1BD3TemplateView *)
					((LivingWorldBuildingTemplateStore *)TheLivingWorldBuildingTemplateStore)->getEmergencyBackupTemplateForBadLoads();
				((Rva00575674 *)&field20)->rva00575674((Object *)new LivingWorldBuilding(field1C, field28, buildingTemplate, buildingId));
				(*xfer == *reinterpret_cast<Snapshot *>(GetBuildPlotBuilding(field20)));
				((Rva000AD6F4 *)&field20)->clear();
				field30 = 0;
				field34 = false;
			}
		}
		AsciiString iconName;
		(*xfer == iconName);
		if (!iconName.isEmpty())
			CreateIcon(iconName);
	} else {
		int regionId = GetBuildPlotRegionID(*this);
		Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionId);
		int buildingId = GetBuildPlotBuildingID(*this);
		Rva004E075FGet((Rva004E075FObj *)xfer, (int)&buildingId);
		if (field20.m_ptr && buildingId != 0) {
			AsciiString templateName(*reinterpret_cast<const AsciiString *>(((LivingWorldBuilding *)field20.m_ptr)->field28));
			(*xfer == templateName);
			(*xfer == *reinterpret_cast<Snapshot *>(GetBuildPlotBuilding(field20)));
		}
		if (!xfer->IsCRC()) {
			AsciiString iconName(field24.m_ptr ? *((BuildPlotIconView *)field24.m_ptr)->m_template : AsciiString::TheEmptyString);
			(*xfer == iconName);
		}
	}
}
