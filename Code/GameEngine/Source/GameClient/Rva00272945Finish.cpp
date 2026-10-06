// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272945@Drawable@@QAEXH@Z @0x00272945 (22B): Drawable forwards `a` to
// the first draw module's virtual slot 0x60/4 (the 0x14C module-pointer array),
// tail-calling through the vtable when the slot is non-null. Keeping the array
// pointer named (rather than naming the element) is what reproduces retail's
// `mov eax,[eax]` reuse plus the `mov ecx,eax` call setup.
class DrawModule
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
	virtual void slot60(int a) = 0;
};

class Drawable
{
public:
	void rva00272945(int a);
private:
	char m_pad[0x14C];
	DrawModule **m_drawModules;
};

// ?rva00272945@Drawable@@QAEXH@Z
void Drawable::rva00272945(int a)
{
	DrawModule **p = m_drawModules;
	if (*p)
		(*p)->slot60(a);
}
