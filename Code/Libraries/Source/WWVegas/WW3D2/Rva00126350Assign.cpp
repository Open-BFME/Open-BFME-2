// cl: /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// ??4Rva00126350@@QAEAAV0@ABV0@@Z @0x00126350 73B
// Copy assign via rowed RefCountPtr Texture assign then 6 dwords byte then dword.
// Evidence: callee 0x000424D0 row RefCountPtr Texture; caller 0x00126409 0x001685F9; next LineSegment StreakRenderer same flags.
class TextureClass;
template <class T> class RefCountPtr
{
public:
	const RefCountPtr<T> &operator=(const RefCountPtr<T> &other);
private:
	T *m_ptr;
};
class Rva00126350
{
public:
	Rva00126350 &operator=(const Rva00126350 &other);
private:
	RefCountPtr<TextureClass> m_tex;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	unsigned char m_20;
};
Rva00126350 &Rva00126350::operator=(const Rva00126350 &other)
{
	if (this != &other) {
		m_tex = other.m_tex;
		m_4 = other.m_4;
		m_8 = other.m_8;
		m_c = other.m_c;
		m_10 = other.m_10;
		m_14 = other.m_14;
		m_18 = other.m_18;
		m_20 = other.m_20;
		m_1c = other.m_1c;
	}
	return *this;
}

class Rva00126399
{
public:
	const Rva00126399 &operator=(const Rva00126399 &other);
};

const Rva00126399 &Rva00126399::operator=(const Rva00126399 &other)
{
	return (const Rva00126399 &)((RefCountPtr<TextureClass> *)this)->operator=(*(const RefCountPtr<TextureClass> *)&other);
}

