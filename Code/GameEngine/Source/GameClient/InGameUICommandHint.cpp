// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native29A224..29A23E returns a full32-bit0/1 when the argument is the
// non-null radar window at1430. The command-hint caller checks the low byte.
// Named from ZH Radar::isRadarWindow (same compare, called from the command
// hint as in ZH InGameUI); keeps the measured int result.
class GameWindow;
#include "../../Include/Common/Radar.h"
int Radar::isRadarWindow(GameWindow *value) { GameWindow *gameWindow=m_radarWindow; if(gameWindow==value && gameWindow) return 1; return 0; }
