// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native29A224..29A23E returns a full32-bit0/1 when the argument is the
// non-null radar window at1430. The command-hint caller checks the low byte.
// ZH Radar::isRadarWindow is a semantic lead; original signature remains
// unproven so preserve an address-derived member with measured int result.
class GameWindow;
class Radar {public:char pad10[0x10];bool hidden,forced;char pad12[0x1430-0x12];GameWindow *window;int rva0029A224(GameWindow *);};
int Radar::rva0029A224(GameWindow *value) { GameWindow *w=window; if(w==value && w) return 1; return 0; }
