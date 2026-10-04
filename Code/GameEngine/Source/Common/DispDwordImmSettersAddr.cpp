// The members of the DispDwordImmSetters.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
class Rva0028576DDwordImmSetter
{
public:
	void apply();

	char m_lead[0x9C];
	unsigned int m_value;
};

void Rva0028576DDwordImmSetter::apply()
{
	m_value = 0x006D7B50;
}
