// cl: /DNDEBUG /MD
// ?rva0057E9ED@Rva0057E97A@@QAEXIH@Z @0x0057E9ED 34B
// Bounded store to the +0xB4 int vector of the Rva0057E97A window holder:
// size is (finish-start)/4 via sub+sar, index in [esp+4] checked against it,
// then start[index] = value in [esp+8]. Same class and flags as the neighbour
// 0x0057E97A TU (which reads the same +0xB4 flags), next is a vector<ObjectID>
// TU. Evidence: packet disasm, single caller 0x00441ECE, prev/next rows.
class Rva0057E97A
{
public:
	void rva0057E9ED(unsigned int index, int value);
private:
	char m_pad0[0xB4]; // +0x00..+0xB3
	struct Vec
	{
		int *start; // +0xB4
		int *finish; // +0xB8
	} m_vec;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void Rva0057E97A::rva0057E9ED(unsigned int index, int value)
{
	struct Vec *v = &m_vec;
	int size = v->finish - v->start;
	if (index >= (unsigned int)size)
		return;
	_ReadWriteBarrier();
	v->start[index] = value;
}
