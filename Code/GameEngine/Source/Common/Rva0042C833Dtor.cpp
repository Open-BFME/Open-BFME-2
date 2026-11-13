// cl: /O1 /EHsc /MD
// ??1Rva0042C833@@UAE@XZ retail 0x0042C833 70B
// Own vptr C3C6EC; under EH state 1 the body unregisters this through the
// rowed ?rva0042CAEB@Rva0042CBB6 0x0042CAEB on the +0xC pointer; the member
// at +0x14 is then torn down (state 0) by its inline dtor calling the rowed
// ?clear@Rva000AD6F4 0x000AD6F4; the inline base dtor restores BDBA74.
// Caller: rowed ??_GRva0042C833 0x0042C977. Supersedes Peppy's 0.94 stash
// reverse/attempts/0x0042c833.cpp (the member dtor was the missing piece).

class Rva0042C1B7Item;
class Rva002D3627Host;

class Rva0042CBB6
{
public:
	void rva0042CAEB(int who);
	void rva002B230F(int impl);
};

#include "../../Include/Common/Rva000AD6F4.h"

class Rva0042C833Base
{
public:
	virtual ~Rva0042C833Base() {}
};

class GameMessage;

class Rva0042C833 : public Rva0042C833Base
{
public:
	Rva0042C833(Rva0042C1B7Item *owner, Rva002D3627Host *holder, Rva0042CBB6 *source);
	virtual ~Rva0042C833();
	int rva0042C879(GameMessage *message);

private:
	Rva0042C1B7Item *m_04;
	Rva002D3627Host *m_08;
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
#include "../../Include/Common/Rva0042C083Param.h"
class Rva0042C7B1
{
public:
    int rva0042C7B1(const Rva0042C083Param *point, int argument);
};
#include "../../Include/Common/Rva005E6817Mid.h"

// Native0042C879..0042C8D1 RET4: input type3, +14 callback first,
// then first argument's two32-bit pixel coordinates and argument1's int
// forwarded to the rowed mouse handler42C7B1 on this. Constructor42C7E0
// and this TU's destructor establish the receiver. Original names unknown.
int Rva0042C833::rva0042C879(GameMessage *message)
{
    Rva005E6817Mid *callback = reinterpret_cast<Rva005E6817Mid *>(m_14.m_ptr);
    if (callback) {
        int result=callback->fwd(message);
        if (result==1) return result;
    }
    if (message->type!=3) return 0;
    const volatile GameMessageArgumentType *gameMessageArgumentType=message->getArgument(0);
    const int x=gameMessageArgumentType->pixel.x;
    const int y=gameMessageArgumentType->pixel.y;
    Rva0042C083Param point={x,y};
    return reinterpret_cast<Rva0042C7B1 *>(this)->rva0042C7B1(&point,message->getArgument(1)->integer);
}

// Native42C7E0..42C833 RET12; the rowed allocating wrapper42C8D1
// forwards owner, holder and source into this 18-byte payload. The rowed
// destructor proves the +14 owned cell and base unwind. Names remain opaque.
// The constructor's state0 boundary supports this complete-object view of
// the +4/+8 fields; their former inherited padding was a structural guess.
Rva0042C833::Rva0042C833(Rva0042C1B7Item *owner, Rva002D3627Host *holder, Rva0042CBB6 *source)
    : m_04(owner), m_08(holder), m_0C(source), m_10(-1)
{
    m_0C->rva002B230F((int)this);
}
