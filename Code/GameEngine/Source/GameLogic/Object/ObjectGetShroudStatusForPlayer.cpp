// cl: /MD
//
// ?getShroudStatusForPlayer@Object@@QBE?AW4CellShroudStatus@@H@Z @0x0028D2A2 (35B).
// Object shroud gate: when the PartitionData at +0x4C4 is missing or the
// template byte at +0x10E carries 0x20, returns CELLSHROUD_FOGGED (1);
// otherwise tail-calls PartitionData::getShroudedStatus with the same player
// index. Retail shape is mov eax,ecx plus helper null test plus template flag
// test plus tail jmp, else xor/inc. Pinned name and callee pin from packet;
// layout from retail immediates and sibling Object TUs; no donor.

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
	CELLSHROUD_COUNT
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED,
	OBJECTSHROUD_COUNT
};

struct ObjectTemplate
{
	unsigned char m_pad[0x10E];
	unsigned char m_byte10E;
};

class PartitionData
{
public:
	ObjectShroudStatus getShroudedStatus(int playerIndex);
};

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;

private:
	char m_pad00[4];
	ObjectTemplate *m_template;
	char m_pad08[0x4C4 - 8];
	PartitionData *m_partition;
};

CellShroudStatus Object::getShroudStatusForPlayer(int playerIndex) const
{
	if (m_partition == 0)
		return CELLSHROUD_FOGGED;
	if ((m_template->m_byte10E & 0x20) == 0)
		return (CellShroudStatus)m_partition->getShroudedStatus(playerIndex);
	return CELLSHROUD_FOGGED;
}
