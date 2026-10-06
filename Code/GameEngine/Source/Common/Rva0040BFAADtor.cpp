// cl: /DNDEBUG /MD /GX
// ??1Rva0040BFAA@@UAE@XZ @ 0x0040BFAA (74B). Dtor with vtable 0x008392E0 calling two vector dtors then base.
// Evidence: retail stores vtable 0x00C392E0 then calls rowed 0x0040B59F at +0x18 and 0x0040BEBA at +0x0C then rowed GameEngineDeletingBase 0x001B4E74; caller 0x0040C0AB deleting dtor.
class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

struct Rva0040B59F
{
	~Rva0040B59F();
	char m_data[12];
};

struct Rva0040BEBA
{
	~Rva0040BEBA();
	char m_data[12];
};

class Rva0040BFAA : public GameEngineDeletingBase
{
public:
	virtual ~Rva0040BFAA();
private:
	Rva0040BEBA m_0C;
	Rva0040B59F m_18;
};

Rva0040BFAA::~Rva0040BFAA()
{
}
