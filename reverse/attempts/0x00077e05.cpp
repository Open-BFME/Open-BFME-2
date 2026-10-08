// ?Rva00077E05Load@@YAJPBDPAK@Z
// partial score=0.72 date=2026-10-08
class Rva00077E05ShaderBuffer
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual unsigned long release();
	virtual const unsigned long *getBufferPointer();
};

extern long __stdcall Rva0062AF3E(const char *source, unsigned long size,
	const void *defines, void *include, unsigned long flags,
	Rva00077E05ShaderBuffer **shader, Rva00077E05ShaderBuffer **errors);

struct Rva00077E05LoadState
{
	Rva00077E05ShaderBuffer *errors;
	int attempt;
	Rva00077E05ShaderBuffer *shader;
};

long __cdecl Rva00077E05Load(const char *strFilePath, unsigned long *pHandle)
{
	Rva00077E05LoadState state;
	File *volatile file;
	try
	{
		state.attempt = 0;
		for (; state.attempt < 10; ++state.attempt) {
			state.shader = 0;
			state.errors = 0;
			file = TheFileSystem->openFile(strFilePath, File::READ | File::BINARY, 0);
			if (file != 0)
				goto hasFile;
			__asm { push 0x00BC66EC }
		reportFailure:
			((void (__stdcall *)(void))OutputDebugStringA)();
			return (long)0x80004005L;

		hasFile:

			FileInfo fileInfo;
			TheFileSystem->getFileInfo(AsciiString(strFilePath), &fileInfo);
			unsigned long fileSize = fileInfo.sizeLow;

			char *source = (char *)HeapAlloc(GetProcessHeap(), 8, fileSize + 8);
			if (source == 0) {
				__asm { push 0x00BC66C0 }
				goto reportFailure;
			}

			((Rva00077D0FFileView *)file)->read(source, fileSize);
			source[fileSize] = 0;
			((Rva00077D0FFileView *)file)->close();

			long result = Rva0062AF3E(source, fileSize, 0, 0, 0, &state.shader, &state.errors);
			HeapFree(GetProcessHeap(), 0, source);
			if (result < 0) {
				if (state.shader != 0) {
					state.shader->release();
					state.shader = 0;
				}
				if (state.errors != 0) {
					state.errors->getBufferPointer();
					state.errors->release();
				}
				if (state.attempt >= 9)
					return (long)0x80004005L;
				continue;
			}

			long hr = DX8Wrapper::_Get_D3D_Device8()->m_vtable->m_createShaderB(
				DX8Wrapper::_Get_D3D_Device8(), state.shader->getBufferPointer(), pHandle);
			state.shader->release();
			if (hr < 0) {
				__asm { push 0x00BC66A4 }
				goto reportFailure;
			}
		}
		return 0;
	}
	catch (...)
	{
		OutputDebugStringA("Error opening file \n");
		return (long)0x80004005L;
	}

	return 0;
}
