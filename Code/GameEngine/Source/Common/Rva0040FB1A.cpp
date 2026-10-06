// cl: /O1 /MD
// ??0Rva0040FB1A@@QAE@XZ @0x0040FB1A 20B
// evidence: frameless this-returning zeroing ctor beside Object forwarder; caller at 0x00221935; LINK 1 file 17B
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva0040FB1A
{
public:
	Rva0040FB1A();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};
Rva0040FB1A::Rva0040FB1A()
{
	m_00 = 0;
	m_04 = 0;
	_ReadWriteBarrier();
	m_10 = -1;
	m_08 = 0;
	m_0C = 0;
}
