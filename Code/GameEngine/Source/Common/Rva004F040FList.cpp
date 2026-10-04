// cl: /O1 /Ob0
// ?rva004F040F@Rva004F040F@@QAEXPAX@Z @0x004F040F 32B list check-then-remove.
// Evidence: calls isInList04 0x004F0341 then rva004F0372 0x004F0372 with this+4 as head; unblocks 0x004F042F/0x004F0819/0x004F1653; prev/next share list-node +4/+8; ret 4 one void* arg.
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
	void rva004F040F(void *arg);
	void rva004F0479(void *arg);
	void rva004F03EF(void *arg);
	void rva004EF383(void *arg);

private:
	char m_pad00[4];
	void *m_04;
	void *m_08;
};

void Rva004F040F::rva004F040F(void *arg)
{
	void **head = &m_04;
	if (((BfmeNode_00161220 *)arg)->isInList04((BfmeNode_00161220 **)head))
		((Rva00160530 *)arg)->rva004F0372((Rva00160530 **)head);
}


// Whole verified BFME1 donor contexts AIPlayerQueueTeardown.cpp,
// AIPlayerSelectTeamToReinforce.cpp and AIPlayer.cpp at1281192 supply
// the two intrusive-list queue protocol. Native Ghidra32-byte entries
// independently prove each condition, head offset, both call destinations
// and RET4 ABI. Existing4F040F remains exact. Receiver original names
// and full layouts remain unknown; no unverified class identity is added.
// Native4F0490 in4F0479 calls the now-verified linked4F03AF/48 with
// node receiver and head-pointer argument; this existing node declaration
// is only that call ABI, bound to its proper TeamInQueue home.
#pragma comment(linker, "/alternatename:?rva004F03AF@BfmeNode_00161220@@QAEXPAPAU1@@Z=?dlink_removeFrom_TeamReadyQueue@TeamInQueue@@QAEXPAPAV1@@Z")

// Native4EF39A calls the independently byte-verified/link-clean23-byte
// second-list prepend4EF35C with its node receiver and supplied head.
// This declaration adds no receiver layout or original type claim.
class Rva004EF35CAppendABI
{
public:
    void prepend(void **head);
};
#pragma comment(linker, "/alternatename:?prepend@Rva004EF35CAppendABI@@QAEXPAPAX@Z=?set@Rva00160620@@QAEXPAPAV1@@Z")

void Rva004F040F::rva004F0479(void *arg)
{
    void **head = &m_08;
    if (((BfmeNode_00161220 *)arg)->isInList0C((BfmeNode_00161220 **)head))
        ((BfmeNode_00161220 *)arg)->rva004F03AF((BfmeNode_00161220 **)head);
}

void Rva004F040F::rva004F03EF(void *arg)
{
    void **head = &m_04;
    if (!((BfmeNode_00161220 *)arg)->isInList04((BfmeNode_00161220 **)head))
        ((Rva00160530 *)arg)->set((Rva00160530 **)head);
}

void Rva004F040F::rva004EF383(void *arg)
{
    void **head = &m_08;
    if (!((BfmeNode_00161220 *)arg)->isInList0C((BfmeNode_00161220 **)head))
        ((Rva004EF35CAppendABI *)arg)->prepend(head);
}
