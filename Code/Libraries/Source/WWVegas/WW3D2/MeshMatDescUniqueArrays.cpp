// cl: /Ireference/shims/meshmatdesclayout /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva0015B8C0@MeshMatDescClass@@QAEXXZ 0x0015B8C0 157B unlock between Make_Color_Array_Unique and Install_UV_Array loop 4 at +0xb8 callee 0x0015B110 returning RefPtr
class RefCountClass
{
public:
	virtual void Delete();
	int m_refCount;
	void Add_Ref() { ++m_refCount; }
	void Release_Ref() { if (--m_refCount == 0) Delete(); }
	int Num_Refs() { return m_refCount; }
};

class RefPtr
{
public:
	RefCountClass *m_ptr;
	RefPtr(RefCountClass *p = 0) : m_ptr(p) {}
	RefPtr(const RefPtr &other) : m_ptr(other.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
	~RefPtr() { if (m_ptr) m_ptr->Release_Ref(); }
};

class Rva0015B110Owner : public RefCountClass
{
public:
	RefPtr rva0015b110();
};

class MeshMatDescClass
{
public:
	void rva0015B8C0();
	char m_pad[0xB8];
	Rva0015B110Owner *m_array[4];
};

void MeshMatDescClass::rva0015B8C0()
{
	Rva0015B110Owner **slot = m_array;
	int count = 4;
	do {
		if (*slot != 0 && (*slot)->Num_Refs() > 1) {
			RefPtr tmp = (*slot)->rva0015b110();
			if (tmp.m_ptr != 0) {
				tmp.m_ptr->Add_Ref();
			}
			if (*slot != 0) {
				(*slot)->Release_Ref();
			}
			*slot = (Rva0015B110Owner *)tmp.m_ptr;
		}
		slot++;
		count--;
	} while (count != 0);
}
