// cl: /O1 /DNDEBUG /MD
// ?rva000B3EB3@ModelConditionFlags@@QBE_NXZ @0x000B3EB3 20B
// 19-word ModelConditionFlags any-nonzero predicate; callers 0x002791E7 0x000B49FF;
// LINK BONUS 3 files 301B; no donor hits.
class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
private:
	unsigned int m_bits[19];
};
bool ModelConditionFlags::rva000B3EB3() const
{
	for (unsigned int i = 0; i < 19; i++)
		if (m_bits[i] != 0)
			return true;
	return false;
}
