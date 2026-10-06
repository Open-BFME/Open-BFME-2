// ?rva004ED69B@Rva004ED471@@QAEXPBVModelNodeClass@HLodClass@@@Z
// cl: /MD
// ?rva004ED69B@Rva004ED471@@QAEXPBVModelNodeClass@HLodClass@@@Z at 0x004ED69B (55B).
// HLod ModelNode vector push_back with 0x14 stride: fast Assign+add 0x14 when
// finish != end, else overflow rva004ED471(pos value dummy 1 1).
// Evidence: callees rowed Assign 0x004ED0D7 and Finish 0x004ED471; callers
// 0x004ED6F8 and 0x004EDBD2; unblocks 0x004ED6D2 and 0x004EDA8C;
// prev file names this the push_back overflow path.
class HLodClass
{
public:
	class ModelNodeClass
	{
	public:
		void *Model;
		int BoneIndex;
		char Offset[12];
	};
};

void __cdecl Rva004ED0D7Assign(HLodClass::ModelNodeClass *dst, const HLodClass::ModelNodeClass *src);

struct _BfmeAllocatorHintType
{
};

class Rva004ED471
{
public:
	void rva004ED471(HLodClass::ModelNodeClass *pos, const HLodClass::ModelNodeClass *value, const void *dummy, unsigned int count, bool atend);
	void rva004ED69B(const HLodClass::ModelNodeClass *value);
	HLodClass::ModelNodeClass *m_start;
	HLodClass::ModelNodeClass *m_finish;
	HLodClass::ModelNodeClass *m_end;
};

void Rva004ED471::rva004ED69B(const HLodClass::ModelNodeClass *value)
{
	if (m_finish != m_end) {
		Rva004ED0D7Assign(m_finish, value);
		++m_finish;
	} else {
		_BfmeAllocatorHintType hint;
		rva004ED471(m_finish, value, &hint, 1, true);
	}
}
