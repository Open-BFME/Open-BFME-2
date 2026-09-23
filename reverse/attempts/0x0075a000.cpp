// ?RetailCollisionManagerData@@QAE@XZ
// partial score=0.85 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc
#include <string.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class RetailCollisionManagerData
{
public:
	RetailCollisionManagerData();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18[0x2B7B];
	int m_AE04;
	int m_AE08;
	int m_AE0C;
	int m_AE10[0x493];
	int m_C05C;
	int m_C060;
	int m_C064;
	int m_C068;
	unsigned char m_C06C;
	unsigned char m_C06D;
	unsigned char m_pad6E[2];
};
RetailCollisionManagerData::RetailCollisionManagerData()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_AE08 = 0;
	m_AE0C = 0;
	_ReadWriteBarrier();
	int *arrayOne = m_18;
	memset(arrayOne, 0, sizeof(m_18));
	arrayOne[0x2B7B] = 0;
	m_C060 = 0;
	m_C064 = 0;
	_ReadWriteBarrier();
	int *arrayTwo = m_AE10;
	memset(arrayTwo, 0, sizeof(m_AE10));
	arrayTwo[0x493] = 0;
	m_C06C = 0;
	m_C06D = 0;
	_ReadWriteBarrier();
	m_C068 = 3;
	_ReadWriteBarrier();
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
}
