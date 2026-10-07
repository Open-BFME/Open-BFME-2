// cl: /MD /O1 /G7
//
// Target evidence: the 50-byte body calls the supplied object's virtual
// slots +0x28 and +0x90. It passes two true bytes to the first and this+0x70
// to the second. The interface slots and data offset follow those calls; the
// original class and method identities remain unknown.

struct Rva001DD031Interface
{
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(bool *flags);
	virtual void slot2c(); virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4c(); virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5c(); virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6c(); virtual void slot70(); virtual void slot74(); virtual void slot78();
	virtual void slot7c(); virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void slot8c();
	virtual void slot90(void *data);
};

class Rva001DD031
{
public:
	void rva001dd031(Rva001DD031Interface *object);
};

void Rva001DD031::rva001dd031(Rva001DD031Interface *object)
{
	bool flags[2] = { true, true };
	object->slot28(flags);
	char *data = reinterpret_cast<char *>(this);
	data += 0x70;
	object->slot90(data);
}
