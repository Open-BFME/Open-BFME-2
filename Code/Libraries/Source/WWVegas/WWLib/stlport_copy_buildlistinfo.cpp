// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__copy@PAVBuildListInfo@@PAV1@H@_STL@@YAPAVBuildListInfo@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x00329D64 52B
// ??$copy@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00@Z @0x0032A40E 29B
// STLport copy/__copy for BuildListInfo (0x80 bytes, sar 7, operator= loop).
// Evidence: __copy calls rowed ??4BuildListInfo@@QAEAAV0@ABV0@@Z at 0x003299AD;
// copy calls __copy; both byte-exact via explicit instantiation of copy.
// Layout matches BuildListInfoAssign.cpp (3 AsciiStrings, Coord3D+Coord2D+Real,
// 9 bools, ObjectID/timestamp, 10 gatherers, desired/current).

#include <algorithm>

#include "ascii_string.h"


struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "../../../Include/Lib/Coord2D.h"

class BuildListInfo
{
public:
	BuildListInfo &operator=(const BuildListInfo &that);

private:
	void *m_vtable;
	AsciiString m_buildingName;
	AsciiString m_templateName;
	Coord3D m_location;
	Coord2D m_rallyPointOffset;
	float m_angle;
	bool m_isInitiallyBuilt;
	unsigned int m_numRebuilds;
	BuildListInfo *m_nextBuildList;
	AsciiString m_script;
	int m_health;
	bool m_whiner;
	bool m_unsellable;
	bool m_repairable;
	bool m_automaticallyBuild;
	void *m_renderObj;
	void *m_shadowObj;
	bool m_selected;
	bool m_underConstruction;
	bool m_isSupplyBuilding;
	bool m_priorityBuild;
	int m_objectID;
	unsigned int m_objectTimestamp;
	int m_resourceGatherers[10];
	int m_desiredGatherers;
	int m_currentGatherers;
};

// ??$__copy_ptrs@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00U__false_type@0@@Z present-unmatched
// ??$__copy_aux@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00U__true_type@0@@Z present-unmatched
// ?_Ret@?$_BothPtrType@PAVBuildListInfo@@PAV1@@_STL@@SA?AU__true_type@2@XZ present-unmatched
// ?_Ret@?$_OKToMemCpy@VBuildListInfo@@V1@@_STL@@SA?AU__false_type@2@XZ present-unmatched
// ??$_IsOKToMemCpy@VBuildListInfo@@V1@@_STL@@YA?AU?$_OKToMemCpy@VBuildListInfo@@V1@@0@PAVBuildListInfo@@0@Z present-unmatched
template BuildListInfo *_STL::copy<BuildListInfo *, BuildListInfo *>(BuildListInfo *, BuildListInfo *, BuildListInfo *);
