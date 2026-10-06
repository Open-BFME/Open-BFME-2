// cl: /DNDEBUG /MD
// ?rva002645FF@Rva002645FF@@QAE_NXZ retail 0x002645FF 87B.
// AIUpdate slot 0x1B8 (110) shared by Siege/Transport/Wander/HordeWorker vtables.
// Evidence: vtable slot 110 of 0x00847B98 0x0084D330 0x008505F8 0x008508C8 0x00853AA8 0x00853D30;
// callers 0x003681E8 0x0048E643 0x0048F46D tail-jump here; callee rowed 0x0004E536 testStatus.
// ?rva00264F3D@Rva00264F3D@@QAEHXZ retail 0x00264F3D 33B.
// Neighbour of 0x002645FF same TU same flags. Returns +0x38 field or 0 with 0x0A status gate.
// Evidence: caller 0x0034BDBD; callee rowed 0x0004E536 testStatus.
// ?rva00264E93@Rva00264E93@@QAEPAXXZ retail 0x00264E93 35B.
// Neighbour same TU same flags. Status 0x16 plus +0x40 gate returns +0x30+0x24 or 0.
// Evidence: callers 0x004789FB 0x00478A80 0x00478B42; callee rowed 0x0004E536 testStatus.
enum ObjectStatusTypes;

class Slot110
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003(); virtual void v004();
	virtual void v005(); virtual void v006(); virtual void v007(); virtual void v008(); virtual void v009();
	virtual void v010(); virtual void v011(); virtual void v012(); virtual void v013(); virtual void v014();
	virtual void v015(); virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023(); virtual void v024();
	virtual void v025(); virtual void v026(); virtual void v027(); virtual void v028(); virtual void v029();
	virtual void v030(); virtual void v031(); virtual void v032(); virtual void v033(); virtual void v034();
	virtual void v035(); virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043(); virtual void v044();
	virtual void v045(); virtual void v046(); virtual void v047(); virtual void v048(); virtual void v049();
	virtual void v050(); virtual void v051(); virtual void v052(); virtual void v053(); virtual void v054();
	virtual void v055(); virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063(); virtual void v064();
	virtual void v065(); virtual void v066(); virtual void v067(); virtual void v068(); virtual void v069();
	virtual void v070(); virtual void v071(); virtual void v072(); virtual void v073(); virtual void v074();
	virtual void v075(); virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083(); virtual void v084();
	virtual void v085(); virtual void v086(); virtual void v087(); virtual void v088(); virtual void v089();
	virtual void v090(); virtual void v091(); virtual void v092(); virtual void v093(); virtual void v094();
	virtual void v095(); virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104();
	virtual void v105(); virtual void v106(); virtual void v107(); virtual void v108(); virtual void v109();
	virtual bool isReady();
};

class Slot8
{
public:
	virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
	virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
	virtual bool getResult();
};

class Mid
{
public:
	char m_pad00[0x258];
	Slot110 *m_slot; // +0x258
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	char m_pad00[0x274];
	Mid *m_mid; // +0x274
	char m_pad278[0x438 - 0x274 - 4];
	unsigned char m_flag438; // +0x438
};

class StateMachine
{
public:
	char m_pad00[4];
	Slot8 *m_next; // +4
};

class Rva002645FF
{
public:
	bool rva002645FF();
	char m_pad00[8];
	Object *m_object; // +8
	char m_pad0C[0x30 - 0x0C];
	StateMachine *m_machine; // +0x30
};

class Inner00264F3D
{
public:
	char m_pad00[0x38];
	int m_val38; // +0x38
	unsigned char m_flag3C; // +0x3C
};

class Rva00264F3D
{
public:
	int rva00264F3D();
	char m_pad00[4];
	Inner00264F3D *m_inner; // +4
	Object *m_object; // +8
};

class Rva00264E93
{
public:
	void *rva00264E93();
	char m_pad00[8];
	Object *m_object; // +8
	char m_pad0C[0x30 - 0x0C];
	char *m_ptr30; // +0x30
	char m_pad34[0x40 - 0x34];
	int m_flag40; // +0x40
};

bool Rva002645FF::rva002645FF()
{
	Object *obj = m_object;
	if ((obj->m_flag438 & 1) != 0)
		return true;
	if (obj->testStatus((ObjectStatusTypes)0x26)) {
		Mid *mid = obj->m_mid;
		if (mid != 0) {
			Slot110 *s = mid->m_slot;
			if (s != 0) {
				if (s->isReady())
					return true;
			}
		}
	}
	StateMachine *sm = m_machine;
	if (sm->m_next != 0)
		return sm->m_next->getResult();
	return true;
}

int Rva00264F3D::rva00264F3D()
{
	Inner00264F3D *inner = m_inner;
	if (inner->m_flag3C != 0) {
		Object *obj = m_object;
		if (!obj->testStatus((ObjectStatusTypes)0x0A))
			return 0;
	}
	return inner->m_val38;
}

void *Rva00264E93::rva00264E93()
{
	if (m_object->testStatus((ObjectStatusTypes)0x16)) {
		if (m_flag40 == 0)
			return m_ptr30 + 0x24;
	}
	return 0;
}
