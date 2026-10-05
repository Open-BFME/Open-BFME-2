// cl: /O1
// ?Rva003E5105Check@@YG_NPAVParameter@@0@Z
// retail 0x003E5105 74B leaf free stdcall bool of 2x Parameter ret 8 from 0x003EC0F3. Evidence:
// rowed ScriptEngine::getUnitNamed twice via g_Va009FE16C plus pin rva002F477E via g_Va009FF0F8+0x10
// pathfinder with (object from to 0); Object +0x38 Coord3D; siblings 0x003E4F79 0x003E514F /O1.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter
{
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_38;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern ScriptEngine *g_Va009FE16C;

class Pathfinder
{
public:
	bool rva002F477E(Object *obj, const Coord3D *from, const Coord3D *to, int x);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_10;
};
extern AI *g_Va009FF0F8;

bool __stdcall Rva003E5105Check(Parameter *a, Parameter *b)
{
	Object *o1 = g_Va009FE16C->getUnitNamed(a);
	if (!o1)
		return false;
	Object *o2 = g_Va009FE16C->getUnitNamed(b);
	if (!o2)
		return false;
	Pathfinder *pf = g_Va009FF0F8->m_10;
	return pf->rva002F477E(o1, &o1->m_38, &o2->m_38, 0);
}
