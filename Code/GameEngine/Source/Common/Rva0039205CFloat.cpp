// cl: /O1 /MD /arch:SSE
// ?rva00392129@Rva0039205C@@QAEXIM@Z 54B @0x00392129: float setter stride 0x1C at +0x0C. Layout count at +0 plus array at +8 from Rva0039205CArray rows. Evidence: init pin at 0x00392092 plus GlobalData count plus callers at 0x00393477 0x00393CDB 0x00393F51.
class Rva004D9A3C
{
public:
	char m_pad00[0x0C];
	float m_float0C;
	unsigned char m_byte10;
	char m_pad11[0x07];
	int m_int18;
};

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
	void rva00392129(unsigned int index, float value);
private:
	int m_count00;
	int m_pad04;
	Rva004D9A3C *m_array08;
};

void Rva0039205C::rva00392129(unsigned int index, float value)
{
	if (m_array08 == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index >= TheWritableGlobalData->m_count)
		return;
	m_array08[index].m_float0C = value;
}
