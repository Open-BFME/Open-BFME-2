// cl: /O1 /arch:SSE /G7 /MD
// ?rva00167EB9@Rva00167EB9@@QAEABVRva00126399@@ABV2@@Z @ 0x00167EB9 11B.
// The caller reaches this at 0x000D03A1; retail adjusts this by +0xE4 then tail-calls
// the rowed Rva00126399 assignment operator at 0x00126399.
class Rva00126399
{
public:
	const Rva00126399 &operator=(const Rva00126399 &other);
};

class Rva00167EB9
{
	char m_pad[0xe4];
	char m_value[4];
public:
	const Rva00126399 &rva00167EB9(const Rva00126399 &other);
};

const Rva00126399 &Rva00167EB9::rva00167EB9(const Rva00126399 &other)
{
	return ((Rva00126399 &)m_value).operator=(other);
}
