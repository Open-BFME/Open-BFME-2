// cl: /DNDEBUG /MD
// ?Rva002B367CLess@@YG_NPAPAVRva0037DCA5@@0@Z @0x002B367C 66B. Stdcall bool
// comparator of Rva0037DCA5 pointers via float at +8 then rowed Get.
// Evidence: SSE sub plus cvttss2si plus rowed Get 0x0037DCA5 twice; ret 8
// 2 args; 12 callers; unblocks 6.
class Rva0037DCA5
{
public:
	int rva0037DCA5();
	char m_pad00[8];
	float m08;
};

bool __stdcall Rva002B367CLess(Rva0037DCA5 **a, Rva0037DCA5 **b)
{
	Rva0037DCA5 *pa = *a;
	Rva0037DCA5 *pb = *b;
	int diff = (int)(pa->m08 - pb->m08);
	if (diff == 0) {
		int va = pb->rva0037DCA5();
		int vb = pa->rva0037DCA5();
		return vb < va;
	}
	return diff < 0;
}
