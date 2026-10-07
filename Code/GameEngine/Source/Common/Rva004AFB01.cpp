// cl: /DNDEBUG /MD /O1 /arch:SSE /G7

// ?rva004AFB01@Rva004AFB01@@QAEHXZ @0x004AFB01 21B.
// Identity is unproven; the address name follows the packet. Retail loads
// the argument through this+8 -> +0x264 -> +0x24, then calls the rowed helper
// at this+4. Those offsets are target evidence; their semantic names are not.
class Rva004AF531
{
public:
	int rva004AF531(int value);
};

struct Rva004AFB01Record
{
	char m_pad[0x24];
	int m_value;
};

struct Rva004AFB01Context
{
	char m_pad[0x264];
	Rva004AFB01Record *m_record;
};

class Rva004AFB01
{
public:
	int rva004AFB01();
	char m_pad[4];
	Rva004AF531 *m_helper;
	Rva004AFB01Context *m_context;
};

int Rva004AFB01::rva004AFB01()
{
	return m_helper->rva004AF531(m_context->m_record->m_value);
}
