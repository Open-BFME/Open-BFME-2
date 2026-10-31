// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003E7FD5Get@@YG_NPAVParameter@@@Z retail 0x003E7FD5 104 bytes.
// Evidence: leaf lane free function ret 4 with 1 Parameter arg; caller 0x003EBDD7; prev/next same cl; calls getQualifiedTriggerAreaByName pin plus TacticalView slot 0x118 plus pointInTrigger row.
#include "ascii_string.h"

class ScriptConditions;
class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};
class PolygonTrigger;
#include "../../../../Libraries/Include/Lib/ICoord3D.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
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
class Rva0030B719Shape
{
public:
	float getRadius() const;	// 0x0030B719
};

struct Coord3D;
class PolygonTrigger
{
public:
	bool pointInTrigger(const ICoord3D &position);
	void getCenterPoint(Coord3D *pOutCoord) const; // 0x002E38F3
	char m_pad00[0x8];
	Rva0030B719Shape m_shape; // +0x08
};

bool __stdcall Rva003E7FD5Get(Parameter *parameter)
{
    PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(parameter->getString());
    if (trig)
    {
        float f[3];
        ((TacticalView *)TheTacticalView)->getPos(f);
        ICoord3D pt;
        pt.x = (int)f[0];
        pt.y = (int)f[1];
        pt.z = (int)f[2];
        return trig->pointInTrigger(pt);
    }
    return false;
}
