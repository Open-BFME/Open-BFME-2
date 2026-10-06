// cl: /MD
//
// GameEngineDeletingBase::~GameEngineDeletingBase, retail 0x001B4E74,
// 14 bytes. Dedicated TU so Locomotor.cpp keeps its matched bodies. Sets the
// vtable then tail-calls the AsciiString member destructor at plus 0x08,
// the same shape as Bucket::~Bucket (which tails to plus 0x0C).

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

GameEngineDeletingBase::~GameEngineDeletingBase()
{
}
