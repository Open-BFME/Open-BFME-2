// cl: /O1
// ?rva0028BBF3@Object@@QAEXPAV1@@Z @0x0028BBF3 18B: Object holder at +0x23c forwards guardee to rowed Rva004DF2E2::rva004DF2FC tail-jmp; caller AIGuardState::onExit 0x003513A4 passes owner and guardee; neighbours share /O1
class BfmeSubBEC;
class Rva004DF2E2
{
public:
	void rva004DF2FC(BfmeSubBEC *bec);
};

class Object
{
public:
	void rva0028BBF3(Object *guardee);
private:
	char m_pad00[0x23c];
	Rva004DF2E2 *m_23c;
};

void Object::rva0028BBF3(Object *guardee)
{
	Rva004DF2E2 *holder = m_23c;
	if (holder != 0)
		holder->rva004DF2FC((BfmeSubBEC *)guardee);
}
