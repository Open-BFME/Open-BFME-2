// cl: /MD
// Scalar deleting destructors that retail reaches only through vtable slots,
// so caller-based discovery never served them. They share the 28B shape
// (dtor call, flags byte test, conditional scalar delete through pinned
// ??3@YAXPAX@Z 0x0002FD60, return this), same recipe as
// VslotSmallBodiesAR.cpp. Each dtor is declared but not defined here and
// resolves through an address-derived pin in reverse/symbols.csv read from the
// wrapper's own REL32 at +4. The remaining opaque dtors are non-virtual
// here and emitted via delete anchors that are never called. The recovered
// PlayerPanelMovieClip below uses its native two-base virtual interface.
// Owner identities and layouts are not recovered; class names are the dtor
// addresses. 0x003B241A is already rowed under its own forwarder view
// (Rva003B241AForwarder.cpp), so its owner here takes a distinct name.
//  0x0044BE69 via dtor 0x0044BE85
//  0x005EB079 via named panel dtor 0x005EB095
//  0x0041E6F3 via dtor 0x003B241A
//  0x005D10BA via dtor 0x005D10D6
// (0x005D6C78 is the deleting dtor of the virtual dtor rowed in
// ChatWindowsOnlineBuddy.cpp, which emits it with its vtable.)
// The recovered virtual 0x005B4A46 destructor and its 0x005B4C7B wrapper
// now live together in Rva005B4A46Dtor.cpp.
// Camera 4E1416/4E186D now belongs to its native record in
// LivingWorldCampaignObjects.cpp.

// Dtors rowed at their addresses under other names (a virtual dtor, an ICF-folded
// setter, a dup_ body): forward through imported inlines so each deleting dtor
// calls the rowed symbol directly and no stray dtor copy is emitted.
class BfmeParserBindingBaseVE { public: virtual ~BfmeParserBindingBaseVE(); };
class Rva0005D10D6DwordImmSetter { public: void apply(); };

// ~Rva0044BE85 is defined beside its twin ~Rva00517397 (Rva00517397Dtor.cpp).
class Rva0044BE85 { public: ~Rva0044BE85(); };
#include "../../Include/Common/Rva0007DF07.h"
class Rva005FBBEE { public: virtual ~Rva005FBBEE(); };
struct EmitPlayerPanelTableTag;
namespace StrategicInGameUI {
class DynamicAutoResolveDialog { public: class Impl; };
class DynamicAutoResolveDialog::Impl { public: class PlayerPanelMovieClip; };
class DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip : public Rva0007DF07, public Rva005FBBEE {
public:
    PlayerPanelMovieClip(EmitPlayerPanelTableTag *);
    virtual ~PlayerPanelMovieClip();
};
// ?PlayerPanelMovieClip::PlayerPanelMovieClip absent-from-retail
DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::PlayerPanelMovieClip(EmitPlayerPanelTableTag *) {}
}
class Rva003B241AOwner { public: __declspec(dllimport) __forceinline ~Rva003B241AOwner() { reinterpret_cast<BfmeParserBindingBaseVE *>(this)->BfmeParserBindingBaseVE::~BfmeParserBindingBaseVE(); } };
class Rva005D10D6 { public: __declspec(dllimport) __forceinline ~Rva005D10D6() { reinterpret_cast<Rva0005D10D6DwordImmSetter *>(this)->apply(); } };

#include <new>

void Rva0044BE85_DeleteAnchor(Rva0044BE85 *m_objectToDelete) { delete m_objectToDelete; }
void Rva003B241AOwner_DeleteAnchor(Rva003B241AOwner *m_objectToDelete) { delete m_objectToDelete; }
void Rva005D10D6_DeleteAnchor(Rva005D10D6 *m_objectToDelete) { delete m_objectToDelete; }
