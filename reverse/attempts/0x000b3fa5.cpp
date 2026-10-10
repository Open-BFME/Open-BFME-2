// ?rva000B3FA5@ModelConditionFlags@@QAEXHH@Z
// partial score=0.85 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva000B3FA5@ModelConditionFlags@@QAEXHH@Z @0x000B3FA5 43B bank (register-allocation near miss)
class ModelConditionFlags
{
public:
	void rva000B3FA5(int bit, int value);
private:
	unsigned int m_words[19];
};
void ModelConditionFlags::rva000B3FA5(int bit, int value)
{
	unsigned int *p = m_words + (bit >> 5);
	*p ^= ((unsigned int)(0 - value) ^ *p) & (1u << (bit & 31));
}
