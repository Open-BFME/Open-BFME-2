// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?rva00050FA0@Rva00050FA0@@QAEPAV1@H@Z @0x00050FA0 36B
// Helper-then-init method: forwards its int argument to the 0x002D99E3
// helper, zeroes the float at +0x88 via SSE and the flag at +0x8C, and
// returns this.
void __stdcall rva0002D99E3(int x);
class Rva00050FA0
{
public:
	Rva00050FA0 *rva00050FA0(int x);
private:
	char m_00[0x88];
	float m_88;
	unsigned char m_8c;
};
Rva00050FA0 *Rva00050FA0::rva00050FA0(int x)
{
	rva0002D99E3(x);
	m_88 = 0.0f;
	m_8c = 0;
	return this;
}
