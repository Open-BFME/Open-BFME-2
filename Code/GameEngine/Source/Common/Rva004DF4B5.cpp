// cl: /O1 /MD
// ?rva004DF4B5@Rva004DF4B5@@QAEXPAX@Z @0x004DF4B5 32B: if arg non-null take ObjectID at +0x74 and push_back into list at +0x24 via rowed BridgeBehaviorObjectIDList::push_back; caller 0x0028BC0F unblocks 0x0028BC05; neighbours share layout
enum ObjectID
{
	OBJECTID_INVALID = 0
};

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_prev;
	ObjectID m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &value);
	BridgeBehaviorObjectIDNode *m_node;
};

struct Rva004DF4B5Arg
{
	char m_pad00[0x74];
	ObjectID m_74;
};

class Rva004DF4B5
{
public:
	void rva004DF4B5(void *p);
private:
	char m_pad00[0x24];
	BridgeBehaviorObjectIDList m_24;
};

void Rva004DF4B5::rva004DF4B5(void *p)
{
	if (p == 0)
		return;
	ObjectID tmp = ((Rva004DF4B5Arg *)p)->m_74;
	m_24.push_back(tmp);
}
