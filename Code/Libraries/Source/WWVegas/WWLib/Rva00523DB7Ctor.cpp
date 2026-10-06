// cl: /MD
// ??0Rva00523DB7@@QAE@PBHABV?$StringBase@D@@@Z @0x00523DB7 29B:
// 2-arg ctor copying int from *arg1 into +0 and StringBase<char> from arg2
// into +4 via rowed copy 0x000365F0. Called by _Construct wrapper 0x0023FC23
// plus 4 other 132B sites. Owner unproven, honest Rva name.
template <typename T>
class StringBase
{
private:
	StringBase(const StringBase &other);
	friend class Rva00523DB7;
private:
	void *m_data;
};
class Rva00523DB7
{
public:
	Rva00523DB7(const int *p, const StringBase<char> &s);
private:
	int m_00;
	StringBase<char> m_04;
};

Rva00523DB7::Rva00523DB7(const int *p, const StringBase<char> &s)
	: m_00(*p), m_04(s)
{
}
