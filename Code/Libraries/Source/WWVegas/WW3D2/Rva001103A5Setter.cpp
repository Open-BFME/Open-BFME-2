// cl: /Ireference/shims/bfmestages /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva001103A5@Rva001103A5@@QAIXABV?$RefCountPtr@VTextureClass@@@@@Z @0x001103A5 49B via fastcall texture-slot setter
// evidence: retail compares [this+4] vs [edx] then RefCountPtr<TextureClass> operator= row 0x000424D0; callers 0x000A9F98 x3
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};
class TextureClass : public TextureBaseClass
{
};
template<class T>
class RefCountPtr
{
public:
	T *Peek() const { return Referent; }
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};
class Rva001103A5
{
public:
	bool m_flag0;
	bool m_flag1;
	RefCountPtr<TextureClass> m_tex;
	void __fastcall rva001103A5(RefCountPtr<TextureClass> const &other);
};
void __fastcall Rva001103A5::rva001103A5(RefCountPtr<TextureClass> const &other)
{
	TextureClass *mine = m_tex.Peek();
	TextureClass *theirs = other.Peek();
	if (mine == theirs)
		return;
	unsigned char theirsNonNull = (unsigned char)(theirs != 0);
	unsigned char mineNonNull = (unsigned char)(mine != 0);
	if (mineNonNull != theirsNonNull)
		m_flag0 = true;
	m_tex = other;
	m_flag1 = true;
}
