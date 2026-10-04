// ?Rva002C98E2Get@@YGMPAVObject@@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
// ?Rva002C98E2Get@@YGMPAVObject@@@Z, retail 0x002C98E2, 123 bytes.
// Free float helper over Object::rva0028C149 0x0028C149 plus testStatus.
// Evidence: unlock lane; callers 0x002C997A 0x002C99EE; prev TU flags.
class Object;
enum ObjectStatusTypes { STATUS_3A = 0x3a };
extern float g_Va00BBB8D8;
extern float BfmeZeroRange;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class Object
{
public:
	bool rva0028C149(int attr, float *val, int arg);
	bool testStatus(ObjectStatusTypes s) const;
};
float __stdcall Rva002C98E2Get(Object *obj)
{
	float v4 = g_Va00BBB8D8;
	float v8 = g_Va00BBB8D8;
	if (obj->rva0028C149(7, &v8, 0)) {
		v4 = v8 + *(const volatile float *)&g_Va00BBB8D8;
	}
	float *mult = (float *)((char *)TheWritableGlobalData + 0x1224);
	if (*mult >= BfmeZeroRange) {
		if (obj->testStatus(STATUS_3A)) {
			v4 = v4 * *(const volatile float *)mult;
		}
	}
	return v4;
}
