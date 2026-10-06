// cl: /DNDEBUG /MD /EHsc
// ?leaveGroup@Object@@QAEXXZ @0x0028C01F 24B
// Object::leaveGroup: if m_group at +0x1A8, clear it before AIGroup::remove(this) to avoid recursion.
// Evidence: pinned name; rowed callee AIGroup::remove 0x0036CF07; 26 callers incl AIGroup::remove itself;
// donor BFME1 Object.cpp:7182 and ZH Object.cpp:6320 use 0x188, BFME2 retail uses 0x1A8.
class Object;

class AIGroup
{
public:
	bool remove(Object *member);
};

class Object
{
public:
	void leaveGroup();

private:
	unsigned char m_pad[0x1A8];
	AIGroup *m_group; // +0x1A8
};

void Object::leaveGroup()
{
	if (m_group)
	{
		AIGroup *group = m_group;
		m_group = 0;
		group->remove(this);
	}
}
