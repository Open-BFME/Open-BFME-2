// cl: /DNDEBUG /MD /O1 /arch:SSE
// ??RRva002BBC1CCmp@@QBE_NABVRva004F6093Holder@@0@Z @0x002B367C 66B. Out-of-line
// bool comparator functor of the refcounted Rva004F6093Holder elements (a
// pointer to an Rva0037DCA5) via the float at +8 then the rowed Get.
// Evidence: SSE sub plus cvttss2si plus rowed Get 0x0037DCA5 twice; ret 8 with
// 2 args; every retail caller is the _STL::sort family over Rva004F6093Holder
// (sort 0x002BBC1C, stlport_*_rva002bbc1c.cpp) and passes ecx = &comp with both
// elements by reference, so it is the functor's operator() (the body leaves
// ecx unused). Formerly rowed as the stdcall view Rva002B367CLess.
class Rva0037DCA5
{
public:
	int rva0037DCA5();
	char m_pad00[8];
	float m08;
};

class Rva004F6093Holder
{
public:
	Rva0037DCA5 *m_ptr;
};

struct Rva002BBC1CCmp
{
	bool operator()(const Rva004F6093Holder &a, const Rva004F6093Holder &b) const;
};

bool Rva002BBC1CCmp::operator()(const Rva004F6093Holder &a, const Rva004F6093Holder &b) const
{
	Rva0037DCA5 *pa = a.m_ptr;
	Rva0037DCA5 *pb = b.m_ptr;
	int diff = (int)(pa->m08 - pb->m08);
	if (diff == 0) {
		int va = pb->rva0037DCA5();
		int vb = pa->rva0037DCA5();
		return vb < va;
	}
	return diff < 0;
}
