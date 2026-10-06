// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0006846A@BaseHeightMapRenderObjClass@@QAEXH@Z, retail 0x0006846a, 13 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Virtual forward through slot 0x224 with 0. Retail is mov eax [ecx]
// push 0 call [eax+0x224] ret 4. Evidence: unlock lane; caller at
// 0x0004472F passes TheTerrainRenderObject (BaseHeightMapRenderObjClass*)
// as this with push 1; siblings 0x00043785 0x000447FD same shape;
// abuts prev row 0x000683FF in Rva000683FF.cpp; flags copied from
// neighbours Rva000683FF.cpp and Disp32DwordClearers2.cpp (/O1).
// Owner proven by caller global type; param is generic int (ret 4).

class BaseHeightMapRenderObjClass
{
public:
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
	virtual void v023();
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
	virtual void v060();
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
	virtual void virt224(int arg);
	void rva0006846A(int arg);
};

void BaseHeightMapRenderObjClass::rva0006846A(int arg)
{
	virt224(0);
}
