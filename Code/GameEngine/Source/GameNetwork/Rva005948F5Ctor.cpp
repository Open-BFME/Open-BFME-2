// cl: /DNDEBUG /MD /EHsc
// ??0Rva005948F5@@QAE@XZ @0x005948F5 (35B): default ctor for 0x20-byte heap object; caller 0x00595089 news 0x20 then calls; writes +0x00=-1 +0x0C=2 +0x0E=0 +0x10=0 +0x1C=10000 +0x04=0 +0x08=0; no vptr; neighbours ConstZeroGetters and UDPDrainDestructor.
class Rva005948F5
{
public:
	Rva005948F5();
private:
	int m_00;
	int m_04;
	unsigned short m_08;
	char _pad0A[2];
	unsigned short m_0C;
	unsigned short m_0E;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
};
Rva005948F5::Rva005948F5()
{
	m_00 = -1;
	m_0C = 2;
	m_0E = 0;
	m_10 = 0;
	m_1C = 10000;
	m_04 = 0;
	m_08 = 0;
}
