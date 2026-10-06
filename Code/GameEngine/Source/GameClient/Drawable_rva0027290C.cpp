// cl: /DNDEBUG /MD /EHsc
// ?rva0027290C@Drawable@@QAEXH@Z @ 0x0027290C (35B): Drawable first-module
// setter: stores key at +0x44C then forwards it via module slot 0x5C.
// ?rva00272870@Drawable@@QAEXH@Z @ 0x00272870 (37B): guarded twin at +0xA8
// via module slot 0x50.
// Draw modules at +0x14C shared with Drawable_rva00272BE7. Callers
// 0x0039B5AF 0x004B05D4. Flags from Drawable_rva00272835 (no Oy- => frameless).
class DrawModule
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(int x); virtual void slot54(); virtual void slot58();
	virtual void slot5C(int x);
};
class Drawable
{
public:
	void rva0027290C(int x);
	void rva00272870(int x);
private:
	unsigned char m_pad[0xA8];
	int m_0A8;
	unsigned char m_padAC[0x14C - 0xAC];
	DrawModule **m_drawModules;
	unsigned char m_pad150[0x44C - 0x150];
	int m_44C;
};
void Drawable::rva0027290C(int x)
{
	if (x == 0)
		return;
	m_44C = x;
	DrawModule *m = m_drawModules[0];
	if (m != 0)
		m->slot5C(x);
}
void Drawable::rva00272870(int x)
{
	if (m_0A8 == x)
		return;
	m_0A8 = x;
	DrawModule *m = m_drawModules[0];
	if (m != 0)
		m->slot50(x);
}
