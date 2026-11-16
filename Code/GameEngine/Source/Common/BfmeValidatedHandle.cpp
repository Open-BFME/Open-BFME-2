// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversion for the validated handle setter at 0x0073B5F0.

enum FilterTypes {};
enum FilterModes {};

bool __cdecl Rva00075725Check(int index, int arg);

class BfmeValidatedHandle
{
public:
	bool setValue(void *value);

private:
	char m_pad0[0x10c];
	void *volatile m_value;
	void *m_reference;
};

bool BfmeValidatedHandle::setValue(void *value)
{
	void *oldValue = m_value;
	m_value = value;

	if (value != 0 && m_reference != 0 &&
		!Rva00075725Check(
			reinterpret_cast<int>(m_reference),
			reinterpret_cast<int>(value)))
	{
		m_value = oldValue;
		return false;
	}

	return true;
}
