// cl: /O1 /DNDEBUG /MD
//
// ProductionQueueHordeContain primary slots 29 and 30 (vtable 0x00C49040),
// over the HordeGarrisonContain slot-29/30 bases (0x00479B7F rowed,
// 0x00479ADA pinned by address; HordeGarrisonContain 0x00C46570 and
// TunnelContain 0x00C47740 carry the same two). Both then hand the Object's ID
// and the Object to the class's 0x004813B3 (pinned by address) when the
// answer of an Object's +0x250 module (its slot 31 result's slot 61) holds:
//   slot 29, retail 0x004814D1 (67 bytes): the Object's own module, asked
//            only when its template has kindOf bit 0x115:0x20.
//   slot 30, retail 0x00481439 (67 bytes): the module of the Object at the
//            argument's +0x274, whose ID is passed.
// Named by the bases' addresses.
template <int N> class Rva004814D1Slots : public Rva004814D1Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004814D1Slots<0>
{
};
class Rva004814D1Answer : public Rva004814D1Slots<61>
{
public:
	virtual bool rvaSlot61() = 0;
};
class Rva004814D1Module : public Rva004814D1Slots<31>
{
public:
	virtual Rva004814D1Answer *rvaSlot31() = 0;
};
enum ObjectID
{
	INVALID_ID = 0
};
class ThingTemplate
{
public:
	bool testKindOf115Bit5() const { return (m_kindOf115 & 0x20) != 0; }
private:
	unsigned char m_pad000[0x115];
	unsigned char m_kindOf115;	// +0x115
};
class Object
{
public:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x74 - 0x08];
	ObjectID m_id;			// +0x74
	unsigned char m_pad078[0x250 - 0x78];
	Rva004814D1Module *m_250;	// +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_274;			// +0x274
};
class ModuleData;
class HordeGarrisonContain
{
public:
	virtual ~HordeGarrisonContain();
	virtual void rva00479B7F(Object *obj);
	virtual void rva00479ADA(Object *obj);
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class ProductionQueueHordeContain : public HordeGarrisonContain
{
public:
	virtual void rva00479B7F(Object *obj);
	virtual void rva00479ADA(Object *obj);
	void rva004813B3(ObjectID id, Object *obj);
};
void ProductionQueueHordeContain::rva00479B7F(Object *obj)
{
	HordeGarrisonContain::rva00479B7F(obj);
	if (!obj->m_template->testKindOf115Bit5() || obj->m_250->rvaSlot31()->rvaSlot61())
		rva004813B3(obj->m_id, obj);
}
void ProductionQueueHordeContain::rva00479ADA(Object *obj)
{
	HordeGarrisonContain::rva00479ADA(obj);
	if (obj->m_274->m_250->rvaSlot31()->rvaSlot61())
		rva004813B3(obj->m_274->m_id, obj);
}
