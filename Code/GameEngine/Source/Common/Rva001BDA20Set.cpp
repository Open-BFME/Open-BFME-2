// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva001BDA20Set.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?set@Rva001BDA20@@QAEXABVRva0036CA00Str@@@Z 0x000B28A5 (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva001BDA20
{
	char m_00[0x10];
	Rva0036CA00Str m_10;
	int m_14;

public:
	void set(const Rva0036CA00Str &s);
};

void Rva001BDA20::set(const Rva0036CA00Str &s)
{
	m_10 = s;
	m_14 = 4;
}
