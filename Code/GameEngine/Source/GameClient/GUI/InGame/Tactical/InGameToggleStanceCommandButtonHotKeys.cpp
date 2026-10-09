// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?rva00567DA6@Impl@InGameToggleStanceCommandButton@@QAEXXZ
// Retail 0x00567DA6..0x00567ECD (295 bytes).
// Registers one hotkey record per stance of the button: when the hotkey
// manager (g_00E01E28) exists it gives each 16-byte record of the vector at
// Impl +0x1C a new set-stance action (this and the button's stance i) through
// the record's reference setter; looks up the stance's hotkey string and when
// it is not empty stores addHotKey's handle and marks the record active; and
// registers the stance's associated message type as a message action.
// Evidence: WorldBuilder 0x01430B50 has the same loop calls and order and
// names the action constructor InGameToggleStanceCommandButton::Impl::
// SetStanceHotKeyAction (rowed ??0Rva0056773E 0x0056773E with this and the
// stance). It is the inverse of the rowed ~Impl (0x0056820D) which walks the
// same record vector (+0x1C; 16-byte stride; active flag +0xC; reference +8)
// unregistering the action (+0) and message and clearing the reference.
// Rowed callees: operator new 0x0002FDA0 CommandButton::getStance 0x0035B6B8
// Rva002BED91::set 0x003F8396 Rva0035B232::rva0035B232 0x0035B232
// GetAssociatedMessageType 0x00567700 HotKeyManager::addMessageAction
// 0x003597A8 StringBase<char>::releaseBuffer 0x00036410; pinned
// HotKeyManager::rva00358CCD 0x00358CCD and addHotKey 0x00359302 (views as
// in ControlBarSetCommandWindow.cpp). The method name is address-derived.
#include <vector>
#include "ascii_string.h"

class CommandButton
{
public:
	int getStance(int index);
	char m_pad00[0x234];
	_STL::vector<int> stances; // +0x234
};

class Rva0035B232
{
public:
	const AsciiString *rva0035B232(int index);
};

struct TargetRef00217D4C;
struct TreeHintRef00217D4C;

struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void set(TargetRef00217D4C *p);
};

struct Rva00359302Result
{
	Rva00359302Result(void *node, bool alternate) : m_node(node), m_alt(alternate) {}
	void *m_node;
	bool m_alt;
};

class HotKeyManager
{
public:
	AsciiString rva00358CCD(const AsciiString &name);
	Rva00359302Result addHotKey(const TreeHintRef00217D4C &action, const AsciiString &key, bool flag);
	void addMessageAction(const TreeHintRef00217D4C &action, int messageType);
};

class Rva00E01E28Owner;
extern Rva00E01E28Owner *g_00E01E28;

int GetAssociatedMessageType(int stance);

// SetStanceHotKeyAction (WorldBuilder name); rowed constructor spelling.
class Rva0056773E
{
public:
	Rva0056773E(int owner, int stance);
private:
	void *m_vtable;
	int m_ref;
	int m_owner;
	int m_stance;
};

struct StanceHotKeyRecord
{
	Rva00359302Result action; // +0x00
	Rva002BED91 ref;          // +0x08
	bool active;              // +0x0C
};

class InGameToggleStanceCommandButton
{
public:
	class Impl
	{
	public:
		void rva00567DA6();
	private:
		void *m_vtable;
		void *m_listPosition;
		void *m_owner08;
		void *m_factory0C;
		void *m_window10;
		CommandButton *m_button14;               // +0x14
		void *m_behavior18;
		_STL::vector<StanceHotKeyRecord> m_hotKeys; // +0x1C
	};
};

void InGameToggleStanceCommandButton::Impl::rva00567DA6()
{
	if (!g_00E01E28)
		return;
	int count = (int)m_button14->stances.size();
	for (int i = 0; i < count; ++i)
	{
		StanceHotKeyRecord &key = m_hotKeys[i];
		key.ref.set(reinterpret_cast<TargetRef00217D4C *>(new Rva0056773E((int)this, m_button14->getStance(i))));
		const TreeHintRef00217D4C &action = *reinterpret_cast<const TreeHintRef00217D4C *>(&key.ref);
		AsciiString hotKey = reinterpret_cast<HotKeyManager *>(g_00E01E28)->rva00358CCD(*reinterpret_cast<Rva0035B232 *>(m_button14)->rva0035B232(i));
		if (!hotKey.isEmpty())
		{
			key.action = reinterpret_cast<HotKeyManager *>(g_00E01E28)->addHotKey(action, hotKey, true);
			key.active = true;
		}
		int message = GetAssociatedMessageType(m_button14->getStance(i));
		if (message)
			reinterpret_cast<HotKeyManager *>(g_00E01E28)->addMessageAction(action, message);
	}
}
