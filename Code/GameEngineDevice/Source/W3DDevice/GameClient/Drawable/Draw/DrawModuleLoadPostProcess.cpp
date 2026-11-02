// Existing W3DLaserDraw post-load directly calls B3FD0. ZH base hook
// is empty; one-byte RET is a genuine relocation-free folded body.
// cl: /O1 /G7 /arch:SSE /MD
class Thing;class ModuleData;class Drawable;class Xfer;
#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"
void DrawModule::loadPostProcess(){}
