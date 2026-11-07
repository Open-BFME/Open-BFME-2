// cl: /DNDEBUG /MD
// ?AddAct@LivingWorldCampaign@@QAEXABURva0052D801Record@@@Z @0x0052D83B 8B
// Evidence: add ecx,0xC tail-jmp to rowed vector push_back 0x0052D801; neighbours share /O1 /G7.
// LivingWorldCampaign's field table 0x008688A8 entry "Act" runs ParseLivingWorldCampaignAct
// 0x00566D83, which appends its parsed act here with the campaign as this; +0x0C is the act
// vector the campaign dtor 0x0052CFB1 destroys. The act counterpart of AddPlayer 0x0052D394.
// reverse/attempt_support/livingworld-act-tu-evidence-20261107/readme.md
typedef int Int;

struct Rva0052D801Record;

namespace _STL {
template <typename T> class allocator;
template <typename T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &v);
};
}

class LivingWorldCampaign
{
	char m_pad[0xC];
	_STL::vector<Rva0052D801Record> m_acts;	// +0x0C
public:
	void AddAct(const Rva0052D801Record &act);
};

void LivingWorldCampaign::AddAct(const Rva0052D801Record &act)
{
	return m_acts.push_back(act);
}
