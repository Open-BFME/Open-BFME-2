// cl: /MD /EHsc /DNDEBUG
//
// ?rva00098565@Rva00098667Product@@QAEXXZ @0x00098565 14B: virtual slot 9
// (offset 0x24) of vtable 0x007C8358, class of ??0Rva00098667Product@@QAE@XZ.
// Calls rowed ?Rva0030AEA6Copy@@YAXXZ then zeroes +0x64 (last tail dword).
// Layout from donor Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva00098667Product.cpp
// (base 0x4C plus seven tail dwords 0x4C..0x64).

class Rva0030AFC4Base
{
public:
	Rva0030AFC4Base();
	virtual ~Rva0030AFC4Base();
private:
	char m_pad04[0x4C - 4];
};

class Rva00098667Product : public Rva0030AFC4Base
{
public:
	virtual void rva00098565();
private:
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
};

void __cdecl Rva0030AEA6Copy();

void Rva00098667Product::rva00098565()
{
	Rva0030AEA6Copy();
	m_64 = 0;
}
