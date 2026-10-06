// ?rva003460DB@@YA_NPAVObject@@@Z
// partial score=0.975 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva003460DB@@YA_NPAVObject@@@Z @0x003460DB 81B.
// Cdecl bool gate (single object arg, frameless): returns true on a set
// slot flag-pair, a set +0x10E quirk, a set object chain bit, or a failed
// status/flag pair; false only when the 0x11 status holds while 0xF does
// not. All callees rowed; the slot check uses an address-derived pin.
class Object;

enum ObjectStatusTypes
{
	OBJECT_STATUS_0F = 0xF,
	OBJECT_STATUS_11 = 0x11
};

struct Rva00390533
{
	bool rva00390533();
};

struct Rva003460DBFlags
{
	char m_pad[0x10F];
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	bool rva0028F518();

	char m_pad00[4];
	Rva003460DBFlags *m_p4;
	char m_pad08[0x25C - 0x8];
	Rva00390533 *m_slot25C;
};

bool rva003460DB(Object *b)
{
	Rva00390533 *slot = b->m_slot25C;
	if (slot == 0)
		goto checks;
	if (slot->rva00390533())
		goto fail;
checks:
	if ((((Rva003460DBFlags *)b->m_p4)->m_pad[0x10E] & 0x40) != 0)
		goto fail;
	if (!b->rva0028F518())
		goto success;
	if (b->testStatus(OBJECT_STATUS_0F) || !b->testStatus(OBJECT_STATUS_11))
		goto fail;
success:
	return true;
fail:
	return false;
}
