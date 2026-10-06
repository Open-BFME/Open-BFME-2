// cl: /MD
// ?rva000E0EDD@Rva000E0EDD@@QAE_NH@Z @0x000E0EDD 49B
// Evidence: unlock int arg ret 4; array [ecx+eax*4] 3 ints; cmp 2 vs cmp 1 loop; caller 0x000E1CAC in 0x000E1C1A.
class Rva000E0EDD
{
public:
	bool rva000E0EDD(int index);
private:
	int m_arr[3];
};

bool Rva000E0EDD::rva000E0EDD(int index)
{
	if (index >= 0 && index < 3)
		return m_arr[index] == 2;
	for (int i = 0; i < 3; ++i)
		if (m_arr[i] == 1)
			return false;
	return true;
}
