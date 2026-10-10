// cl: /MD

// Address-named target wrapper. Retail bytes establish the call through slot
// +0x94 with pointer 0x00CE7AA8 and final integer argument 4. The BFME1 donor
// exposed a similar raw virtual dispatch, but used a different slot and
// pointer; its owner identity was one of eight ICF-folded candidates and is
// not carried over here.
class Rva006BD490Receiver
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
	virtual void slot90();
	virtual void slot94(const void *, void *, int);
};

extern const char s_geometryTypeString[];

void Rva006BD490DispatchRaw(Rva006BD490Receiver *receiver, void *value)
{
	receiver->slot94(s_geometryTypeString, value, 4);
}
