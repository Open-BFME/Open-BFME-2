// cl: /O1 /G7 /DNDEBUG /MD
// Native4DE47E..4DE4E2/100B; WB1286BF0 explicitly names
// PathfinderPosGoalManager::LoadPostProcess. Existing Object+A4
// forwarders and the three18B slot flushes own PathfinderPosGoalManager and its
// three24B slots. Retail reads owner0/template4/flags114/AI258;
// AI virtual224 returns AL. Original predicate and slot state names unknown.
struct Rva004DD843Slot
{
public:
	int m_value;
	char m_pad04[4];
	int m_x24;
	char m_pad0C[4];
	int state;
	int auxiliary;
};
struct GoalTemplate{char pad[0x114];unsigned flags;};
class GoalAIInterface{public:
virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99(); virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107(); virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115(); virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
virtual void slot120(); virtual void slot121(); virtual void slot122(); virtual void slot123(); virtual void slot124(); virtual void slot125(); virtual void slot126(); virtual void slot127();
virtual void slot128(); virtual void slot129(); virtual void slot130(); virtual void slot131(); virtual void slot132(); virtual void slot133(); virtual void slot134(); virtual void slot135();
virtual void slot136();
virtual bool slot137();
};
struct GoalOwner{char pad00[4];GoalTemplate*templ;char pad08[0x258-8];GoalAIInterface*ai;};
class Object;

class PathfinderPosGoalManager
{
public:
	float rva004DD843();
	void SetGoal(int first, float value, int last);
	void rva004DE511(int first, int last);
	void rva004DE4E2(int arg);
	void rva004DDD6E();
	void rva004DDD80();
	void rva004DDD92();
	void RemoveObjPtr(Rva004DD843Slot *slot);
	void LoadPostProcess();
	void AddObjPtr(Rva004DD843Slot *slot);

private:
	Object *m_object;
	Rva004DD843Slot m_slot04;
	Rva004DD843Slot m_slot1C;
	Rva004DD843Slot m_slot34;
};
void PathfinderPosGoalManager::LoadPostProcess(){
 if(m_slot04.m_value!=-666666){m_slot04.state=((GoalOwner *)m_object)->templ->flags&0x2000?4:3;AddObjPtr(&m_slot04);}
 if(m_slot1C.m_value!=-666666){m_slot1C.state=((GoalOwner *)m_object)->ai->slot137()?0:2;AddObjPtr(&m_slot1C);}
}
