// cl: /GS
// Open-BFME5 conversions.

class BfmeMsgVJL
{
public:
	void bfmeInitVJL(char *buf, int n);
	void bfmeDoneVJL();
	char m_bfmePad[0x34];
};

class BfmeXVJL
{
public:
	virtual void bfmeB00VJL();
	virtual void bfmeB04VJL();
	virtual void bfmeB08VJL();
	virtual void bfmeB0CVJL(class BfmeMsgVJL *m);
};

class BfmeThingVJL
{
public:
	virtual void bfmeA00VJL();
	virtual class BfmeXVJL *bfmeA04VJL();
	virtual void bfmeA08VJL();
	virtual void bfmeA0CVJL();
	virtual void bfmeA10VJL();
	virtual void bfmeA14VJL();
	virtual void bfmeA18VJL(class BfmeMsgVJL *m);
	void bfmeGoVJL(int unused);
};

// Address-qualified static scope only: no EA class/method identity is claimed.
// BFME1 donor at 775a0370b7:
// game/GameEngine/Source/Common/Rva007F4770.cpp (0x007F4770/15).
// Target facts: rowed registration 0x006611A0/67 pushes callback VA 0x00A61220
// at 0x006611BF with its unchanged receiver; target 0x00661220/15 forwards
// its first four-byte argument and second receiver word to the independently
// rowed BfmeThingVJL::bfmeGoVJL body at 0x00661230/87. The donor supplies the
// same forwarding structure, not the target's original names or wider layout.
// Reuse this unit's established receiver declaration, adding no private view.
// The callback precedes the helper definition so the observed direct call
// remains a call; both native bodies are independently byte-verified.
class Rva00661220Callback
{
public:
    static void __cdecl forward(int value, BfmeThingVJL *receiver);
};

void __cdecl Rva00661220Callback::forward(int value, BfmeThingVJL *receiver)
{
    receiver->bfmeGoVJL(value);
}

void BfmeThingVJL::bfmeGoVJL(int unused)
{
	char buf[0x20];
	BfmeMsgVJL msg;
	msg.bfmeInitVJL(buf, 0x20);
	bfmeA18VJL(&msg);
	bfmeA04VJL()->bfmeB0CVJL(&msg);
	msg.bfmeDoneVJL();
}
