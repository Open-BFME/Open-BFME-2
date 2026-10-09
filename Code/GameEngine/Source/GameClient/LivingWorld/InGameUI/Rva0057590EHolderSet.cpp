// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0057590E@Rva0057590E@@QAEXH@Z retail 0x0057590E..0x005759A5 (151
// bytes EH RET 4), reached only through the rowed forwarder 0x00575DC2 on
// its +0x08 object. When the +0x28 holder's object accepts the value (its
// slot 7) that object is restarted (its slot 4). Otherwise the holder is
// cleared (rowed Rva000AD6F4::clear) and set (rowed 0x00575674) to a new
// 0x24-byte StrategicInGameUI::PlanningPhaseBuildingSelection (rowed ctor
// 0x005CE5B3) built from the +0x04 base subobject / the +0x1C word / the
// two values the +0x18 object's +0x04 field yields (rowed getters
// 0x00328A83 and 0x00574AAC) / the value as the region.
//
// Evidence: same holder test / clear / new / reset shape as the matched
// sibling 0x00575A3F (Rva00575A3FHolderSet.cpp), whose WB twins evaluate the
// 0x00328A83 getter into a temporary before the argument pushes; retail
// does the same here (WB twin 0x014D38C0 score 2.0), reproduced with the
// same hoisted word temporary. Class identity and field meanings remain
// unresolved.

class Object;
class LivingWorldRegion;

class Rva000AD6F4
{
public:
	void clear();
};

class Rva00575674
{
public:
	void rva00575674(Object *object);
};

class StrategicInGameUI
{
public:
	class PlanningUI;
	class PlanningPhaseBuildingSelection
	{
	public:
		PlanningPhaseBuildingSelection(void *owner, void *context, PlanningUI *ui, void *extra, LivingWorldRegion *region);
		virtual ~PlanningPhaseBuildingSelection();
	private:
		unsigned char m_pad04[0x24 - 0x04];
	};
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};

class Rva00574AACAddDwordField
{
public:
	int get() const;
};

class Rva0057590ECurrent
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void restart();					// slot 4
	virtual void slot5();
	virtual void slot6();
	virtual bool accepts(int value);		// slot 7
};

struct Rva0057590ESource
{
	unsigned char m_pad00[0x04];
	void *m_field04;						// +0x04
};

struct Rva0057590ERef
{
	void *m_object;
	Rva0057590ERef(void *object) : m_object(object) {}
	const Rva00328A83PtrChaseField *first() const
	{
		return static_cast<const Rva00328A83PtrChaseField *>(m_object);
	}
	const Rva00574AACAddDwordField *second() const
	{
		return static_cast<const Rva00574AACAddDwordField *>(m_object);
	}
};

struct Rva0057590EWord
{
	int m_value;
	Rva0057590EWord(int value) : m_value(value) {}
	operator StrategicInGameUI::PlanningUI *() const { return (StrategicInGameUI::PlanningUI *)m_value; }
};

class Rva0057590EBase0
{
public:
	virtual void base0Slot0();
};

class Rva0057590EBase4
{
public:
	virtual void base4Slot0();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva0057590E : public Rva0057590EBase0, public Rva0057590EBase4
{
public:
	void rva0057590E(int value);
private:
	Rva0057590ESource *m_source18;			// +0x18
	int m_1C;								// +0x1C
	unsigned char m_pad20[0x28 - 0x20];
	Rva0057590ECurrent *m_current28;		// +0x28 owning holder
};

void Rva0057590E::rva0057590E(int value)
{
	Rva0057590ECurrent *current = m_current28;
	if (current && current->accepts(value))
	{
		m_current28->restart();
		return;
	}
	reinterpret_cast<Rva000AD6F4 *>(&m_current28)->clear();
	reinterpret_cast<Rva00575674 *>(&m_current28)->rva00575674(reinterpret_cast<Object *>(
		new StrategicInGameUI::PlanningPhaseBuildingSelection(static_cast<Rva0057590EBase4 *>(this), (void *)m_1C,
			Rva0057590EWord(Rva0057590ERef(m_source18->m_field04).first()->get()),
			(void *)Rva0057590ERef(m_source18->m_field04).second()->get(),
			(LivingWorldRegion *)value)));
}
