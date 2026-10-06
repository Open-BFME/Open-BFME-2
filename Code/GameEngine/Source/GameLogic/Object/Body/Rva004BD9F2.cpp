// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva004BD9F2@Rva004BD9F2@@QAEMXZ @0x004BD9F2 19B
// No callers; honest address name. Retail reads signed byte at this+0x5F7
// (movsx) and returns it as float via fild temp.

class Rva004BD9F2
{
public:
	float rva004BD9F2();
private:
	char m_pad[0x5F7];
	signed char m_val;
};

float Rva004BD9F2::rva004BD9F2()
{
	return (float)m_val;
}
