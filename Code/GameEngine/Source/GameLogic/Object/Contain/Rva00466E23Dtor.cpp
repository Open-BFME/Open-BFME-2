// cl: /EHsc /MD
// ??1Rva00466E23@@QAE@XZ retail 0x00466E23 53B
// Non-virtual dtor destroying two StringBase<char> members at +0 and +4
// via rowed releaseBuffer 0x00036410 (reverse order +4 then +0) with
// __EH_prolog frame 0x00629188. Evidence: two releaseBuffer calls with
// lea ecx,[esi+4] then mov ecx,esi plus and/or EH states; no vptr store;
// callers at 0x00466EC5 0x00467DD6 0x004689CB plus jmp at 0x00467794;
// neighbours CaveContainModuleDataCtor and StringRecordCopy. Honest Rva name.
template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva00466E23
{
public:
	~Rva00466E23();
private:
	StringBase<char> m_00;
	StringBase<char> m_04;
};
Rva00466E23::~Rva00466E23()
{
}
