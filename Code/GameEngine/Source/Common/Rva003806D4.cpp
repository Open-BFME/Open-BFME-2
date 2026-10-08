// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /G7
// ?rva003806D4@Rva003806D4@@QAEXXZ @0x003806D4 49B unlock between 0x003802DF and 0x00380705.
// Bare new of AptMessageBox with EH state and null-checked ctor.
// Evidence: push 8 via rowed 0x0002FDA0 then rowed 0x00437F0A; caller at
// 0x00380C07; prev 0x003802DF next 0x00380705 share page and flags.
void *__cdecl operator new(unsigned int size);

class AptMessageBox
{
public:
	AptMessageBox();
private:
	char m_pad[8];
};

class Rva003806D4
{
public:
	void rva003806D4();
};

void Rva003806D4::rva003806D4()
{
	new AptMessageBox();
}
