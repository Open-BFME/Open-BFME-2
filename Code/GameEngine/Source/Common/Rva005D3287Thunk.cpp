// cl: /O1 /arch:SSE /G7 /MD
// ?rva005D3287@Rva005D3287@@QAEX_N@Z @0x005D3287 7B
// Evidence: leaf tail-jmp to Impl SetVisibility 0x005D321D; caller 0x00578664; prev 0x005D321D next 0x005D328E.
namespace StrategicHUD
{
class RegionStatsTrayMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionStatsTrayMovieClip::Impl
{
public:
	void SetVisibility(bool flag);
};

class Rva005D3287
{
public:
	void rva005D3287(bool flag);
private:
	StrategicHUD::RegionStatsTrayMovieClip::Impl *m_impl00;
};

void Rva005D3287::rva005D3287(bool flag)
{
	return m_impl00->SetVisibility(flag);
}

// Three more leaf tail-jumps just before 0x005D3287 (0x005D3272, 0x005D3279,
// 0x005D3280, 7B each), from the Palantir forwarders 0x00578616/1E/26:
// the object at +0x00 receives the two ints through the rowed counter
// setters 0x005D30EE, 0x005D3153 and 0x005D31B8 (Rva005D30EEAptCounters.cpp).
class Rva005D30EE
{
public:
	void rva005D30EE(int a, int b);
	void rva005D3153(int a, int b);
	void rva005D31B8(int a, int b);
};

class Rva005D3272
{
public:
	void rva005D3272(int a, int b);
private:
	Rva005D30EE *m_impl00;
};

void Rva005D3272::rva005D3272(int a, int b)
{
	m_impl00->rva005D30EE(a, b);
}

class Rva005D3279
{
public:
	void rva005D3279(int a, int b);
private:
	Rva005D30EE *m_impl00;
};

void Rva005D3279::rva005D3279(int a, int b)
{
	m_impl00->rva005D3153(a, b);
}

class Rva005D3280
{
public:
	void rva005D3280(int a, int b);
private:
	Rva005D30EE *m_impl00;
};

void Rva005D3280::rva005D3280(int a, int b)
{
	m_impl00->rva005D31B8(a, b);
}
