// cl: /MD /GX /DNDEBUG
//
// Large-object destructors, 80B each, sharing the vtable-restore + reverse
// member teardown + base dtor shape. The bodies destroy (they call pinned
// dtors), so these are dtors despite the family grouping with ctors:
//   ??1Rva005C9659@@UAE@XZ @0x005C9659: +0x258 via 0x0056D76B, +0x218 via
//       ~Rva00524BB4 (pinned), base ~GameWindow (donor_sweep pin 0x00314A0C)
// Member views are minimal: Rva00524BB4 spans +0x218..+0x258 (0x40); the
// trailing member's size is unproven and not declared beyond its dtor.
class GameWindow
{
protected:
	virtual ~GameWindow();
};
class Rva00524BB4
{
public:
	virtual ~Rva00524BB4();
private:
	unsigned char m_pad[0x40 - 4];
};
class Rva0056D76B
{
public:
	~Rva0056D76B();
};

class Rva005C9659 : public GameWindow
{
public:
	virtual ~Rva005C9659();
private:
	unsigned char m_pad218[0x218 - 4];
	Rva00524BB4 m_mem218;
	Rva0056D76B m_mem258;
};

Rva005C9659::~Rva005C9659()
{
}
