// cl: /O1 /G7 /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// BF1 f989 multilist.h structural candidate, not a target template identity.
// Native 6EF7D calls Internal_Remove_List_Head6109A0 then preserves null
// while adjusting a nonnull result -8. The concrete payload remains unknown.
#include "../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

// ?bfmeAnchorMultiListRenderObjRemoveHead absent-from-retail
RenderObjClass *bfmeAnchorMultiListRenderObjRemoveHead(MultiListClass<RenderObjClass> *p)
{
	return p->Remove_Head();
}
