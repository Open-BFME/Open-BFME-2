// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva003F8728@@UAE@XZ retail 0x003F8728 86B
// Own vptr C37314; under EH state 0 the file pointers in the vector at +0xC are
// handed back through the rowed for-each
// ?rva0059E2DC@@YA_NPAPAVFileClass@@0URva0059E2DCBox@@@Z 0x0059E2DC with an
// empty functor temporary (one zeroed byte, pushed as a dword); then the
// vector's inline dtor frees its block with the CRT free.
// Byte twin of Rva003F87A9Dtor.cpp (vptr C37318), sharing its EH handler.
// Names address-derived; functor view as in Rva0059E2DCBox.cpp.

extern "C" void __cdecl free(void *block);

class FileClass;

struct Rva0059E2DCBox
{
};

bool __cdecl rva0059E2DC(FileClass **first, FileClass **last, Rva0059E2DCBox box);

class Rva003F8728Files
{
public:
	~Rva003F8728Files()
	{
		if (m_begin)
			free(m_begin);
	}
	FileClass **begin() { return m_begin; }
	FileClass **end() { return m_end; }

	FileClass **m_begin;
	FileClass **m_end;
	FileClass **m_capacity;
};

class Rva003F8728
{
public:
	virtual ~Rva003F8728();

private:
	char m_pad04[8];
	Rva003F8728Files m_files; // +0x0C
};

Rva003F8728::~Rva003F8728()
{
	rva0059E2DC(m_files.begin(), m_files.end(), Rva0059E2DCBox());
}
