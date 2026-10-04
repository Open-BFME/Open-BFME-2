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
};

class Rva00160530
{
	Rva00160530 *m_00;
	Rva00160530 *m_04;
	Rva00160530 *m_08;

public:
	void rva004F0372(Rva00160530 **p);
};

class Rva004F040F
{
public:
	void rva004F040F(void *arg);

private:
	char m_pad00[4];
	void *m_04;
};

void Rva004F040F::rva004F040F(void *arg)
{
	void **head = &m_04;
	if (((BfmeNode_00161220 *)arg)->isInList04((BfmeNode_00161220 **)head))
		((Rva00160530 *)arg)->rva004F0372((Rva00160530 **)head);
}
