// cl: /O1 /DNDEBUG /MD
// HotKey.cpp -- HotKeyManager members at their WorldBuilder home
// (reverse/wb_name_leads.csv: WB's debug build names the file and method and
// asserts action.IsBound() and that the message type is not yet mapped);
// retail supplies the bytes.
//
// Layout (target evidence): the message-action map at +0x24, whose
// operator[] (0x003596AD, unrowed) yields the reference-counted action
// handle that the rowed handle assignment 0x002174A4 overwrites.

typedef int Int;

// The reference-counted action handle (rowed under this address name).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &that);	// 0x002174A4

	void *m_node;
};

// View of the STLport map from message type to action handle.
class HotKeyMessageActionMap
{
public:
	TreeHintRef00217D4C &operator[](const Int &messageType);		// 0x003596AD

private:
	unsigned char m_data[0xc];
};

class HotKeyManager
{
public:
	void addMessageAction(const TreeHintRef00217D4C &action, Int messageType);

private:
	unsigned char m_pad00[0x24];
	HotKeyMessageActionMap m_messageActionMap;		// +0x24
};

// HotKeyManager::addMessageAction, retail 0x003597A8 (27 bytes): the action
// is bound to the message type.
void HotKeyManager::addMessageAction(const TreeHintRef00217D4C &action, Int messageType)
{
	m_messageActionMap[messageType] = action;
}
