// ?getStance@CommandButton@@QAEHH@Z retail 0x0035B6B8 16B
// Array indexer returning m_234[index]. Evidence: unlock lane plus 6 callers
// plus ecx-first thiscall shape with ret-4 honest address name.

class CommandButton
{
public:
	int getStance(int index);

private:
	char m_pad[0x234];
	int *m_arr;
};

int CommandButton::getStance(int index)
{
	return m_arr[index];
}
