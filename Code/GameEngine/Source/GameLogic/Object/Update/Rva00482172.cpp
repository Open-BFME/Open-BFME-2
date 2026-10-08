// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00482172, 89 bytes, RET. This interface view is +24 from the
// native UpdateModule prefix, whose module data and Object fields are +4/+8.
// Target evidence fixes the data value +8 and flag bytes +14/+15, this
// view's +4/+5 state bytes and GameLogic's manager pointer +170. Original
// interface class and method names remain unresolved.

class Object;
class GameLogic;
extern GameLogic *TheGameLogic;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModule
{
protected:
	void setWakeFrame(Object *object, UpdateSleepTime delay);
public:
	__forceinline void wakeNativeObject(Object *object)
	{
		setWakeFrame(object, UPDATE_SLEEP_NONE);
	}
};

struct Rva0035A238Argument;
class Rva0035A238
{
public:
	void rva0035A238(Rva0035A238Argument *argument, float value, bool flag, bool front);
	void rva0035A14F(Rva0035A238Argument *argument);
};

struct Rva00482172LogicView
{
	char unknown00[0x170];
	Rva0035A238 *manager;
};

struct Rva00482172Data
{
	char unknown00[8];
	float value;
	char unknown0C[8];
	bool front;
	bool flag;
};

class Rva00482172
{
public:
	void rva00482172();
private:
	char unknown00[4];
	bool initialized;
	bool state;
};

void Rva00482172::rva00482172()
{
	UpdateModule *module = reinterpret_cast<UpdateModule *>(reinterpret_cast<char *>(this) - 0x24);
	module->wakeNativeObject(*reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 0x1C));
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 0x1C);
	state = false;
	if (!initialized)
	{
		Rva00482172Data *data = *reinterpret_cast<Rva00482172Data **>(reinterpret_cast<char *>(this) - 0x20);
		reinterpret_cast<Rva00482172LogicView *>(TheGameLogic)->manager->rva0035A238(
			reinterpret_cast<Rva0035A238Argument *>(object), data->value, data->flag, data->front);
		initialized = true;
	}
	reinterpret_cast<Rva00482172LogicView *>(TheGameLogic)->manager->rva0035A14F(
		reinterpret_cast<Rva0035A238Argument *>(object));
}
