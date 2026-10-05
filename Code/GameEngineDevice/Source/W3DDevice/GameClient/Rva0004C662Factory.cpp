// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ?rva0004C662@Rva004C743@@QAEPAVRva00984EF@@XZ @0x0004C662 50B
// Virtual-slot factory returning new Rva00984EF (0x1C bytes) via rowed ctor.
// Evidence: vtable slot 48 of 0x007C4738 class Rva004C743; callees operator new 0x0002FDA0 row mem_ops.cpp ctor 0x000984CE row OpaqueSingleInheritanceDtors.cpp EH_prolog; prev W3DGameClientSnowFactory.cpp same flags same new-pattern 53B; size 0x1C matches Rva00984EF layout.
class Rva0098477
{
public:
	Rva0098477();
	virtual ~Rva0098477();
};
class Rva00984EF : public Rva0098477
{
public:
	Rva00984EF();
	virtual ~Rva00984EF();
private:
	unsigned char m_pad04[0xC];
	int m_10;
	int m_14;
	int m_18;
};
// Keyboard (vtable 0x00BE81F0) and DirectInputKeyboard (0x00BC8688,
// 0xE28 bytes), formerly modelled here as AIPlayer / AISkirmishPlayer.
class Keyboard
{
public:
	Keyboard() throw();
	virtual ~Keyboard() throw();
protected:
	char m_pad04[8];
	unsigned short m_modifiers;
	char m_pad0E[0xE20 - 0x0E];
};
class DirectInputKeyboard : public Keyboard
{
public:
	DirectInputKeyboard();
	virtual ~DirectInputKeyboard();
private:
	void *m_pDirectInput;
	void *m_pKeyboardDevice;
};
// Rva004C743 is W3DGameClient (its vtable 0x00BC4738 holds the matched
// W3DGameClient::createFontLibrary at slot 40) and slot 44 (0x0004C6D4) is
// Zero Hour's inline W3DGameClient::createKeyboard, NEW DirectInputKeyboard.
// The row keeps the address name: W3DGameClient.cpp already emits that inline
// from Zero Hour's header (unoptimized), so claiming the ZH name here would
// put a second body behind one COMDAT.
class Rva004C743
{
public:
	Rva00984EF *rva0004C662();
	Keyboard *rva0004C6D4();
};
Rva00984EF *Rva004C743::rva0004C662()
{
	return new Rva00984EF;
}
Keyboard *Rva004C743::rva0004C6D4()
{
	return new DirectInputKeyboard;
}
