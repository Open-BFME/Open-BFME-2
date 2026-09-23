// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /O2 /Ob0 /Ireference/open-bfme-1/Code/GameEngine/Source/Common

struct Rva0025A3F0Inner
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva0025A3F0Sub
{
	Rva0025A3F0Inner *m_holder;
};

class Rva0025A3F0
{
public:
	bool eq(int a) const;
};

bool Rva0025A3F0::eq(int a) const
{
	return a == ((const Rva0025A3F0Sub *)((const char *)this - 0x1C))->m_holder->m_08;
}
