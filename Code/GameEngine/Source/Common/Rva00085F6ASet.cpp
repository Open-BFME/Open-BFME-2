// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?rva00085F6A@Rva00085F6A@@QAE_NH@Z 0x00085F6A 62B: thiscall sets m_110 to arg validates via Rva00075725Check restores on false; chain from 0x00075725
bool __cdecl Rva00075725Check(int index, int arg);

class Rva00085F6A
{
public:
	char m_pad[0x10C];
	int m_10C;
	int m_110;
	bool rva00085F6A(int val);
};

bool Rva00085F6A::rva00085F6A(int val)
{
	int oldIdx = m_10C;
	int oldVal = m_110;
	m_110 = val;
	if (oldIdx == 0)
		return true;
	if (val == 0)
		return true;
	bool ok = Rva00075725Check(val, oldIdx);
	if (!ok) {
		m_110 = oldVal;
		return ok;
	}
	return true;
}
