// cl: /GX- /GS
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
	void bfmeGoVJH(int messageTid);
};

#include "../../Include/Common/Rva008038F0Sender.h"

void BfmeThingVJH::bfmeGoVJH(int messageTid)
{
	char messageBuffer[0x40];
	BfmeMsgVJH msg(messageBuffer, 0x40);
	msg.m_bfme1c = 0x4c444154;
	msg.bfmeSet3VJH("TID", messageTid);
	msg.bfmeSet3VJH("LID", -2);
	msg.bfmeSetVJH("NAME", "LAN");
	((Rva008038F0Sender *)this)->send((BfmeC994 *)&msg);
}
