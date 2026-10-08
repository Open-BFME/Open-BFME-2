// cl: /O1 /DNDEBUG /MD
//
// ?rva002C5FBA@Rva002C5FBA@@QAEPAXH@Z retail 0x002C5FBA (17 B), the pin
// name its caller 0x004E955F uses. Target evidence: a null target chooser at
// +0x0C gives 0; otherwise tail-jumps to the rowed
// AITargetChooser::rva00505408 with the index. Owner address-named.
class Rva002C589B;

class AITargetChooser
{
public:
	Rva002C589B *rva00505408(int index);		// 0x00505408
};

class Rva002C5FBA
{
public:
	void *rva002C5FBA(int index);

private:
	unsigned char m_pad[0xC];
	AITargetChooser *m_chooser;			// +0x0C
};

void *Rva002C5FBA::rva002C5FBA(int index)
{
	if (m_chooser)
		return m_chooser->rva00505408(index);
	return 0;
}
