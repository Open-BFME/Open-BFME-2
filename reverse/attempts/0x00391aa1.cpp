// ?Rva00391AA1Has@@YG_NPAX0@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /MD
// ?Rva00391AA1Has@@YG_NPAX0@Z @0x00391AA1 103B
// Free helper: if byte at +0x10F of first object has 0x80, look up command set via rowed 0x0031D5F8 on AsciiString at +0x70 through g_bfmeWorldRV, scan 32 buttons via rowed getCommandButton, filter types 3/0x35/1/0x2E, compare rowed 0x0035B570 template with second arg.
// Evidence: unlock lane; callees rowed 0x0031D5F8 0x00409EE8 plus pin 0x0035B570; caller 0x005DCCDD passes two rva002D06CA results; ret 8 two args returning bool; honest free-function name.
class AsciiString;
class CommandButton;
class ThingTemplate;
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};
struct BfmeWorldRV;
extern BfmeWorldRV *g_bfmeWorldRV;
class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};
class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;
};
// ?Rva00391AA1Has@@YG_NPAX0@Z present-unmatched
bool __stdcall Rva00391AA1Has(void *a, void *b)
{
	void *set = 0;
	int i = 0;
	if ((((unsigned char *)a)[0x10F] & 0x80) == 0)
		return false;
	set = ((Rva0031D5F8 *)g_bfmeWorldRV)->rva0031D5F8((const AsciiString *)((char *)a + 0x70));
	if (set == 0)
		return false;
	for (i = 0; i < 0x20; ++i)
	{
		const CommandButton *btn = ((const CommandSet *)set)->getCommandButton(i);
		if (btn == 0)
			continue;
		int t = *(const int *)((const char *)btn + 0x14);
		if (t == 3 || t == 0x35 || t == 1 || t == 0x2E)
		{
			if (btn->rva0035B570() == b)
				return true;
		}
	}
	return false;
}
