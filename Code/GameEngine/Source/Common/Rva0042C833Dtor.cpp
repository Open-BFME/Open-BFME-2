// cl: /EHsc /MD
// ??1Rva0042C833@@UAE@XZ retail 0x0042C833 70B
// Own vptr C3C6EC; under EH state 1 the body unregisters this through the
// rowed ?rva0042CAEB@Rva0042CBB6 0x0042CAEB on the +0xC pointer; the member
// at +0x14 is then torn down (state 0) by its inline dtor calling the rowed
// ?clear@Rva000AD6F4 0x000AD6F4; the inline base dtor restores BDBA74.
// Caller: rowed ??_GRva0042C833 0x0042C977. Supersedes Peppy's 0.94 stash
// reverse/attempts/0x0042c833.cpp (the member dtor was the missing piece).

class Rva0042CBB6
{
public:
	void rva0042CAEB(int who);
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4() { clear(); }
	void clear();
	__forceinline int getPointer() const { return m_ptr; }

private:
	int m_ptr;
};

class Rva0042C833Base
{
public:
	virtual ~Rva0042C833Base() {}

private:
	int m_04;
	int m_08;
};

class GameMessage;

class Rva0042C833 : public Rva0042C833Base
{
public:
	virtual ~Rva0042C833();
	int rva0042C879(GameMessage *message);

private:
	Rva0042CBB6 *m_0C;
	int m_10;
	Rva000AD6F4 m_14;
};

Rva0042C833::~Rva0042C833()
{
	m_0C->rva0042CAEB((int)this);
}

union GameMessageArgumentType
{
    int integer;
    float real;
    int boolean, objectID, drawableID;
    unsigned int teamID;
    struct Loc { float x, y, z; } location;
    struct Pix { int x, y; } pixel;
    struct PixReg { int loX, loY, hiX, hiY; } pixelRegion;
    unsigned int timestamp;
    unsigned short wChar;
};
class GameMessage
{
public:
    const GameMessageArgumentType *getArgument(int index) const;
    char unknown00[0x10];
    int type;
};
struct Rva0042C083Param { int m_00, m_04; };
class Rva0042C7B1
{
public:
    int rva0042C7B1(const Rva0042C083Param *point, int argument);
};
class Rva005E6817Mid
{
public:
    int fwd(GameMessage *message);
};

// Native0042C879..0042C8D1 RET4: input type3, +14 callback first,
// then first argument's two32-bit pixel coordinates and argument1's int
// forwarded to the rowed mouse handler42C7B1 on this. Constructor42C7E0
// and this TU's destructor establish the receiver. Original names unknown.
int Rva0042C833::rva0042C879(GameMessage *message)
{
    Rva005E6817Mid *callback = reinterpret_cast<Rva005E6817Mid *>(m_14.getPointer());
    if (callback) {
        int result=callback->fwd(message);
        if (result==1) return result;
    }
    if (message->type!=3) return 0;
    const volatile GameMessageArgumentType *argument=message->getArgument(0);
    const int x=argument->pixel.x;
    const int y=argument->pixel.y;
    Rva0042C083Param point={x,y};
    return reinterpret_cast<Rva0042C7B1 *>(this)->rva0042C7B1(&point,message->getArgument(1)->integer);
}
