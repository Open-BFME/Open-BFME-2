// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ModelSMConditionInfo::validateTurretInfo: WB921FA0; nativeBBE86..BBF4B197B RET4.
// BF1/ZH ModelConditionInfo validates angle/pitch bones. Target stores24B
// records in a vector atD0/D4 and validates at most one. Keep current rowed
// accessor and pristine-bone provider identities; returned animation-record
// prefix holds the string tested by native1E2F. No new aliases or pins.
// The accessor's existing const-char-pointer spelling is an opaque return
// ABI view. WB's first field/length test proves the returned record begins
// with the StringBase prefix; retain the provider's original declaration.

#include <vector>
#include "ascii_string.h"
template<> bool StringBase<char>::isEmpty() const;

class Rva000B4A9F {public: const char *rva000B4A9F();};
void setFPMode();
int Rva000B2CBDGet();

class Rva000BBDDF
{
public:
	void *rva000BBDDF(int key, int *slot) const;
};

struct Rva000BBE86Rec
{
	int m_key0;
	int m_key4;
	char m_pad[8];
	int m_slot10;
	int m_slot14;
};

class ModelSMConditionInfo
{
public:
	void validateTurretInfo(const Rva000BBDDF *arg);

	char m_pad[0xD0];
	_STL::vector<Rva000BBE86Rec> m_turrets;
	char m_padDC[0xF5 - 0xDC];
	unsigned char m_flag;
};

void ModelSMConditionInfo::validateTurretInfo(const Rva000BBDDF *arg)
{
	if (m_flag)
		return;
	setFPMode();
	const StringBase<char> *text = reinterpret_cast<const StringBase<char> *>(
		reinterpret_cast<Rva000B4A9F *>(this)->rva000B4A9F());
	for (int index = 0; index < 1; ++index) {
		if (index >= m_turrets.size())
			break;
		Rva000BBE86Rec &rec = m_turrets[index];
		if ((unsigned char)Rva000B2CBDGet() == 0 || text->isEmpty()) {
			rec.m_slot10 = 0;
			rec.m_slot14 = 0;
			continue;
		}
		if (rec.m_key0) {
			if (!arg->rva000BBDDF(rec.m_key0, &rec.m_slot10))
				rec.m_slot10 = 0;
		} else {
			rec.m_slot10 = 0;
		}
		if (rec.m_key4) {
			if (!arg->rva000BBDDF(rec.m_key4, &rec.m_slot14))
				rec.m_slot14 = 0;
		} else {
			rec.m_slot14 = 0;
		}
	}
	m_flag = 1;
}
