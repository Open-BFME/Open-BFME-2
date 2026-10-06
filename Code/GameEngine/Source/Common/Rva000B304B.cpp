// cl: /DNDEBUG /MD
// ?rva000B304B@Rva000B304B@@QAEXPAX_N@Z @0x000B304B 73B
// Honest address-derived placeholder: method rva000B304B in new opaque class
// Rva000B304B. Unlock lane: landing it makes 0x000B5179/97 0x000B4E43/583
// 0x000B57A7/367 ready. Callers pass (ptr bool): 0x000B4EF4 setne bool
// 0x000B51C0 true 0x000B5903 false. Body null-guards p then q and forwards
// bool-to-int to slot101 (0x194); provider slot34 (0x88) takes (0 this+8).
// Slots are TU-local (indirect calls no rows); refcount at +4 owner int +8.
class Rva000B304BRef
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual void slot100();
	virtual void slot101(int arg);
	int m_ref; // +4
};

class Rva000B304BProvider
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33();
	virtual Rva000B304BRef *slot34(int a, int b);
};

class Rva000B304B
{
public:
	void rva000B304B(void *p, bool flag);
private:
	char m_pad00[8];
	int m_val08; // +8
};

void Rva000B304B::rva000B304B(void *p, bool flag)
{
	if (!flag)
		flag = false;
	if (!p)
		return;
	Rva000B304BProvider *prov = (Rva000B304BProvider *)p;
	Rva000B304BRef *q = prov->slot34(0, m_val08);
	if (!q)
		return;
	q->slot101(flag);
	if (--q->m_ref == 0)
		q->slot00();
}
