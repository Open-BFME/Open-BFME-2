// cl: /O1 /MD /Ireference/shims/bfme2_ascii
// PlayerAITypeSet::PlayerAITypeSet, native 0x0022E156..0x0022E177 (33B).
// Identity: byte-verified GameEngine::init allocates 0x18 bytes, calls this
// target and registers ThePlayerAITypeSet through its named subsystem slot.
// Target layout: SubsystemInterface ctor 0x1B4E63, derived vptr 0xBE77B0,
// empty vector header at +0x0C; the vector-base helper is 0x211E58 (29B).
// Semantic reference: Open-BFME-1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c,
// game/GameEngine/Source/Common/PlayerAITypeSetFind.cpp. Its 16-byte entry
// view (AsciiString then 12 opaque bytes) is donor-derived; this constructor
// proves only the empty header, not the target entries' contents or stride.
// BFME2's base grows from donor +8 to +0xC, corroborated by native allocation
// and the explicit member address. The vector fields are never dereferenced
// here. /O1 /MD with no EH option matches the verified RankInfoStore sibling;
// enabling EH introduces cleanup states that are absent from this boundary.
// stlport
#include <vector>
#include "ascii_string.h"
struct PlayerAITypeEntry { AsciiString name; char unknown[12]; };
// Bind the base initialization to its existing C++ owner. The inline bridge
// is the same source pattern as the verified RankInfoStore constructor.
class BFME2NativeNetwork { public: void baseConstruct(); };
class __declspec(novtable) PlayerAITypeSetBase {
public:
 PlayerAITypeSetBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
 virtual ~PlayerAITypeSetBase();
private:
 unsigned char m_04;
 int m_08;
};
class PlayerAITypeSet : public PlayerAITypeSetBase {
public:
 PlayerAITypeSet();
 virtual ~PlayerAITypeSet();
private:
 _STL::vector<PlayerAITypeEntry> m_types;
};
PlayerAITypeSet::PlayerAITypeSet() {}
