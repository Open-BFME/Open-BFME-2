// cl: /O1 /DNDEBUG /MD
// ?rva0029895A@Object@@QAEXPAUBfmeCopyElementA@@@Z @0x0029895A 31B lane=chain
// Evidence: calls 0x0028AB75 just landed plus rowed bfmeAssign 0x00064605; member +0xA8 BfmeCopyElementA; callers 0x004868BF 0x004BE90C; prev 0x00298893 next 0x00298C0B /O1 /DNDEBUG /MD.
struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);
};

class Object
{
public:
	void rva0029895A(BfmeCopyElementA *src);
	void rva0028AB75(bool flag);
private:
	char _00[0xA8];
	BfmeCopyElementA m_a8;
};

void Object::rva0029895A(BfmeCopyElementA *src)
{
	m_a8.bfmeAssign(src);
	rva0028AB75(false);
}
