// cl: /DNDEBUG /MD /EHsc
//
// ??1AIGateUpdate@@UAE@XZ, retail 0x004B0802, 116 bytes (pinned; rowed
// deleting wrapper 0x004B0926). Stores the three vtables, then
// in EH state 0 looks up the node registered under the ID at +0x24 through
// the rowed Rva002E36D5Find, and when found unlinks it (0x002E3714), passes
// it to the rowed Rva0023D661::rva0023D661 on the global at 0x00DFE78C and
// deletes it through its slot-0 destructor. Last comes the opaque MI base
// dtor 0x0024A797, the only entry in retail's unwind map. Base layout as in
// Rva0024A797Derived.cpp. The same find/unlink/notify/delete sequence
// recurs at 0x00397E6E and 0x004EB61A.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_INVALID = 0 };

struct Rva002E36D5Node
{
	virtual ~Rva002E36D5Node();
	unsigned char m_pad[0x3C - 4];
	Rva002E36D5Node *m_next3C;
};

void *Rva002E36D5Find(int id);
void Rva002E3714Unlink(Rva002E36D5Node *node);

class Rva0023D661
{
public:
	void rva0023D661(int val);
};

class GameLogic;
class GateOpener;
extern GameLogic *TheGameLogic;

class AIGateUpdate : public UpdateModule
{
public:
	virtual ~AIGateUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
private:
	GateOpener *m_opener;
	unsigned m_24;
};

AIGateUpdate::~AIGateUpdate()
{
	Rva002E36D5Node *node = (Rva002E36D5Node *)Rva002E36D5Find(m_24);
	if (node) {
		Rva002E3714Unlink(node);
		((Rva0023D661 *)TheGameLogic)->rva0023D661((int)node);
		::delete node;
	}
}
// ?g_009FE78C@@3PAVRva0023D661@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
