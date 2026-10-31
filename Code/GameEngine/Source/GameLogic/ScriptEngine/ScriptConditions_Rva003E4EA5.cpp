// ?Rva003E4EA5Get@@YG_NPAVParameter@@@Z
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// @0x003E4EA5 48B leaf single-param terrain-tactical check via TheTerrainLogic
// slot 0x88 plus TheTacticalView slot 0x6C. Evidence: caller 0x003EBDBF;
// prev 0x003E4BFA evaluateSkirmishPlayerHasBeenAttackedByPlayer; next
// 0x003E514F Rva003E514FCheck.
class Parameter;
class AsciiString;
class Waypoint;
class Object;
class TerrainLogic
{
public:
	bool anyBridgesDamageStatesChanged() { return m_bridgeDamageStatesChanged; }
	bool isBridgeRepaired(const Object *bridge);
	bool isBridgeBroken(const Object *bridge);
	virtual void _d00(), _d01(), _d02(), _d03(), _d04(), _d05(), _d06();
	virtual void _d07(), _d08(), _d09(), _d10(), _d11(), _d12(), _d13();
	virtual void _d14(), _d15(), _d16(), _d17(), _d18(), _d19(), _d20();
	virtual void _d21(), _d22(), _d23(), _d24(), _d25(), _d26(), _d27();
	virtual void _d28(), _d29(), _d30(), _d31(), _d32(), _d33();
	virtual Waypoint *getWaypointByName(const AsciiString &name);
	char m_pad04[0x40];
	bool m_bridgeDamageStatesChanged; // +0x44
	char m_pad45[0x3];
};
extern TerrainLogic *TheTerrainLogic;
class TacticalView
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
	virtual bool slot6C(int arg);
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
	virtual void getPos(float *out);
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
	virtual void _v111();
	virtual void _v112();
	virtual void _v113();
	virtual void _v114();
	virtual void _v115();
	virtual void _v116();
	virtual void _v117();
	virtual void _v118();
	virtual void _v119();
	virtual void _v120();
	virtual void _v121();
	virtual void _v122();
	virtual void _v123();
	virtual void _v124();
	virtual void _v125();
	virtual void _v126();
	virtual void _v127();
	virtual void _v128();
	virtual void _v129();
	virtual void _v130();
	virtual void _v131();
	virtual void _v132();
	virtual void _v133();
	virtual void _v134();
	virtual void _v135();
	virtual void _v136();
	virtual void _v137();
	virtual void _v138();
	virtual void _v139();
	virtual void _v140();
	virtual void _v141();
	virtual void _v142();
	virtual float slot23C();
	virtual float slot240();
	virtual float slot244();
	virtual bool slot248();
};
extern class View *TheTacticalView;

bool __stdcall Rva003E4EA5Get(Parameter *parameter)
{
	void *cell = TheTerrainLogic->getWaypointByName(*(const AsciiString *)((char *)parameter + 0x10));
	if (cell) {
		int val = *(int *)((char *)cell + 4);
		return ((TacticalView *)TheTacticalView)->slot6C(val);
	}
	return false;
}
