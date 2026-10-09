// cl: /O1 /MD
// ?IsObstaclePresent@PathfindCell@@QBE_NW4ObjectID@@@Z, retail 0x002E6C23 (42 bytes, ret 4). WorldBuilder
// PathfindCell::IsObstaclePresent (callgraph lead): whether this obstacle cell's info (+0x00) names the
// object (info +0x28). Zero Hour's isObstaclePresent, with the info null test kept as a real branch.
enum ObjectID
{
	INVALID_ID = 0
};

struct PathfindCellInfo
{
	char m_pad00[0x28];
	ObjectID m_obstacleID;		// +0x28
};

class PathfindCell
{
public:
	bool IsObstaclePresent(ObjectID id) const;

private:
	PathfindCellInfo *m_info;	// +0x00
	char m_pad04[8];
	unsigned int m_flags;		// +0x0C, type in the low four bits
};

bool PathfindCell::IsObstaclePresent(ObjectID id) const
{
	if (id != INVALID_ID && (m_flags & 0xF) == 4)
		return m_info != 0 && m_info->m_obstacleID == id;
	return false;
}
