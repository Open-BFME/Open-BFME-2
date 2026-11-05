// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva001808B0@Gen_dtor_00972460@@UAEXXZ, retail 0x001808B0, 171 bytes.
// Chain from 0x0007882F landing: vtable slot 2 of Gen_dtor_00972460 vtable
// 0x007D5010. Copies name to 260B stack buffer via _mbscpy thunk, replaces
// extension with .w3d via strchr IAT, opens File via rowed opener, wraps in
// ChunkLoadClass, checks chunk 0x740, reads 0x44 bytes into new object at
// +0x14, releases File via slot 8. Evidence: vtable slot, callers share.

extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);

typedef unsigned int uint32;
typedef unsigned char uint8;


#include "../../../../GameEngine/Include/Common/File.h"

class FileClass;

File *__cdecl GetGameFilePart(const char *filename, int a, int b);

#include "../WWLib/ChunkLoadClass.h"



void *__cdecl operator new(unsigned int size);

class Gen_dtor_00972460
{
public:
	virtual void f0();
	virtual void f1();
	virtual void rva001808B0();
	char m_pad[0x10];
	void *m_ptr;
	char *m_name;
	int m_unk1C;
	int m_unk20;
};

void Gen_dtor_00972460::rva001808B0()
{
	char buf[0x104];
	_mbscpy(buf, m_name);
	char *dot = strchr(buf, '.');
	if (dot != 0)
		_mbscpy(dot, ".w3d");
	File *file = GetGameFilePart(buf, m_unk1C, m_unk20);
	if (file != 0) {
		// The chunk reader retains its legacy slot-compatible stream view.
		ChunkLoadClass chunk((BFMEChunkInput *)file);
		if (chunk.Open_Chunk() && chunk.Cur_Chunk_ID() == 0x740) {
			void *p = operator new(0x44);
			m_ptr = p;
			chunk.Read(p, 0x44);
		}
		file->close();
	}
}
