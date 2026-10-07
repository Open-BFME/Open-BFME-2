// cl: /EHsc /MD
// ?rva005503B1@Rva005503B1@@SAPAVRva0055011A@@XZ @0x005503B1 53B.
// Factory method returning a fresh Rva0055011A from throwing scalar new inside an EH frame.
// Evidence: new-size 0xB4 equals the landed Rva0055011A layout; callee ctor at 0x0055011A rowed;
// caller 0x00386F7F (SetUpGameSpy) calls it with no ECX setup and stores the result in
// ThePinger, so it is a static factory; the push ecx only reserves the EH new slot.
class Rva0055011A
{
public:
	Rva0055011A();
	~Rva0055011A();
private:
	char m_pad[0xB4];
};

class Rva005503B1
{
public:
	static Rva0055011A *rva005503B1();
};

Rva0055011A *Rva005503B1::rva005503B1()
{
	return new Rva0055011A;
}
