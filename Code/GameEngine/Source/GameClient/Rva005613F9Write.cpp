// cl: /DNDEBUG /MD
// ?rva005613F9@Rva005613F9@@QAEXPAVFile@@I@Z at 0x005613F9 size 35
// Evidence: chain via 0x0055C9A0 and just-landed 0x003AFC6B; vslot 3 DefaultModuleTemplate; WriteHeader then footer only.
class File;
void Rva0055C9A0WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

class Rva005613F9 {
public:
	void rva005613F9(File *file, unsigned int flags);
};

void Rva005613F9::rva005613F9(File *file, unsigned int flags)
{
	Rva0055C9A0WriteHeader(this, file, &flags);
	Rva003AFC6BWrite(file, &flags);
}
