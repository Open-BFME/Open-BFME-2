// cl: /O1 /MD /arch:SSE
// ?Rva005D7860Check@@YG_NPAVObject@@@Z @0x005D7860 101B via vtable slot 6 class Rva005D7855 gap between dtor and deleting dtor; callees rowed getControllingPlayer get rva002A7461; floats g_Va00BBB8D8 length_estimate_factor.
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};
class Rva002A7389
{
public:
	int get(int);
};
class Rva002A7461
{
public:
	int rva002A7461();
};
extern float g_Va00BBB8D8;
extern "C" const float length_estimate_factor;
bool __stdcall Rva005D7860Check(Object *obj)
{
	Player *player = obj->getControllingPlayer();
	char *base = (char *)player;
	int limit = *(int *)(base + 0x94);
	void *holder = base + 0x60;
	float f = (float)((Rva002A7389 *)holder)->get(1);
	int total = ((Rva002A7461 *)holder)->rva002A7461();
	float totalF = (float)total;
	if (limit <= 1000)
		return false;
	float ratio = f / totalF;
	float diff = g_Va00BBB8D8 - ratio;
	if (diff > length_estimate_factor)
		return true;
	return false;
}
