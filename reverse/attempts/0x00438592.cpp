// ?rva00438592@Rva002542F3Member@@QAEXPAVRva00438758Interface@@@Z
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00438592@Rva002542F3Member@@QAEXPAVRva00438758Interface@@@Z retail
// 0x00438592..0x00438758 (454 bytes thiscall ret 4). The xfer of the
// 0xB8-byte member (ctor 0x002542F3 / copy 0x0043831C) called only by the
// wrapper xfer Rva004382FC::rva00438758 0x00438758 with the same interface.
// Version {1 1} through slot +0x28 then the dword at +0 (slot +0x78)
// BitFlags<104>::xfer +4 then XferInvisibilityType on +0x18 then
// 0x003064CB on the +0x1C storage and the dword at +0x9C (+0x78). When
// slot +0x04 answers true it reads two names (slot +0x6C) and resolves them
// through TheFXListStore->findFXList into +0xA0 and +0xA4; otherwise it
// writes the two FXLists' names (+0xC) or empty strings. Finally
// BitFlags<101>::xfer +0xA8. The callees prove the interface is the Xfer;
// the pinned spelling keeps the address-derived interface name.
#include "ascii_string.h"

class Xfer;

class Rva00438758Interface
{
public:
	virtual void slot00();
	virtual bool slot01(); // +0x04
	virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(void *version); // +0x28
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(AsciiString *value); // +0x6C
	virtual void slot28(); virtual void slot29();
	virtual void slot30(void *value); // +0x78
};

// Xfer::Version: the stored and the current version byte.
class Rva00438592Version
{
public:
	Rva00438592Version(unsigned char a, unsigned char b) : m_a(a), m_b(b) {}
	unsigned char m_a;
	unsigned char m_b;
};

template <int N> class BitFlags
{
public:
	void xfer(Xfer *xfer);

private:
	char m_pad[0x10];
};

class Rva00291440;

void XferInvisibilityType(Xfer *xfer, int *value);
void rva003064CB(Xfer *xfer, Rva00291440 *value);

class FXList
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad[0xc];
	AsciiString m_name; // +0x0C
};

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};
extern FXListStore *TheFXListStore;

class Rva002542F3Member
{
public:
	void rva00438592(Rva00438758Interface *interfaceView);

private:
	int m_00; // +0x00
	BitFlags<104> m_bits04; // +0x04
	float m_float14; // +0x14
	int m_int18; // +0x18
	char m_buf1C[0x80]; // +0x1C
	int m_9C; // +0x9C
	const FXList *m_fxA0; // +0xA0
	const FXList *m_fxA4; // +0xA4
	BitFlags<101> m_bitsA8; // +0xA8
};

void Rva002542F3Member::rva00438592(Rva00438758Interface *interfaceView)
{
	Xfer *xfer = reinterpret_cast<Xfer *>(interfaceView);
	Rva00438592Version version(1, 1);
	interfaceView->slot10(&version);
	interfaceView->slot30(this);
	m_bits04.xfer(xfer);
	XferInvisibilityType(xfer, &m_int18);
	rva003064CB(xfer, reinterpret_cast<Rva00291440 *>(m_buf1C));
	interfaceView->slot30(&m_9C);
	if (interfaceView->slot01())
	{
		AsciiString nameA0;
		AsciiString nameA4;
		interfaceView->slot27(&nameA0);
		interfaceView->slot27(&nameA4);
		m_fxA0 = TheFXListStore->findFXList(nameA0.str());
		m_fxA4 = TheFXListStore->findFXList(nameA4.str());
	}
	else
	{
		AsciiString nameA0 = m_fxA0 ? m_fxA0->getName() : AsciiString("");
		AsciiString nameA4 = m_fxA4 ? m_fxA4->getName() : AsciiString("");
		interfaceView->slot27(&nameA0);
		interfaceView->slot27(&nameA4);
	}
	m_bitsA8.xfer(xfer);
}
