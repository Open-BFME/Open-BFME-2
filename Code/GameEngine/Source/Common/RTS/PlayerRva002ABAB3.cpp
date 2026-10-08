// cl: /DNDEBUG /MD /EHsc
// ?rva002ABAB3@Player@@QAEXXZ @0x002ABAB3 (13B): Player ecx pass-through to iterateObjects with callback at 0x002AA27A and NULL userdata.
// Evidence: push 0 then push 0x6aa27a then call pinned Player::iterateObjects @0x002AB08B; 13B push-push-call-ret matches void Player method with no args; sibling PlayerRva002ABAA6 @0x002ABAA6 same shape with callback 0x002AA264.
class Object;
typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
	void rva002ABAB3();
};

// The iterateObjects callback at 0x002AA27A (24B): it hands 2 and each object's
// +0x74 field to TheAiOrdersManager (global 0x00A01E18, registered as
// "TheAiOrdersManager") and returns 1 to keep iterating.
class AiOrdersManager
{
public:
	void rva00355183(int a, int b);
};

extern AiOrdersManager *TheAiOrdersManager;

// The object field at +0x74 is what the callee looks up through 0x0035516C.
struct Rva002AA27AObject
{
	char m_pad[0x74];
	int m_74;
};

int __cdecl Rva002AA27A(Object *obj, void *userData)
{
	TheAiOrdersManager->rva00355183(2, ((Rva002AA27AObject *)obj)->m_74);
	return 1;
}

void Player::rva002ABAB3()
{
	iterateObjects((ObjectIterateFunc)Rva002AA27A, 0);
}
