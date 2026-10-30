// cl: /DBFME_ASCII_DTOR_DECL /GX /MD /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common
// stlport
//
// ??0WallHubBehaviorModuleData@@QAE@XZ, retail 0x00453020, 148 bytes.
// ModuleData-side ctor in the WallHub file-unit: the segment template name
// vector at +8 builds through the AsciiString Vector_base alias (0x211E58)
// and is cleared, the six template-name strings at +14/+18/+1C/+20/+24/+28
// zero-init inline with declared clear/dtor folding to 0x36410 (only
// +14/+18 call clear in the body; all six plus the base plus the vector
// drive the EH states to the retail state-7 before the erase), BuilderRadius
// at +2C defaults to the 9.876 pool float, MaxBuildoutDistance at +30 to the
// 54321.0 pool float, Options at +34 is 0, StaggeredBuildFactor at +38 is 5.
// Table 0xC3FED8 carries all eleven fields at these offsets; factory
// 0x24A94C news 0x3C with this ctor as sole caller (pinned).
// The ModuleData base and typed members drive the EH frame. Body stores
// clear names first, then set the radius, options, factor and distance.

// 0x24A94C news 0x3C with this ctor as sole caller (pinned). Shape follows
// PassiveAreaEffect (empty UpdateModuleData base with declared-only dtor
// driving the EH frame, explicit vtable first member, implicit member init
// in decl order, body in retail order: clears first, then the radius,
// options, factor and distance stores).
#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
}

#include "Common/Snapshot.h"

#include "BfmeModuleData.h"
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

class WallHubBehaviorModuleData : public ModuleData
{
public:
	WallHubBehaviorModuleData();
	virtual ~WallHubBehaviorModuleData();
	virtual bool slot06() const { return true; }

private:
	friend class WallHubBehavior;

	unsigned char m_pad04[4]; // +0x04
	_STL::vector<AsciiString> m_segmentTemplateNames; // +0x08
	AsciiString m_hubCapTemplateName; // +0x14
	AsciiString m_defaultSegmentTemplateName; // +0x18
	AsciiString m_cliffCapTemplateName; // +0x1C
	AsciiString m_shoreCapTemplateName; // +0x20
	AsciiString m_borderCapTemplateName; // +0x24
	AsciiString m_elevatedSegmentTemplateName; // +0x28
	float m_builderRadius; // +0x2C
	float m_maxBuildoutDistance; // +0x30
	int m_options; // +0x34
	int m_staggeredBuildFactor; // +0x38
};

// ??0WallHubBehaviorModuleData@@QAE@XZ @0x453020
WallHubBehaviorModuleData::WallHubBehaviorModuleData()
{
	m_segmentTemplateNames.clear();
	m_hubCapTemplateName.clear();
	m_defaultSegmentTemplateName.clear();
	m_builderRadius = 9.876f;
	m_options = 0;
	m_staggeredBuildFactor = 5;
	m_maxBuildoutDistance = 54321.0f;
}
