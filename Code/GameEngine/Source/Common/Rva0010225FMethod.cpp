// cl: /O1 /MD /EHs-c-
// stlport
// ?rva0010225F@Rva0010225F@@QAEXABV?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@@Z @0x0010225F 37B
// Evidence: unlock lane; vector assign 0x001020BA at +4 then null-checked calls 0x00116496 0x00116482 on +0; callers 0x00102284 0x0010231F 0x000B071D
#include <vector>

struct EvaMessageInfo
{
	char m_unported[28];
	EvaMessageInfo();
	EvaMessageInfo(const EvaMessageInfo &);
	~EvaMessageInfo();
};

class Rva00116496
{
public:
	void rva00116496();
};

class Rva00116482
{
public:
	void rva00116482();
};

class Rva0010225F
{
public:
	void rva0010225F(const _STL::vector<EvaMessageInfo> &arg);
private:
	Rva00116496 *m_00;
	_STL::vector<EvaMessageInfo> m_04;
};

void Rva0010225F::rva0010225F(const _STL::vector<EvaMessageInfo> &arg)
{
	m_04 = arg;
	if (m_00) {
		m_00->rva00116496();
		((Rva00116482 *)m_00)->rva00116482();
	}
}
