// cl: /O1 /DNDEBUG /MD /EHsc

// ??1CommandButtonHuntUpdate@@MAE@XZ, retail 0x00495389, 73 bytes.
// Dtor lane: restores three vptrs (+0 0x0084ECFC plus +0x0C 0x007EFF90 plus
// +0x10 0x0084ECF0) then destroys AsciiString at +0x20 via pinned 0x00036410
// then calls pinned UpdateModule base dtor 0x0024A797. Layout from the rowed
// ctor 0x004952CF (UpdateModule base 0x20 plus AsciiString plus raw pointer).
// ZH donor CommandButtonHuntUpdate.cpp:94 has empty dtor. Recipe is the
// InvisibilityUpdateDtor slot pattern with String member (ProductionModifier
// AsciiString pin spelling).

class Thing;
class ModuleData;
class Object;

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class CommandButtonHuntUpdate : public UpdateModule
{
protected:
	virtual ~CommandButtonHuntUpdate();

private:
	AsciiString m_commandButtonName;
	const void *m_commandButton;
};

CommandButtonHuntUpdate::~CommandButtonHuntUpdate()
{
}
