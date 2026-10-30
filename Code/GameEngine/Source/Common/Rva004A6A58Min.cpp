// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
//
// ?update@Rva004A6A58@@QAEHXZ @0x004A6A58 41B.
// Virtual slot 4 on the object at +0x3D8, clamped to at least 1, then the
// minimum of that and AIUpdateInterface::update (direct call, rowed symbol
// 0x0026E267). cmovl keeps the smaller signed result.

enum UpdateSleepTime
{
	USLEEP_MIN = 0
};

class SlotOwner
{
public:
	virtual int s0();
	virtual int s1();
	virtual int s2();
	virtual int s3();
	virtual int s4();
};

typedef bool Bool;
typedef int Int;
class Object;
class SupplyTruckAIInterface;
#include "../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiDock(Object *obj, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
};

class Xfer;

class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update(); virtual void v001(); virtual void v002(); virtual void xfer(Xfer *xfer);
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface(); // slot 95 (+0x17C)
	virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109();
	virtual Bool isIdle(); // slot 110 (+0x1B8)
	Int getCurrentStateID() const; // rowed 0x00262FC3

	char m_pad04[0x20 - 0x04];
	AICommandInterface m_commands; // +0x20
	char m_pad21[0x3E8 - 0x21];
};

class Rva004A6A58
{
public:
	int update();

private:
	char m_pad[0x3D8];
	SlotOwner *m_slot;
};

int Rva004A6A58::update()
{
	int raw = m_slot->s4();
	int n;
	if (raw > 0)
		n = raw;
	else
		n = 1;
	int slept = ((AIUpdateInterface *)this)->AIUpdateInterface::update();
	if (n < slept)
		slept = n;
	return slept;
}
