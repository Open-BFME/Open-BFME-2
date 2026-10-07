// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
//
// ?rva002AD1FD@Player@@QAEXXZ @0x002AD1FD 94B: Player helper scanning 32 command buttons.
// For the Player's Object (via rva002AC629) with template name (via Object rva00290E67),
// looks up CommandSet via g_bfmeWorldRV Rva0031D5F8, then for each of 32 buttons checks +0x44
// pointer via Object special-power query and calls virtual slot 22 (0x58) on the hit.
// Evidence: ecx passthrough to Player rva002AC629 proves Player this; callees all rowed;
// global g_bfmeWorldRV used by 1 TU; caller 0x002AE8A1 unclaimed; neighbours share RTS shard flags.
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class AsciiString;
struct BfmeWorldRV;
extern BfmeWorldRV *g_bfmeWorldRV;
class Object;
class CommandButton
{
public:
	unsigned char m_pad00[0x44];
	void *m_44; // +0x44
};
class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *s);
};

struct Iface22
{
	virtual void pad00() = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void pad03() = 0;
	virtual void pad04() = 0;
	virtual void pad05() = 0;
	virtual void pad06() = 0;
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;
	virtual void pad16() = 0;
	virtual void pad17() = 0;
	virtual void pad18() = 0;
	virtual void pad19() = 0;
	virtual void pad20() = 0;
	virtual void pad21() = 0;
	virtual void slot22() = 0;
};
class Player
{
public:
	Object *rva002AC629();
	void rva002AD1FD();
};
class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	const AsciiString *rva00290E67() const;
};

void Player::rva002AD1FD()
{
	Object *obj = rva002AC629();
	if (obj == 0)
		return;
	if (g_bfmeWorldRV == 0)
		return;
	const AsciiString *name = obj->rva00290E67();
	void *cmdSet = ((Rva0031D5F8 *)g_bfmeWorldRV)->rva0031D5F8(name);
	for (int i = 0; i < 0x20; i++)
	{
		const CommandButton *btn = ((CommandSet *)cmdSet)->getCommandButton(i);
		if (btn == 0)
			continue;
		void *p = btn->m_44;
		if (p == 0)
			continue;
		void *found = obj->getSpecialPowerModule(reinterpret_cast<const SpecialPowerTemplate *>(p));
		if (found == 0)
			continue;
		((Iface22 *)found)->slot22();
	}
}
