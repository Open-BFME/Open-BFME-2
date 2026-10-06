// cl: /O1 /DNDEBUG /MD
// ?rva003460DB@@YA_NPAVObject@@@Z @0x003460DB 81B.
// Cdecl bool gate (single object arg, frameless). Target facts: false when
// the +0x25C slot is set and its rowed check 0x00390533 holds, when byte
// +0x10E of the +0x4 record has bit 0x40, when rowed Object 0x0028F518 holds,
// or when status 0xF is set without status 0x11; true otherwise. Status
// values are the raw indices passed to the rowed testStatus; their names are
// not established.
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
	if (b->m_slot25C && b->m_slot25C->rva00390533())
		return false;
	if ((((Rva003460DBFlags *)b->m_p4)->m_pad[0x10E] & 0x40) != 0 || b->rva0028F518())
		return false;
	if (b->testStatus(OBJECT_STATUS_0F))
	{
		if (!b->testStatus(OBJECT_STATUS_11))
			return false;
	}
	return true;
}
