// cl: /DNDEBUG /MD /EHsc
//
// ?rva00468CB6@HordeContain@@QAE_NPAVRva00468CB6A@@PAVObject@@@Z, retail 0x00468CB6 91B.
// Turret goal check: null guards, related via rva002931F5, virtual +0x1BC,
// goal via TurretStateMachine +0x30, second related compare.
// Callers 0x471FFA 0x4726DD, prev 0x468A3F, next 0x468E26.

class Object
{
public:
	Object *rva002931F5(bool checkProducer);
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class Rva00468CB6A
{
public:
	virtual void _v000();
	virtual void _v001();
	virtual void _v002();
	virtual void _v003();
	virtual void _v004();
	virtual void _v005();
	virtual void _v006();
	virtual void _v007();
	virtual void _v008();
	virtual void _v009();
	virtual void _v010();
	virtual void _v011();
	virtual void _v012();
	virtual void _v013();
	virtual void _v014();
	virtual void _v015();
	virtual void _v016();
	virtual void _v017();
	virtual void _v018();
	virtual void _v019();
	virtual void _v020();
	virtual void _v021();
	virtual void _v022();
	virtual void _v023();
	virtual void _v024();
	virtual void _v025();
	virtual void _v026();
	virtual void _v027();
	virtual void _v028();
	virtual void _v029();
	virtual void _v030();
	virtual void _v031();
	virtual void _v032();
	virtual void _v033();
	virtual void _v034();
	virtual void _v035();
	virtual void _v036();
	virtual void _v037();
	virtual void _v038();
	virtual void _v039();
	virtual void _v040();
	virtual void _v041();
	virtual void _v042();
	virtual void _v043();
	virtual void _v044();
	virtual void _v045();
	virtual void _v046();
	virtual void _v047();
	virtual void _v048();
	virtual void _v049();
	virtual void _v050();
	virtual void _v051();
	virtual void _v052();
	virtual void _v053();
	virtual void _v054();
	virtual void _v055();
	virtual void _v056();
	virtual void _v057();
	virtual void _v058();
	virtual void _v059();
	virtual void _v060();
	virtual void _v061();
	virtual void _v062();
	virtual void _v063();
	virtual void _v064();
	virtual void _v065();
	virtual void _v066();
	virtual void _v067();
	virtual void _v068();
	virtual void _v069();
	virtual void _v070();
	virtual void _v071();
	virtual void _v072();
	virtual void _v073();
	virtual void _v074();
	virtual void _v075();
	virtual void _v076();
	virtual void _v077();
	virtual void _v078();
	virtual void _v079();
	virtual void _v080();
	virtual void _v081();
	virtual void _v082();
	virtual void _v083();
	virtual void _v084();
	virtual void _v085();
	virtual void _v086();
	virtual void _v087();
	virtual void _v088();
	virtual void _v089();
	virtual void _v090();
	virtual void _v091();
	virtual void _v092();
	virtual void _v093();
	virtual void _v094();
	virtual void _v095();
	virtual void _v096();
	virtual void _v097();
	virtual void _v098();
	virtual void _v099();
	virtual void _v100();
	virtual void _v101();
	virtual void _v102();
	virtual void _v103();
	virtual void _v104();
	virtual void _v105();
	virtual void _v106();
	virtual void _v107();
	virtual void _v108();
	virtual void _v109();
	virtual void _v110();
	virtual bool isAllowed();
private:
	char m_pad[0x30 - 4];
public:
	TurretStateMachine *m_30;
};

// Both native callers4726DD and471FFA load ECX with primary HordeContain.
// The body does not consume it; stdcall and thiscall body bytes coincide.
// Keep one owner with the call-site-proven member ABI rather than an alias.
class HordeContain { public: bool rva00468CB6(Rva00468CB6A *,Object *); };
bool HordeContain::rva00468CB6(Rva00468CB6A *a, Object *b)
{
	if (a == 0 || b == 0)
		return false;
	Object *related1 = b->rva002931F5(false);
	bool ok = false;
	if (a->isAllowed())
	{
		Object *goal = a->m_30->getGoalObject();
		if (goal != 0)
		{
			if (b == goal)
				ok = true;
			else
			{
				Object *related2 = goal->rva002931F5(false);
				if (related2 != 0 && related1 == related2)
					ok = true;
			}
		}
	}
	return ok;
}
