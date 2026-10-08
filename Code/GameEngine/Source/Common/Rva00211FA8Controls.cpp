// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native 610DB6..610DC9 (19B) ends in RET before the next entry.
// WorldBuilder B5EBA0 independently repeats the GameLogic reset with
// (true,false) and callback result 3. Its original name remains unknown.
// The owning callback impl at BE5128 invokes its stored cdecl function
// through 611216: it loads the first argument with FLD and forwards the
// second flag. Both arguments are unused here.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

int rva00210DB6(float, bool)
{
    TheGameLogic->rva00376E92(true, false);
    return 3;
}

