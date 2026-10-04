// cl: /GS
// Open-BFME5 conversions.

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	~BfmeMsgVJH() throw();
	void bfmeSetVJH(const char *k, const char *v) throw();
	void bfmeSet3VJH(const char *k, int v) throw();
	char m_bfmePad[0x1c];
	int m_bfme1c;
	char m_bfmePad2[0x14];
};

class BfmeThingVJH
{
public:
	void bfmeGoVJH(int a);
};

class BfmeC994;
class Rva008038F0Sender
{
public:
	void send(BfmeC994 *message) throw();
};

void BfmeThingVJH::bfmeGoVJH(int a)
{
	char buf[0x40];
	BfmeMsgVJH msg(buf, 0x40);
	msg.m_bfme1c = 0x4c444154;
	msg.bfmeSet3VJH("TID", a);
	msg.bfmeSet3VJH("LID", -2);
	msg.bfmeSetVJH("NAME", "LAN");
	((Rva008038F0Sender *)this)->send((BfmeC994 *)&msg);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGoVJH@BfmeOwner803BF0@@QAEXH@Z=?bfmeGoVJH@BfmeThingVJH@@QAEXH@Z")
