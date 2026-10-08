// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva002724C4@Drawable@@QAEXH@Z, retail 0x002724C4, 57 bytes, and
// ?rva00272545@Drawable@@QAEHH@Z, retail 0x00272545, 54 bytes: two more of
// the Drawable broadcasters over the draw modules at this+0x14C (see
// Drawable_rva002724FD.cpp), through getObjectDrawInterface at DrawModule
// slot 0xA8. 0x002724C4 runs only while the drawable has an object (+0xFC)
// and forwards its argument to ObjectDrawInterface slot 0x80;
// 0x00272545 returns the first nonzero answer of slot 0x90 for its
// argument, else 0. Argument and result types are read as dwords.

class BfmeObjectDrawForRva2724C4
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void rva002724C4Target(int arg) = 0;
	virtual void slot84() = 0; virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual int rva00272545Target(int arg) = 0;
};

class BfmeDrawModuleForRva2724C4
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual BfmeObjectDrawForRva2724C4 *getObjectDrawInterface() = 0;
};

class Object;

class Drawable
{
public:
	void rva002724C4(int arg);
	int rva00272545(int arg);

private:
	unsigned char m_pad000[0xFC];
	Object *m_object;	// +0xFC
	unsigned char m_pad100[0x14C - 0x100];
	BfmeDrawModuleForRva2724C4 **m_drawModules;	// +0x14C
};

void Drawable::rva002724C4(int arg)
{
	if (m_object == 0)
		return;
	for (BfmeDrawModuleForRva2724C4 **dm = m_drawModules; *dm; ++dm) {
		BfmeObjectDrawForRva2724C4 *di = (*dm)->getObjectDrawInterface();
		if (di)
			di->rva002724C4Target(arg);
	}
}

int Drawable::rva00272545(int arg)
{
	for (BfmeDrawModuleForRva2724C4 **dm = m_drawModules; *dm; ++dm) {
		BfmeObjectDrawForRva2724C4 *di = (*dm)->getObjectDrawInterface();
		if (di) {
			int result = di->rva00272545Target(arg);
			if (result)
				return result;
		}
	}
	return 0;
}
