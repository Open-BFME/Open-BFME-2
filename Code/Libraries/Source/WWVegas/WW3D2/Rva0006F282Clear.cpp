// cl: /O1 /DNDEBUG /MD
// ?rva0006F282@Rva0006F282@@QAEXXZ @0x0006F282 25B: thiscall drain via Peek_Head gated Internal_Remove_List_Head loop. Evidence: callees rowed Internal_Remove_List_Head 0x006109A0 and Peek_Head RenderObj 0x0006EFAD; callers 0x00071285; prev/next WW3D2 BfmeRefSceneList family.
class MultiListObjectClass;
class RenderObjClass;
class GenericMultiListClass
{
protected:
	MultiListObjectClass *Internal_Remove_List_Head(void);
};
template <class T> class RefMultiListClass : public GenericMultiListClass
{
public:
	T *Peek_Head(void);
};
class Rva0006F282 : public RefMultiListClass<RenderObjClass>
{
public:
	void rva0006F282(void);
};
void Rva0006F282::rva0006F282(void)
{
	while (Peek_Head() != 0)
		Internal_Remove_List_Head();
}
