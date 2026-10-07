// cl: /DNDEBUG /MD /EHsc
// ?rva0023998E@Drawable@@QAEXH@Z @0x0023998E 93B.
// Target evidence: indexes the +0xF8 circular-list holders, brackets their
// node callbacks with TheDisplay vslots +0xD4/+0x100, then clears the holder.
// Identity remains address-derived; callback owner and list semantics are inferred.

class Rva002796D9
{
public:
	void rva002796D9(int slot);
};

struct Rva0023998EListNode
{
	Rva0023998EListNode *m_next;
	void *m_prev;
	Rva002796D9 *m_callback;
};

class Rva00239380Holder
{
public:
	Rva0023998EListNode *m_head;
	void rva00239380();
};

class Display
{
public:
#define DISPLAY_SLOT(n) virtual void unused##n();
	DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03)
	DISPLAY_SLOT(04) DISPLAY_SLOT(05) DISPLAY_SLOT(06) DISPLAY_SLOT(07)
	DISPLAY_SLOT(08) DISPLAY_SLOT(09) DISPLAY_SLOT(10) DISPLAY_SLOT(11)
	DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15)
	DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23)
	DISPLAY_SLOT(24) DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27)
	DISPLAY_SLOT(28) DISPLAY_SLOT(29) DISPLAY_SLOT(30) DISPLAY_SLOT(31)
	DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34) DISPLAY_SLOT(35)
	DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39)
	DISPLAY_SLOT(40) DISPLAY_SLOT(41) DISPLAY_SLOT(42) DISPLAY_SLOT(43)
	DISPLAY_SLOT(44) DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47)
	DISPLAY_SLOT(48) DISPLAY_SLOT(49) DISPLAY_SLOT(50) DISPLAY_SLOT(51)
	DISPLAY_SLOT(52)
#undef DISPLAY_SLOT
	virtual void beginImageDraw();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void endImageDraw();
};

extern Display *TheDisplay;

class Drawable
{
public:
	virtual void unused();
private:
	unsigned char m_pad[0xF8 - 4];
	Rva00239380Holder m_lists[10];
public:
	void rva0023998E(int slot);
};

void Drawable::rva0023998E(int slot)
{
	if (slot < 0 || slot >= 10)
		return;
	register int slotIndex = slot;
	register Rva00239380Holder *holder = &m_lists[slotIndex];
	if (holder->m_head->m_next == holder->m_head)
		return;
	TheDisplay->beginImageDraw();
	for (register Rva0023998EListNode *node = holder->m_head->m_next;
		node != holder->m_head; node = node->m_next)
		node->m_callback->rva002796D9(slotIndex);
	TheDisplay->endImageDraw();
	holder->rva00239380();
}
