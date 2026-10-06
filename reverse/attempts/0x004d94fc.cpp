// ?rva004D94FC@@YA_NPAVObject@@@Z
// partial score=0.95 date=2026-10-07
struct Object
{
	float getVisionRange() const;
};
class Rva00DFF0F8AI
{
public:
	int rva002FFFA3(Object *, float, int, int, int, int);
};
extern void *g_00DFF0F8;
bool rva004D94FC(Object *object)
{
	volatile unsigned int *flags = (volatile unsigned int *)((char *)object + 0x11c);
	if (((*flags >> 29) & 1) == 0)
		return false;
	return ((Rva00DFF0F8AI *)g_00DFF0F8)->rva002FFFA3(
		object, object->getVisionRange(), 0x6e, 0, 0, 1) != 0;
}
