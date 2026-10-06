// cl: /DNDEBUG /MD
//
// ?rva00480281@SlaughterHordeContain@@UAE_NPAVObject@@@Z, retail 0x00480281, 25 bytes.
// Slot 20 of ??_7SlaughterHordeContain 0x00C48AA0 (CitadelSlaughterHordeContain
// 0x00C48CC0 inherits it; the HordeGarrisonContain table holds the shared
// default 0x005CB9FF there). True when the pinned lookup 0x00588BF3 of the
// empty second base at +0x9E0 (the HordeGarrisonContainCtor view) finds an
// entry for this contain and the object. Address name: class and slot are
// proven, the method identity is not.

class Object;

class GarrisonContain
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual bool rva00480281(Object *obj);
private:
	unsigned char m_pad04[0x9E0 - 0x04];
};

class Rva0047A040Base9E0
{
public:
	void *rva00588BF3(void *contain, Object *obj);
};

class HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
private:
	int m_9E0;
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual bool rva00480281(Object *obj);
};

// ?rva00480281@SlaughterHordeContain@@UAE_NPAVObject@@@Z @0x00480281
bool SlaughterHordeContain::rva00480281(Object *obj)
{
	return rva00588BF3(this, obj) != 0;
}
