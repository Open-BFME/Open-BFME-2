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

class Snapshot;
class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual void slot02();
	virtual bool isCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(void *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void xferCoord2D(Coord2D *value);
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferInt(int *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(bool *value);
};

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
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int);
};
class LivingWorldLogic
{
public:
	char m_pad00[0xB0];
	Rva0020EAF6View *m_regions;
	Rva0020EAF6View *getRegions() const { return m_regions; }
};
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva0059E647Entry;
struct Rva0059E647Factory
{
	Rva0059E647Entry *Lookup(int *);
};
class LivingWorldBuildingTemplate;
class LivingWorldBuildingTemplateStore
{
public:
	const LivingWorldBuildingTemplate *getEmergencyBackupTemplateForBadLoads();
};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;

struct Rva003F1BD3TemplateView;
class LivingWorldBuilding
{
public:
	LivingWorldBuilding(LivingWorldRegion *region, const Coord2D &position,
	                   const Rva003F1BD3TemplateView *templ, int id);
	char m_pad00[0x18];
	int m_id;
	char m_pad1C[0x0C];
	const AsciiString *m_template;
	char m_pad2C[0x28];
};

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *object);
	LivingWorldBuilding *m_building;
	LivingWorldBuilding *get() const { return m_building; }
};
class Rva000AD6F4
{
public:
	void clear();
};

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

class LivingWorldBuildPlot
{
public:
	virtual void DoXfer(Xfer *xfer);
	void CreateIcon(const AsciiString &iconName);

	char m_pad04[0x14];
	int m_id;
	LivingWorldRegion *m_region;
	Rva00575674 m_building;
	BuildPlotIconView *m_icon;
	Coord2D m_position;
	int m_buildFrames;
	bool m_hidden;
	int getRegionID() const { if (m_region) return ((BuildPlotRegionView *)m_region)->m_id; return -1; }
	int getBuildingID() const { if (m_building.get()) return m_building.get()->m_id; return 0; }
};

void LivingWorldBuildPlot::DoXfer(Xfer *xfer)
{
	BuildPlotXferVersion version(1, 1);
	xfer->xferVersion(&version);
	XferLivingWorldBuildPlotID(xfer, &m_id);
	xfer->xferCoord2D(&m_position);
	xfer->xferInt(&m_buildFrames);
	xfer->xferBool(&m_hidden);
	if (xfer->isLoading()) {
		int regionId;
		Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionId);
		m_region = 0;
		if (TheLivingWorldLogic)
			m_region = (LivingWorldRegion *)TheLivingWorldLogic->getRegions()->rva0020EAF6(regionId);
		int buildingId;
		Rva004E075FGet((Rva004E075FObj *)xfer, (int)&buildingId);
		if (buildingId != 0) {
			AsciiString templateName;
			xfer->xferAsciiString(&templateName);
			const Rva003F1BD3TemplateView *templ = (const Rva003F1BD3TemplateView *)
				((Rva0059E647Factory *)TheLivingWorldBuildingTemplateStore)->Lookup((int *)&templateName);
			if (templ) {
				m_building.rva00575674((Object *)new LivingWorldBuilding(m_region, m_position, templ, buildingId));
				xfer->xferSnapshot(m_building.get());
			} else {
				templ = (const Rva003F1BD3TemplateView *)
					((LivingWorldBuildingTemplateStore *)TheLivingWorldBuildingTemplateStore)->getEmergencyBackupTemplateForBadLoads();
				m_building.rva00575674((Object *)new LivingWorldBuilding(m_region, m_position, templ, buildingId));
				xfer->xferSnapshot(m_building.get());
				((Rva000AD6F4 *)&m_building)->clear();
				m_buildFrames = 0;
				m_hidden = false;
			}
		}
		AsciiString iconName;
		xfer->xferAsciiString(&iconName);
		if (!iconName.isEmpty())
			CreateIcon(iconName);
	} else {
		int regionId = getRegionID();
		Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionId);
		int buildingId = getBuildingID();
		Rva004E075FGet((Rva004E075FObj *)xfer, (int)&buildingId);
		if (m_building.m_building && buildingId != 0) {
			AsciiString templateName(*m_building.m_building->m_template);
			xfer->xferAsciiString(&templateName);
			xfer->xferSnapshot(m_building.get());
		}
		if (!xfer->isCRC()) {
			AsciiString iconName(m_icon ? *m_icon->m_template : AsciiString::TheEmptyString);
			xfer->xferAsciiString(&iconName);
		}
	}
}
