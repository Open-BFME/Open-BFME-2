// cl: /MD
// ?rva0006F219@Rva0006F219@@QAE_NPAVRenderObjClass@@@Z retail 0x0006F219 38B placeholder
// Evidence: LINK BONUS via 0x0006F94A; caller 0x0006F9AD; callees rowed Add 0x0006EF29 twice; layout lists at +0x74 plus +0x114; prev 0x0006F1A6 next 0x0006F24A
class RenderObjClass;

template <typename T>
class RefMultiListClass
{
public:
	bool Add(T *obj, bool flag);
};

class Rva0006F219
{
public:
	bool rva0006F219(RenderObjClass *obj);
};

bool Rva0006F219::rva0006F219(RenderObjClass *obj)
{
	((RefMultiListClass<RenderObjClass> *)((char *)this + 0x114))->Add(obj, true);
	return ((RefMultiListClass<RenderObjClass> *)((char *)this + 0x74))->Add(obj, true);
}
