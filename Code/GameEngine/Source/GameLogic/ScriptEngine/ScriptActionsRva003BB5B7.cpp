// cl: /O1
// ?Rva003BB5B7Do@@YGXPAVParameter@@HPAURGBColor@@@Z @0x003BB5B7 103B: free stdcall Parameter+int+color to Drawable stores.
// Target evidence: ScriptEngine::getUnitNamed 0x003588E7 then Thing::getDrawable 0x005508E2 then v<=0 guard then g_Va00DBA4E4*v/g_00E02D9C then RGBColor::getAsInt 0x00004EA7 vs Object::getIndicatorColor 0x0028B026 then Drawable+0x168+0x16c ret 0xc; caller 0x003CBB2E.
class Parameter;
class Drawable
{
public:
	char m_pad[0x168];
	int m_168;
	int m_16c;
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
struct RGBColor
{
	int getAsInt() const;
};
class Object
{
public:
	int getIndicatorColor() const;
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern ScriptEngine *g_Va009FE16C;
extern int g_Va00DBA4E4;
extern int g_00E02D9C;
void __stdcall Rva003BB5B7Do(Parameter *p, int v, RGBColor *c)
{
	Object *o = g_Va009FE16C->getUnitNamed(p);
	if (!o)
		return;
	Drawable *d = ((Thing *)o)->getDrawable();
	if (!d)
		return;
	if (v <= 0)
		return;
	int scaled = g_Va00DBA4E4 * v / g_00E02D9C;
	int color;
	if (c == 0)
		color = o->getIndicatorColor();
	else
		color = c->getAsInt();
	d->m_168 = scaled;
	d->m_16c = color;
}
