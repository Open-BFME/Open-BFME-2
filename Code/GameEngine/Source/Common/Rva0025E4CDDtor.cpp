// cl: /O1 /MD /EHsc
// ??1Rva0025E4CD@@UAE@XZ retail 0x0025E4CD 80B
// Own vptr BF6040; under EH state 0 the object at +0xC is destroyed through
// the rowed non-virtual dtor ??1Rva004D2344@@QAE@XZ 0x004D2344 and freed with
// the global ??3@YAXPAX@Z; the intermediate base's inline dtor restores BF5F30
// and the rowed base dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74 runs.
// Names address-derived.

class Rva004D2344
{
public:
	~Rva004D2344();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva0025E4CDBase : public GameEngineDeletingBase
{
public:
	virtual ~Rva0025E4CDBase() {}
};

class Rva0025E4CD : public Rva0025E4CDBase
{
public:
	virtual ~Rva0025E4CD();

private:
	Rva004D2344 *m_owned; // +0x0C
};

Rva0025E4CD::~Rva0025E4CD()
{
	delete m_owned;
}
