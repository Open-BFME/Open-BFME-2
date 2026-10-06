// cl: /MD /EHsc /DNDEBUG
// Reference-guided: clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76
// game/GameEngine/Source/GameClient/CameraPath_dtor.cpp,
// compiled with BFME2 settings; donor semantics kept separately from target facts.
// Target101B8990C/88B89971 are Ghidra bounded. Array iterator callbacks
// establish 255/4 owning20B elements at2C/1418; initialized end1468 is not
// full size. EH parent75FB68/FuncInfo90276C/two-state map90275C associates
// real base and first-array cleanup actions. Original identities unknown.
// Retail has no derived entry vptr store here; preserve the base restore.
#define BFME_ARRAY_OWNER_ATTRIBUTES __declspec(novtable)
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

Rva0089971::~Rva0089971() {}
