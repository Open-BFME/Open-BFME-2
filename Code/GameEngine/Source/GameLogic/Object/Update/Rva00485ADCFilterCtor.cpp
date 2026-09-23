// cl: /O1 /DNDEBUG /MD /GX
//
// ??0Rva00485ADCFilter@@QAE@XZ, retail 0x00485ADC, 83 bytes. EldestKindof
// filter holder: an ObjectFilter at +0 built through the opaque 0x3623E5
// pin, fed by two 28B FixedStorage temps from the prototype at 0x00DFEFA4
// through the 0x362087 pin. Called on the +0x4C member of
// CreateObjectDieIfEldestKindofModuleData (0x00485E19) and the +0x138
// member of StatusBitsUpgradeIfEldestKindofModuleData (0x002547D1); both
// factories prove the owners. Shape follows AttachUpdateModuleDataCtor
// (filter with dtor for EH state 0, FixedStorage temps by value). The
// Rva name is honest: the address is proven, the filter role is proven
// by the callees, but no donor names the holder class.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

class Rva00485ADCFilter
{
public:
	Rva00485ADCFilter();

private:
	Rva003623E5Member m_filter; // +0
};

// ??0Rva00485ADCFilter@@QAE@XZ @0x485ADC
Rva00485ADCFilter::Rva00485ADCFilter()
{
	m_filter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
