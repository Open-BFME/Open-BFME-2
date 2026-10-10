// cl: /O1 /Oy- /DNDEBUG /MD
//
// ?rva0033A77F@Rva0033A77F@@QAEXHHHHH@Z @0x0033A77F 35B.
// Forwarder: passes its five stack arguments plus a trailing 0 to the member
// object at +0xA0 (thiscall, ret 0x14), calling the unclaimed 0x006BEF80.
// Retail keeps a frame pointer here (push ebp / mov ebp,esp), hence /Oy-.
// Argument and owner types are unknown; dwords are the measured ABI view.

class Rva006BEF80
{
public:
	void rva006BEF80(int a, int b, int c, int d, int e, int f);
};

class Rva0033A77F
{
public:
	void rva0033A77F(int a, int b, int c, int d, int e);

private:
	char unknown00[0xA0];
	Rva006BEF80 mA0;
};

void Rva0033A77F::rva0033A77F(int a, int b, int c, int d, int e)
{
	mA0.rva006BEF80(a, b, c, d, e, 0);
}
