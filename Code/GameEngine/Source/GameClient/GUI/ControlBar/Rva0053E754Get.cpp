// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native53E754..53E783 RET4; the330B button callback328700 passes this=TheControlBar
// and a GameWindow stack argument. The previous free stdcall signature omitted
// that witnessed receiver. Retail ignores this and scans the32 global window/ID
// pairs before calling the canonical GameLogic provider. Name remains neutral.
class Object;
class GameWindow;
enum ObjectID { INVALID_OBJECT_ID=0 };
class GameLogic {public:Object *findObjectByID(ObjectID);};
extern GameLogic *TheGameLogic;
struct Rva0053E754Entry { GameWindow *m_window; int m_mapped; };
extern Rva0053E754Entry g_00E05E20[32];
class ControlBar {public:Object *rva0053E754(GameWindow *);};
Object *ControlBar::rva0053E754(GameWindow *window)
{
 int mapped=0;
 for(int i=0;i<32;++i) {
  if(g_00E05E20[i].m_window==window) { mapped=g_00E05E20[i].m_mapped;break; }
 }
 return TheGameLogic->findObjectByID((ObjectID)mapped);
}
