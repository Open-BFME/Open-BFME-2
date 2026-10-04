// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0044AA84@LANAPI@@UAEXVAsciiString@@@Z @ 0x0044AA84 77B slot 52 of 0x0083E680.
// Slot52 resolves AsciiString via ResolveIP pin then calls slot53 with IP.
// Evidence: vslot lane slot 52; pin ResolveIP 0x581339 takes AsciiString; rowed StringBase copy 0x365F0 and releaseBuffer 0x36410; virtual [edx+0xd4] is slot53; class copied from LANAPIFillInLANMessage TU.
#include "ascii_string.h"

unsigned int __cdecl ResolveIP(AsciiString addr);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);
private:
	unsigned char m_baseFields[8];
};
class LANAPIInterface : public SubsystemInterface
{
public:
	virtual ~LANAPIInterface(void) {}
};
class LANAPI : public LANAPIInterface
{
public:
	virtual ~LANAPI(void);
	virtual void reset(void);
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void rva0044AA84(AsciiString addr);
	virtual void slot53(unsigned int ip) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void fillInLANMessage(void *message);
};

void LANAPI::rva0044AA84(AsciiString addr)
{
	unsigned int ip = ResolveIP(addr);
	slot53(ip);
}
