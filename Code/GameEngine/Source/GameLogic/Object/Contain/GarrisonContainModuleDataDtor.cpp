// cl: /O1 /MD /EHsc /DNDEBUG
//
// ??1GarrisonContainModuleData@@UAE@XZ, retail 0x00257507, 56 bytes.
// Target evidence: base ctor 0x0047978F installs vtable 0x00C462D8 and zeroes
// +0xA4 (AsciiString zero) after calling Rva base 0x00465124; this body
// destroys +0xA4 via 0x00036410 then base 0x00257481. Called by HordeGarrison
// deleting chain 0x002579E9->0x00257A05 (vtable 0x007F4328 slot 0) plus three
// 0x0047 callers. Donor BFME1 GarrisonContainModuleDataCtorThunk plus
// GarrisonContain.cpp XIV: HordeTransport 5B-jmp precedent for POD derived.

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

class __declspec(novtable) OpenContainModuleData
{
public:
	virtual ~OpenContainModuleData();

private:
	unsigned char m_pad[0x98 - 4];
};

class __declspec(novtable) GarrisonContainModuleData : public OpenContainModuleData
{
public:
	virtual ~GarrisonContainModuleData();

private:
	unsigned char m_pad98[0xA4 - 0x98];
	StringBase<char> m_strA4;
	int m_padA8;
};

GarrisonContainModuleData::~GarrisonContainModuleData()
{
}
