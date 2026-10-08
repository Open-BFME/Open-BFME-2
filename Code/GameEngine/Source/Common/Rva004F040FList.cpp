// cl: /Ob0
// The 32B list check-then-remove at 0x004F040F is rowed as
// AIPlayer::removeFrom_TeamBuildQueue in AIPlayerTeamQueues.cpp.
typedef bool Bool;

struct BfmeNode_00161220
{
	void *m_vptr;
	BfmeNode_00161220 *m_next04;
	BfmeNode_00161220 *m_previous08;
	BfmeNode_00161220 *m_next0C;
	BfmeNode_00161220 *m_previous10;

	Bool isInList04(BfmeNode_00161220 **head) const;
	Bool isInList0C(BfmeNode_00161220 **head) const;
	void rva004F03AF(BfmeNode_00161220 **head);
};

class Rva00160530
{
	Rva00160530 *m_00;
	Rva00160530 *m_04;
	Rva00160530 *m_08;

public:
	void rva004F0372(Rva00160530 **p);
	void set(Rva00160530 **p);
};

class Rva004F040F
{
public:
	void rva004EF383(void *arg);

private:
	char m_pad00[4];
	void *m_04;
	void *m_08;
};


// Native4EF39A calls the independently byte-verified/link-clean23-byte
// second-list prepend4EF35C with its node receiver and supplied head.
// This declaration adds no receiver layout or original type claim.
class Rva004EF35CAppendABI
{
public:
    void prepend(void **head);
};
// The membership test and the link are the rowed
// TeamInQueue::dlink_isInList_TeamReadyQueue and Rva00160620::set.
class TeamInQueue
{
public:
	Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *head) const;
};
class Rva00160620
{
public:
	void set(Rva00160620 **head);
};

void Rva004F040F::rva004EF383(void *arg)
{
    void **head = &m_08;
    if (!((const TeamInQueue *)arg)->dlink_isInList_TeamReadyQueue((TeamInQueue *const *)head))
        ((Rva00160620 *)arg)->set((Rva00160620 **)head);
}
