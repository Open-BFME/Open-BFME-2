// cl: /O1 /DNDEBUG /MD /EHsc
// ?Rva000CFF4C@W3DStreakDraw@@UAEX_N@Z, retail 0x000CFF4C, 51 bytes.
// W3DStreakDraw vslot 16 (offset 0x40) of vtable 0x00BCD9B8 (class of ??1W3DStreakDraw@@UAE@XZ).
// Null-guarded forward of hidden and !hidden to the streak render object int slots 101 (0x194)
// and 105 (0x1a4). Layout follows W3DStreakDrawDestructor.cpp (m_streak at +0xc). Streak slots
// take int per WW3D RenderObjClass::Set_Hidden(int) in rendobj.h; the bool-to-int conversion
// produces the retail xor/movzx shape. Identity is class plus slot; the method name is an
// honest address name and the streak slot names are TU-local (indirect calls, no rows).
class BfmeStreakObject
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
	virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84();
	virtual void slot85(); virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94();
	virtual void slot95(); virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual void slot100();
	virtual void slot101(int onoff);
	virtual void slot102(); virtual void slot103(); virtual void slot104();
	virtual void slot105(int onoff);
};

class Rva0002B8C8TailBase
{
public:
	virtual ~Rva0002B8C8TailBase();

private:
	unsigned char m_pad[8];
};

class StreakDrawBase : public Rva0002B8C8TailBase
{
public:
	virtual ~StreakDrawBase() {}
};

class W3DStreakDraw : public StreakDrawBase
{
public:
	virtual void Rva000CFF4C(bool hidden);

private:
	BfmeStreakObject *m_streak;
	unsigned char m_pad[8];
};

void W3DStreakDraw::Rva000CFF4C(bool hidden)
{
	if (m_streak) {
		m_streak->slot105(!hidden);
		m_streak->slot101(hidden);
	}
}
