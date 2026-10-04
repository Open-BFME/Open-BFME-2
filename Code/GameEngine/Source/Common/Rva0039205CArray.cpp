// cl: /O1 /MD
// ?rva00392CF9@Rva0039205C@@QAEPAVRva004D9A3C@@I@Z 36B @0x00392CF9: bounds-checked element getter stride 0x1C. Layout count at +0 plus array at +8 from dtor row at 0x0039205C plus ctor at 0x003921FA. Evidence: init pin at 0x00392092 plus callers at 0x002A2866 0x002A29E9 0x00392EBF.
class Rva004D9A3C
{
public:
	char m_pad00[0x0C];
	float m_float0C;
	unsigned char m_byte10;
	char m_pad11[0x07];
	int m_int18;
};

extern const float BfmeZeroRange;

extern class GlobalData *TheWritableGlobalData;

class GlobalData
{
public:
	char m_pad[0xA94];
	unsigned int m_count;
};

class Rva00392092Target
{
public:
	void rva00392092();
};

class Rva0039205C
{
public:
	Rva004D9A3C *rva00392CF9(unsigned int index);
	unsigned char rva00392D49(unsigned int index);
	float rva00392D1D(unsigned int index);
	void rva00392196(unsigned int index, int value);
	void rva003921C8(unsigned int index, unsigned char value);
	int rva00392D71(int index);
private:
	int m_count00;
	int m_pad04;
	Rva004D9A3C *m_array08;
};

Rva004D9A3C *Rva0039205C::rva00392CF9(unsigned int index)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index < (unsigned int)m_count00)
		return m_array08 + index;
	return 0;
}

unsigned char Rva0039205C::rva00392D49(unsigned int index)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index < (unsigned int)m_count00)
		return m_array08[index].m_byte10;
	return 0;
}

float Rva0039205C::rva00392D1D(unsigned int index)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index < (unsigned int)m_count00)
		return m_array08[index].m_float0C;
	return BfmeZeroRange;
}

void Rva0039205C::rva00392196(unsigned int index, int value)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index >= TheWritableGlobalData->m_count)
		return;
	m_array08[index].m_int18 = value;
}

void Rva0039205C::rva003921C8(unsigned int index, unsigned char value)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index >= TheWritableGlobalData->m_count)
		return;
	m_array08[index].m_byte10 = value;
}

int Rva0039205C::rva00392D71(int index)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index < (int)TheWritableGlobalData->m_count)
		return m_array08[index].m_int18;
	return -1;
}
