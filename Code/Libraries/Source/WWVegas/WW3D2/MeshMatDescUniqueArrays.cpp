// cl: /Ireference/shims/meshmatdesclayout /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva0015B8C0@MeshMatDescClass@@QAEXXZ 0x0015B8C0 157B unlock between Make_Color_Array_Unique and Install_UV_Array loop 4 at +0xb8 callee 0x0015B110 returning RefPtr
#include "MeshMatDescClass.h"

class RefPtr
{
public:
	RefCountClass *m_ptr;
	RefPtr(RefCountClass *refCount = 0) : m_ptr(refCount) {}
	RefPtr(const RefPtr &other) : m_ptr(other.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
	~RefPtr() { if (m_ptr) m_ptr->Release_Ref(); }
};

class Rva0015B110Owner : public RefCountClass
{
public:
	RefPtr rva0015b110();
};

void MeshMatDescClass::rva0015B8C0()
{
	RefCountClass **slot = field_B8;
	int count = 4;
	do {
		if (*slot != 0 && (*slot)->Num_Refs() > 1) {
			RefPtr tmp = ((Rva0015B110Owner *)*slot)->rva0015b110();
			if (tmp.m_ptr != 0) {
				tmp.m_ptr->Add_Ref();
			}
			if (*slot != 0) {
				(*slot)->Release_Ref();
			}
			*slot = tmp.m_ptr;
		}
		slot++;
		count--;
	} while (count != 0);
}
