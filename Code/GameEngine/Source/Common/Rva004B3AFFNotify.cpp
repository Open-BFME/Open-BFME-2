// cl: /O1 /DNDEBUG /MD
//
// ?rva004B3AFF@Rva004B3AFF@@QAEXXZ @0x004B3AFF 67B.
// Run the upgrade hook at this-0x10, push the AsciiString at +0x118 of
// the object at this-0xC onto the Object at this-8, tell the skirmish
// manager about that object twice, and mark TheControlBar +0x28.

// class-gate: allow AsciiString address-only view. This body only pushes the
// member address and never constructs or destroys a string; the empty class
// matches the 67B retail body.
class AsciiString
{
};

class Object
{
public:
	void setCommandSetStringOverride(const AsciiString &name);
};

class UpgradeModule
{
public:
	void rva004CE4A0();
};

class Rva002A8F24
{
public:
	void rva002A8F56(Object *obj);
	void rva002A9365(Object *obj);
};

class StringHolder
{
public:
	char m_pad[0x118];
	AsciiString m_name;
};

class ControlBar
{
public:
	char m_pad[0x28];
	unsigned char m_flag28;
};

extern Rva002A8F24 *g_00DFEEF8;
extern ControlBar *TheControlBar;

class Rva004B3AFF
{
public:
	void rva004B3AFF();
};

void Rva004B3AFF::rva004B3AFF()
{
	((UpgradeModule *)((char *)this - 0x10))->rva004CE4A0();
	StringHolder *holder = *(StringHolder **)((char *)this - 0x0C);
	Object *obj = *(Object **)((char *)this - 8);
	obj->setCommandSetStringOverride(holder->m_name);
	g_00DFEEF8->rva002A8F56(obj);
	g_00DFEEF8->rva002A9365(obj);
	TheControlBar->m_flag28 = 1;
}
