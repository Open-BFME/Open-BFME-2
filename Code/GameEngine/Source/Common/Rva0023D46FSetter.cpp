// cl: /O1 /MD /GX
// ?rva0023D46F@Rva0023D46F@@QAEPAV1@PAVBfmeDfe6e4@@@Z @0x0023D46F (24B):
// refcounted pointer setter returning this. Retail: push esi; esi=ecx;
// ecx=[esp+8]; [esi]=ecx; je skip; call BfmeDfe6e4::_M_rva00625476 (0x225476)
// on the stored pointer; eax=esi; pop esi; ret 4. Single rowed callee;
// address-derived outer name, shared BfmeDfe6e4 view for the mangling.
class BfmeDfe6e4
{
public:
	void _M_rva00625476();
};

class Rva0023D46F
{
public:
	Rva0023D46F *rva0023D46F(BfmeDfe6e4 *arg);
private:
	BfmeDfe6e4 *m_ptr;
};

// ?rva0023D46F@Rva0023D46F@@QAEPAV1@PAVBfmeDfe6e4@@@Z
Rva0023D46F *Rva0023D46F::rva0023D46F(BfmeDfe6e4 *arg)
{
	m_ptr = arg;
	if (arg != 0) {
		arg->_M_rva00625476();
	}
	return this;
}
