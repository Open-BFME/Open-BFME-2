// cl: /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Clean constructor lead: Open-BFME-1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/GameEngine/Source/Common/Rva00943650OwnerCtor.cpp, BF1 RVA 0x00943650.
// Target 0x00141830..0x0014185A: scene-array callback, 28-byte stride in
// BfmeSceneVector::Set_Level (0x00142060); its element destructor (0x00141CA0)
// destroys the non-ref scene list at +4. Retail's vtable is RVA 0x007D33B8,
// owned by BfmeNonRefSceneList_dtor.cpp, not the donor RenderObj list template.
// Retain the existing neutral Rva00141D00 owner; the original element name
// and the purpose of its leading integer remain unknown.
// multilist.h's inline members are retail's size-optimised bodies: compile
// them for size (as hlod.cpp/decalsys.cpp do) so this unit's copies match.
#pragma optimize("s", on)
#include "multilist.h"
#pragma optimize("", on)
#include "multilist.h"

class BfmeNonRefSceneList : public GenericMultiListClass
{
public:
    virtual ~BfmeNonRefSceneList();
};

#include "../../../../GameEngine/Include/Common/Rva00141D00.h"

typedef char SceneListElementSize[(sizeof(Rva00141D00) == 0x1c) ? 1 : -1];

Rva00141D00::Rva00141D00() : m_0(0)
{
}
