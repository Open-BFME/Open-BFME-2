// cl: /Ireference/shims/bfme2_ascii /MD
// Range-27 string reset and command-set update.
// ?Rva00529E19@Holder00529E19@@QAEXXZ @0x00529E19 34B
// ?Rva00529DA9@Holder00529E19@@QAEXH@Z @0x00529DA9 112B
// The 34B reset stashes m_30, clears it, releases m_34, clears m_2C, and
// calls the 112B method with the stashed ID. The latter resolves that ID
// through TheGameLogic, selects Object::rva00290E67's AsciiString (or the
// observed fallback VA 0x00DE0878), avoids a repeat when flag/ID/name match,
// then resets the holder, copies the name, sets the flag and clears six slots.
// Target evidence: this+0x2C/+0x30/+0x34, direct calls and the six-iteration
// loop. The address-derived holder identity is supported by the 0x00529E19
// call site; helper class views remain address-derived.
#include "ascii_string.h"

class Object;
// Zero Hour's GameCommon.h spells the id an enum; retail's 0x00049DC5 row takes it.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class Rva00528F30Target
{
public:
	void reset();
};
class Rva0052936C
{
public:
	void rva005294FC(int index);
};

struct Holder00529E19
{
	char m_pad[0x2C];
	unsigned char m_2C;
	char m_pad2D[3];
	int m_30;
	StringBase<char> m_34;
	void Rva00529DA9(int value);
	void Rva00529E19();
};

void Holder00529E19::Rva00529E19()
{
	int tmp = m_30;
	m_30 = 0;
	m_34.clear();
	m_2C = 0;
	Rva00529DA9(tmp);
}

void Holder00529E19::Rva00529DA9(int value)
{
	Object *object = TheGameLogic->findObjectByID((ObjectID)value);
	const AsciiString *name = object != NULL
		? object->rva00290E67()
		: &AsciiString::TheEmptyString;
	if (m_2C != 0 && value == m_30 && name->compare((const AsciiString &)m_34) == 0)
		return;
	((Rva00528F30Target *)this)->reset();
	m_30 = value;
	m_34.set(*(const StringBase<char> *)name);
	m_2C = 1;
	for (int i = 0; i < 6; ++i)
		((Rva0052936C *)this)->rva005294FC(i);
}
