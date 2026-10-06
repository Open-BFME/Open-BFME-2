// cl: /MD
// ?rva004210B0@Rva004210B0@@QAE_NPBVModuleData@@@Z @0x004210B0 32B
// Linear search of vector<ModuleData*> at +8 for pointer equality.
// Evidence: __thiscall via ecx plus ret 4; mov eax [ecx+8] mov ecx [ecx+0xc] loop;
// caller 0x004213E2 conditional push_back to vector at +8; honest Rva class.
class ModuleData;
class Rva004210B0
{
public:
	bool rva004210B0(const ModuleData *data);
private:
	char m_pad[8];
	const ModuleData **m_begin;
	const ModuleData **m_end;
};
bool Rva004210B0::rva004210B0(const ModuleData *data)
{
	for (const ModuleData **it = m_begin; it != m_end; ++it) {
		if (*it == data)
			return true;
	}
	return false;
}
