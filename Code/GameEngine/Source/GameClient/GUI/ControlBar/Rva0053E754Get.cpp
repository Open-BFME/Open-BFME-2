// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?Rva0053E754Get@@YGPAVObject@@H@Z @0x0053E754 47B
// Free __stdcall lookup: scan 32-entry table at g_00E05E20 for id then GameLogic findObjectByID. Evidence: rowed findObjectByID 0x00049DC5; global TheGameLogic; caller 0x00328700; neighbour ControlBarUpdateConstruction pattern.
class Object;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
struct Rva0053E754Entry
{
	int m_id;
	int m_mapped;
};
extern Rva0053E754Entry g_00E05E20[32];
Object * __stdcall Rva0053E754Get(int id)
{
	int mapped = 0;
	for (int i = 0; i < 0x20; ++i) {
		if (g_00E05E20[i].m_id == id) {
			mapped = g_00E05E20[i].m_mapped;
			break;
		}
	}
	return TheGameLogic->findObjectByID((ObjectID)mapped);
}
