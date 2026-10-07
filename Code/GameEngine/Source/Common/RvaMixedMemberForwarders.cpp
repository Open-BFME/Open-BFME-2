// cl: /DNDEBUG /MD
//
// Member forwarders, address-named except where an existing pin already
// spells the forwarder (those spellings are followed):
// 18B null-checked pointer forwarders (VslotNullCheckedForwarders.cpp shape,
// ret N gives the argument count):
//   0x00271BCC +0x450 -> 0x003626AD (2 args; pinned Rva00271BCC spelling)
//   0x0029B16A +0x7F4 -> 0x004E5EBE (2 args)
//   0x002A9CDE +0x2DC -> 0x004F2ABC (2 args)
//   0x002A9CF0 +0x2DC -> 0x004F0819 (1 arg)
//   0x002A9DEC +0x2DC -> 0x004F2C14 (1 arg; pinned Rva002A9BF2 spelling)
// add ecx N / jmp embedded-member forwarders:
//   0x0028BC4D Object +0x330 -> rowed ?rva002C7474@Rva002C7474@@QAEXXZ (pinned spelling)
//   0x004EC072 +0x90 -> rowed ?rva0059A71C@Rva0059A71C@@QAEXPAUArg@@@Z
//   0x004EC07D +0x90 -> 0x0059A153 (pinned Rva002A8AB1Record spelling)
// Rva002A8AB1Record::rva004EC088 (0x004EC088, 49 bytes) picks a member by
// kind: 0 asks the builder at +4 (rowed AIBaseBuilder 0x00506BF7), 1 the
// member at +0x38 (rowed 0x005748B2), others return null. Its caller
// AIPlayer::startTraining 0x004F20C2 passes kind 1, a team's member list and
// the template name, and pushes a non-null result onto that list.
//   0x0023D0B7 GameLogic +0x184 -> 0x0040D3FF (pinned GameLogic spelling)
// Unrowed jump targets arrive as address-derived pins.

typedef int Int;
class Rva003626ADNullTarget
{
public:
	void rva003626AD(Int a0, Int a1);
};

class Rva00271BCC
{
public:
	void rva00271BCC(Int a0, Int a1);
private:
	char m_lead[0x450];
	Rva003626ADNullTarget *m_member;
};

void Rva00271BCC::rva00271BCC(Int a0, Int a1)
{
	if (m_member)
		m_member->rva003626AD(a0, a1);
}

class Rva004F2C14NullTarget
{
public:
	void rva004F2C14(Int a0);
};

class Rva002A9BF2
{
public:
	void rva002A9DEC(Int a0);
private:
	char m_lead[0x2DC];
	Rva004F2C14NullTarget *m_member;
};


class Rva002C7474
{
public:
	void rva002C7474();
};

class Object
{
public:
	void rva0028BC4D();
private:
	char m_lead[0x330];
	Rva002C7474 m_member;
};

void Object::rva0028BC4D()
{
	m_member.rva002C7474();
}

struct Arg;

class Rva0059A71C
{
public:
	void rva0059A71C(Arg *arg);
};

class TeamPrototype;

class Rva0059A153
{
public:
	void rva0059A153(TeamPrototype *proto);
};

class Rva005AD9C0Hit;
class AIBaseBuilder
{
public:
	Rva005AD9C0Hit *rva00506BF7(void *arg);
};

class Rva005748B2
{
public:
	int rva005748B2(int a, int b);
};

class Rva002A8AB1Record
{
public:
	void rva004EC07D(TeamPrototype *proto);
	void *rva004EC088(Int kind, void *list, const void *name);
private:
	char m_lead[0x90];
	Rva0059A153 m_member;
};

void Rva002A8AB1Record::rva004EC07D(TeamPrototype *proto)
{
	m_member.rva0059A153(proto);
}

void *Rva002A8AB1Record::rva004EC088(Int kind, void *list, const void *name)
{
	switch (kind)
	{
	case 0:
		return ((AIBaseBuilder *)(m_lead + 4))->rva00506BF7(list);
	case 1:
		return (void *)((Rva005748B2 *)(m_lead + 0x38))->rva005748B2((int)list, (int)name);
	}
	return 0;
}

class Rva0040D3FF
{
public:
	int rva0040D3FF();
};

class GameLogic
{
public:
	int rva0023D0B7();
private:
	char m_lead[0x184];
	Rva0040D3FF m_member;
};

int GameLogic::rva0023D0B7()
{
	return m_member.rva0040D3FF();
}
