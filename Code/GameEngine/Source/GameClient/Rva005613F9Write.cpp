// cl: /DNDEBUG /MD
// Retail export 1939: DefaultModuleTemplate<6>::writeINI, 0x005613F9, 35 bytes.
// This writer has no fields to serialize after the common header.
class File;
void Rva0055C9A0WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

namespace FXParticleSystem {

template <int CATEGORY>
class DefaultModuleTemplate {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
};

template <int CATEGORY>
void DefaultModuleTemplate<CATEGORY>::writeINI(File &file, unsigned int flags) const
{
	Rva0055C9A0WriteHeader(this, &file, &flags);
	Rva003AFC6BWrite(&file, &flags);
}

template void DefaultModuleTemplate<6>::writeINI(File &, unsigned int) const;

// Exports 1942, 1954 and 1959 fold these draw writers onto the
// same complete body. These views declare only the out-of-line writer.
class ButterflyDrawModuleTemplate {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
};

void ButterflyDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
	Rva0055C9A0WriteHeader(this, &file, &flags);
	Rva003AFC6BWrite(&file, &flags);
}

class QuadDrawModuleTemplate {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
};

void QuadDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
	Rva0055C9A0WriteHeader(this, &file, &flags);
	Rva003AFC6BWrite(&file, &flags);
}

class StreakDrawModuleTemplate {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
};

void StreakDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
	Rva0055C9A0WriteHeader(this, &file, &flags);
	Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
