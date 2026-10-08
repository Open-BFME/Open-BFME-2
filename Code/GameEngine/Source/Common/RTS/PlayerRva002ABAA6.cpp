// cl: /DNDEBUG /MD /EHsc
// ?rva002ABAA6@Player@@QAEXXZ @0x002ABAA6 (13B): Player ecx pass-through to iterateObjects with callback at 0x002AA264 and NULL userdata.
// Evidence: push 0 then push 0x6aa264 then call pinned Player::iterateObjects @0x002AB08B; 13B push-push-call-ret matches void Player method with no args; neighbours PlayerRva002ABD1D and PlayerRva002ABCF0 use same ecx pass-through recipe.
class Object;
typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
	void rva002ABAA6();
};

// The iterateObjects callback at 0x002AA264 (22B): it hands each object's +0x74
// field to TheAiOrdersManager (global 0x00A01E18, registered as
// "TheAiOrdersManager") and returns 1 to keep iterating.
class AiOrdersManager
{
public:
	void rva0035519E(int value);
};

extern AiOrdersManager *TheAiOrdersManager;

// The object field at +0x74 is what the callee looks up through 0x0035516C.
struct Rva002AA264Object
{
	char m_pad[0x74];
	int m_74;
};

int __cdecl Rva002AA264(Object *obj, void *userData)
{
	TheAiOrdersManager->rva0035519E(((Rva002AA264Object *)obj)->m_74);
	return 1;
}

void Player::rva002ABAA6()
{
	iterateObjects((ObjectIterateFunc)Rva002AA264, 0);
}
