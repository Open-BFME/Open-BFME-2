// cl: /O1 /MD /EHsc /DNDEBUG
// ZH doCameraFollowNamed supplies lock/snap/follow semantics. Retail3BC1B2
// adds Drawable ID through neutral getter55A88B and a float play argument.
// Its dispatcher at3CC8D3 and RET12 prove Parameter*, Bool, float free ABI.
// Getter5508E2 is Thing::getDrawable, not the folded BuildListInfo getter.
// Nested arguments and a direct cast of canonical TheTacticalView retain
// native vtableEDI and global THIS reload across the getter calls.
class Parameter;

class Object
{
public:
	char m_pad[0x74];
	int m_74;
};

class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActionsFollowView
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004();
	virtual void s005(); virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009();
	virtual void s010(); virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014();
	virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023(); virtual void s024();
	virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029();
	virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034();
	virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043(); virtual void s044();
	virtual void s045(); virtual void s046(); virtual void s047(); virtual void s048(); virtual void s049();
	virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054();
	virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064();
	virtual void s065(); virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069();
	virtual void s070(); virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074();
	virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083(); virtual void s084();
	virtual void s085(); virtual void s086(); virtual void s087(); virtual void s088(); virtual void s089();
	virtual void s090(); virtual void s091(); virtual void s092(); virtual void s093(); virtual void s094();
	virtual void s095(); virtual void s096();
	virtual void s097(int v);
	virtual void s098();
	virtual void s099(int a, float b);
	virtual void s100(); virtual void s101(); virtual void s102();
	virtual void s103(int v);
};

class View;
extern View *TheTacticalView;

void __stdcall Rva003BC1B2Do(Parameter *p, bool flag, float v)
{
	Object *obj = TheScriptEngine->getUnitNamed(p);
	if (obj == 0)
		return;
	reinterpret_cast<ScriptActionsFollowView *>(TheTacticalView)->s097(obj->m_74);
	reinterpret_cast<ScriptActionsFollowView *>(TheTacticalView)->s103(((Rva0055A88BDwordField *)((Thing *)obj)->getDrawable())->get());
	if (flag)
		reinterpret_cast<ScriptActionsFollowView *>(TheTacticalView)->s098();
	reinterpret_cast<ScriptActionsFollowView *>(TheTacticalView)->s099(1, v);
}
