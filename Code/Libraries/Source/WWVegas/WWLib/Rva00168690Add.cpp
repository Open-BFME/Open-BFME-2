// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
// ?rva00168690@Rva00168690@@QAEXABVVector3@@M@Z @0x00168690 42B
// Unlock callee of 0x000D0091; two SimpleDynVec Adds.
// Evidence: retail push esi push 0 push arg lea ecx [esi+0xc4] call Vector3 Add; push 0 lea eax [esp+0x10] push eax lea ecx [esi+0xd4] call float Add; ret 8; callees rowed 0x001002C5 0x001683C3; callers unclaimed.
class Vector3;
struct BfmePod4 { int a[1]; };
template <typename T> class SimpleDynVecClass
{
public:
	bool Add(const T &v, int i);
	bool Delete(int index, bool allow_shrink);
	int Count() const { return m_activeCount; }
private:
	char m_data[12];
	int m_activeCount;
};
class Rva00168690
{
public:
	void rva00168690(const Vector3 &v, float f);
	void rva001686BA(int index);
private:
	char m_pad00[0xC4];
	SimpleDynVecClass<Vector3> m_c4;
	SimpleDynVecClass<float> m_d4;
};
void Rva00168690::rva00168690(const Vector3 &v, float f)
{
	m_c4.Add(v, 0);
	m_d4.Add(f, 0);
}
void Rva00168690::rva001686BA(int index)
{
	if ((unsigned int)index < (unsigned int)m_c4.Count())
	{
		m_c4.Delete(index, true);
		((SimpleDynVecClass<BfmePod4> *)&m_d4)->Delete(index, true);
	}
}
