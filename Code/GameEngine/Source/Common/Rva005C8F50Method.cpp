// cl: /O1 /MD
// stlport
// ?rva005C8F50@Rva005C8F50Elem@@QAEXHH@Z @0x005C8F50 74B filtered erase over vector at +0x38 with conditional TargetObj notify. Evidence: caller 0x005C835D in RangeApplyWrappers plus rowed vector erase 0x0034C117 plus pinned TargetObj method 0x005C8DBF plus prev HostClass005C8F17 layout.
#include <vector>
class TargetObj005C8DBF
{
public:
	void method_005C8DBF(float v);
};
struct BfmePod12
{
	TargetObj005C8DBF *m_obj;
	int m_key;
	float m_val;
};
class Rva005C8F50Elem
{
public:
	void rva005C8F50(int a, int b);
private:
	char m_pad00[8];
	void *m_08;
	char m_pad0C[0x38 - 0x0C];
	_STL::vector<BfmePod12> m_vec38;
	char m_padTail[0x48 - 0x38 - 12];
};
void Rva005C8F50Elem::rva005C8F50(int a, int b)
{
	for (BfmePod12 *it = m_vec38.begin(); it != m_vec38.end();) {
		if (it->m_key == a) {
			if (b == 0 && m_08 != 0)
				it->m_obj->method_005C8DBF(it->m_val);
			it = m_vec38.erase(it);
		} else
			++it;
	}
}
