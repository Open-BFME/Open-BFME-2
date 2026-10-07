// cl: /DNDEBUG /MD /EHsc /Oy- /O1 /arch:SSE /G7
// ?rva00272709@Drawable@@QAEHXZ @0x00272709 (34B). Evidence: Drawable's adjacent
// slot-19 and slot-20 module-array walkers at 0x002726C3 and 0x0027272B share
// the +0x14C array; vtable offset 0xCC is proven by this body's indirect call.
class DrawModule
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4(); virtual void slotC8();
	virtual int slotCC();
};
class Drawable
{
public:
	int rva00272709();
private:
	char m_pad[0x14C];
	DrawModule **m_drawModules;
};
int Drawable::rva00272709()
{
	for (DrawModule **p = m_drawModules; *p; ++p)
	{
		int v = (*p)->slotCC();
		if (v != 0)
			return v;
	}
	return 0;
}
