// ?rva0045F084@StancesBehavior@@QAE_NH@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva0045F084@StancesBehavior@@QAE_NH@Z, retail 0x0045F084, 408 bytes.
// Stance setter: early false when value equals +0x30; Object at +0x08,
// iface at Object+0x250 via slot 0x7c, stance-4 triple check via slots
// 0xf0/0x5c/0x60 with re-fetch; new==3 aiIdle(0) via Object+0x258+0x20;
// ModuleData key at +0x04+0x08 via global map g_00E031D4 rowed 0x4260DE;
// name table switch via pinned keyToName 0x148C95 plus Object rows
// 0x28EB42/0x28EA91; b slot 0x260; classify via rowed 0x45ED4B; broadcast
// via rowed forEach 0x45EF55 with rowed forwarder 0x5CB260; AI tail via
// rowed aiIdle 0x1E8A38 plus rowed 0x262D40 and slot 0x1b8.
// Note: callers declare void ?rva0045F084@StancesBehavior@@QAEXH@Z but
// retail sets al (false on no-change/missing, true on change), so bool.
// LINK BONUS names the void pin; byte gate needs bool.

class AsciiString;
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004260DE
{
public:
	int *rva004260DE(int key);
};
extern Rva004260DE *g_00E031D4;

struct StanceEntry
{
	int m_name;
	int m_arg;
};
struct StanceTable
{
	int m_header;
	StanceEntry m_entries[6];
};

struct IfaceBig
{
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual bool v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual bool v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void v142();
	virtual void v143();
	virtual void v144();
	virtual void v145();
	virtual void v146();
	virtual void v147();
	virtual void v148();
	virtual void v149();
	virtual void v150();
	virtual void v151();
	virtual void doIt(int value);
};

struct IfaceA
{
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual IfaceBig *get();
};

enum CommandSourceType
{
	SOURCE_0 = 0,
	SOURCE_1 = 1,
	SOURCE_2 = 2
};
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
};

class AIUpdateInterface
{
public:
	virtual void a000();
	virtual void a001();
	virtual void a002();
	virtual void a003();
	virtual void a004();
	virtual void a005();
	virtual void a006();
	virtual void a007();
	virtual void a008();
	virtual void a009();
	virtual void a010();
	virtual void a011();
	virtual void a012();
	virtual void a013();
	virtual void a014();
	virtual void a015();
	virtual void a016();
	virtual void a017();
	virtual void a018();
	virtual void a019();
	virtual void a020();
	virtual void a021();
	virtual void a022();
	virtual void a023();
	virtual void a024();
	virtual void a025();
	virtual void a026();
	virtual void a027();
	virtual void a028();
	virtual void a029();
	virtual void a030();
	virtual void a031();
	virtual void a032();
	virtual void a033();
	virtual void a034();
	virtual void a035();
	virtual void a036();
	virtual void a037();
	virtual void a038();
	virtual void a039();
	virtual void a040();
	virtual void a041();
	virtual void a042();
	virtual void a043();
	virtual void a044();
	virtual void a045();
	virtual void a046();
	virtual void a047();
	virtual void a048();
	virtual void a049();
	virtual void a050();
	virtual void a051();
	virtual void a052();
	virtual void a053();
	virtual void a054();
	virtual void a055();
	virtual void a056();
	virtual void a057();
	virtual void a058();
	virtual void a059();
	virtual void a060();
	virtual void a061();
	virtual void a062();
	virtual void a063();
	virtual void a064();
	virtual void a065();
	virtual void a066();
	virtual void a067();
	virtual void a068();
	virtual void a069();
	virtual void a070();
	virtual void a071();
	virtual void a072();
	virtual void a073();
	virtual void a074();
	virtual void a075();
	virtual void a076();
	virtual void a077();
	virtual void a078();
	virtual void a079();
	virtual void a080();
	virtual void a081();
	virtual void a082();
	virtual void a083();
	virtual void a084();
	virtual void a085();
	virtual void a086();
	virtual void a087();
	virtual void a088();
	virtual void a089();
	virtual void a090();
	virtual void a091();
	virtual void a092();
	virtual void a093();
	virtual void a094();
	virtual void a095();
	virtual void a096();
	virtual void a097();
	virtual void a098();
	virtual void a099();
	virtual void a100();
	virtual void a101();
	virtual void a102();
	virtual void a103();
	virtual void a104();
	virtual void a105();
	virtual void a106();
	virtual void a107();
	virtual void a108();
	virtual void a109();
	virtual bool a110();
	void rva00262D40(int mode);
	char m_pad04[0x20 - 4];
	AICommandInterface m_cmd20;
};

class Object
{
public:
	void rva0028EB42(const AsciiString &name);
	bool rva0028EA91(const AsciiString &name, int v);
	char m_pad00[0x250];
	IfaceA *m_250;
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai258;
};

class ModuleData
{
public:
	char m_pad00[8];
	int m_key08;
};

class Thing;
class Rva0045EF55Listener
{
public:
	void notify(void *arg, int value, int extra);
};
struct Rva0045EEC4Call;
class Rva0045EF55List
{
public:
	void forEach(void (Rva0045EF55Listener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva0045EEC4Call &call);
	Rva0045EF55Listener **m_begin;
	Rva0045EF55Listener **m_end;
	Rva0045EF55Listener **m_capacity;
	unsigned int m_index;
};
class Rva005CB260
{
public:
	void rva005CB260();
};

class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class UpdateModuleInterface
{
public:
	virtual void updateSlot() = 0;
};
class UpdateModule : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned char m_pad14[0x20 - 0x14];
};
class StancesBehavior : public UpdateModule
{
public:
	int rva0045ED4B() const;
	bool rva0045F084(int value);
private:
	Rva0045EF55List m_list20;
	int m_30;
};

// ?rva0045F084@StancesBehavior@@QAE_NH@Z present-unmatched
bool StancesBehavior::rva0045F084(int value)
{
	Object *obj = m_object;
	if (value == m_30)
		return false;
	IfaceA *iface = obj->m_250;
	IfaceBig *b = 0;
	if (iface != 0)
		b = iface->get();
	else
		b = 0;
	if (b != 0)
	{
		if (m_30 == 4)
		{
			if (b->v060() && b->v023())
			{
				b->v024();
				IfaceA *iface2 = obj->m_250;
				if (iface2 != 0)
					b = iface2->get();
				else
					b = 0;
			}
		}
	}
	if (value == 3)
	{
		AIUpdateInterface *ai = obj->m_ai258;
		if (ai != 0)
			ai->m_cmd20.aiIdle(SOURCE_0);
	}
	int key = m_moduleData->m_key08;
	if (key == 0)
		return false;
	int *found = g_00E031D4->rva004260DE(key);
	if (found == 0)
		return false;
	StanceTable *table = (StanceTable *)found;
	int oldName = table->m_entries[m_30].m_name;
	int newName = table->m_entries[value].m_name;
	if (oldName != newName)
	{
		if (oldName != 0)
			obj->rva0028EB42(TheNameKeyGenerator->keyToName((NameKeyType)oldName));
		if (newName != 0)
			obj->rva0028EA91(TheNameKeyGenerator->keyToName((NameKeyType)newName), -1);
	}
	if (b != 0)
		b->doIt(table->m_entries[value].m_arg);
	const int oldStance = m_30;
	const int oldClass = rva0045ED4B();
	m_30 = value;
	const int newClass = rva0045ED4B();
	if (oldStance != 0 && oldClass == newClass)
		return true;
	m_list20.forEach((void (Rva0045EF55Listener::*)(void *, int, int))&Rva005CB260::rva005CB260, this, oldClass, newClass);
	AIUpdateInterface *ai2 = obj->m_ai258;
	if (ai2 == 0)
		return true;
	if (!ai2->a110())
		return true;
	if (value == 1)
		ai2->rva00262D40(0);
	else if (value == 3 || value == 4)
		ai2->rva00262D40(1);
	else if (oldStance == 1 || oldStance == 3)
		ai2->m_cmd20.aiIdle(SOURCE_2);
	return true;
}
