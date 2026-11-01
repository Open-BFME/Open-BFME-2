#pragma once
// Native tableC0D904 has four slots. Extent80 from32A1FE/32A942;
// fields32A0CE/3299AD, independent of the different ZH tail order.
#if defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#error BuildListInfo requires the named Snapshot surface before Snapshot is included
#endif
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3DInline.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"
class INI;
class BuildListInfo : public Snapshot
{
public:
	BuildListInfo();
	BuildListInfo(const BuildListInfo &);
	void deleteInstance();
	static void parseStructure(INI *, void *, void *, const void *);
	BuildListInfo *duplicate();
	BuildListInfo &operator=(const BuildListInfo &);
	virtual const char *GetSnapshotName() const;

protected:
	virtual ~BuildListInfo();
	virtual void loadPostProcess();
	virtual void xfer(Xfer *);

public:
	AsciiString m_buildingName; // +0x04
	AsciiString m_templateName; // +0x08
	Coord3D m_location; // +0x0C
	Coord2D m_rallyPointOffset; // +0x18
	float m_angle; // +0x20
	bool m_isInitiallyBuilt; // +0x24
	unsigned int m_numRebuilds; // +0x28
	BuildListInfo *m_nextBuildList; // +0x2C
	AsciiString m_script; // +0x30
	int m_health; // +0x34
	bool m_whiner; // +0x38
	bool m_unsellable; // +0x39
	bool m_repairable; // +0x3A
	bool m_automaticallyBuild; // +0x3B
	void *m_renderObj; // +0x3C
	void *m_shadowObj; // +0x40
	bool m_selected; // +0x44
	bool m_underConstruction; // +0x45
	bool m_isSupplyBuilding; // +0x46
	bool m_priorityBuild; // +0x47
	int m_objectID; // +0x48
	unsigned int m_objectTimestamp; // +0x4C
	int m_resourceGatherers[10]; // +0x50
	int m_desiredGatherers; // +0x78
	int m_currentGatherers; // +0x7C
public:
 enum {UNLIMITED_REBUILDS=0xFFFFFFFF,MAX_RESOURCE_GATHERERS=10};
 void setNextBuildList(BuildListInfo *next) {m_nextBuildList=next;}
 BuildListInfo *getNext() const {return m_nextBuildList;}
 void setNumRebuilds(unsigned int n) {m_numRebuilds=n;}
 int getNumRebuilds() {return m_numRebuilds;}
 void decrementNumRebuilds() {if(m_numRebuilds>0 && m_numRebuilds!=UNLIMITED_REBUILDS)--m_numRebuilds;}
 void incrementNumRebuilds() {if(m_numRebuilds!=UNLIMITED_REBUILDS)++m_numRebuilds;}
 bool isBuildable() {return m_numRebuilds>0 || m_numRebuilds==UNLIMITED_REBUILDS;}
 void setTemplateName(AsciiString name) {AsciiString &dst=m_templateName;dst=name;}
 AsciiString getTemplateName() const {return m_templateName;}
 AsciiString getBuildingName() const {return m_buildingName;}
 AsciiString getScript() const {return m_script;}
};

typedef char Bfme2BuildListInfo_extent80[(sizeof(BuildListInfo)==0x80)?1:-1];
