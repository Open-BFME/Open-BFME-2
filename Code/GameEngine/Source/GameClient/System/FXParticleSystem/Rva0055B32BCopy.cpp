// cl: /EHs-c-
// ??0Rva0055B32B@@QAE@ABV0@@Z @0x003ADCC7 30B copy with vtable 0x0081D134 and 16-dword rep movsd. Evidence: same vtable as default ctor row 0x0055B32B; caller 0x003ADC95; prev // cl: /O1 /EHs-c-.
struct Keyframe0055B32B
{
	float m_value;
	unsigned int m_frame;
};
struct Block0055B32B
{
	Keyframe0055B32B k[8];
};
class Rva0055B32B
{
public:
	virtual ~Rva0055B32B();
	Rva0055B32B(const Rva0055B32B &other);
private:
	Block0055B32B m_b;
};
Rva0055B32B::Rva0055B32B(const Rva0055B32B &other)
{
	m_b = other.m_b;
}
