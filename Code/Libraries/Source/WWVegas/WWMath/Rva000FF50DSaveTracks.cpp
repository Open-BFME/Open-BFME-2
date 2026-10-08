// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep
// ?rva000FF50D@Rva000FF50D@@QAEXXZ, retail 0x000FF50D, 217 bytes.
// Evidence: unlock lane; .wak/.wb literals plus fopen/fwrite/fclose IAT;
// WaterTracks saveTracks donor (W3DWaterTracks.cpp saveTracks with .wak,
// wb, fwrite start/end/type plus count) ported to member filename at +0x28
// and list at +0x10; WaterTracksObj +0x58/+0x60 8B +0x30 4B +0x68 flag
// +0xB0 next; caller 0xFF8FA; neighbours Rva000FE9E3 + pod containers.
#include "ascii_string.h"
#include <stdio.h>
#include <string.h>

extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" __declspec(dllimport) struct _iobuf *__cdecl fopen(const char *path, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *ptr, unsigned int size, unsigned int count, struct _iobuf *file);
extern "C" __declspec(dllimport) int __cdecl fclose(struct _iobuf *file);

struct Vector2
{
	float x;
	float y;
};

class WaterTracksObj
{
public:
	char m_pad00[0x30];
	int m_type;
	char m_pad34[0x58 - 0x34];
	Vector2 m_initStart;
	Vector2 m_initEnd;
	int m_initTimeOffset;
	char m_pad6C[0xB0 - 0x6C];
	WaterTracksObj *m_nextSystem;
};

class Rva000FF50D
{
public:
	void rva000FF50D();
	char m_pad00[0x10];
	WaterTracksObj *m_used;
	char m_pad14[0x28 - 0x14];
	AsciiString m_file;
};

void Rva000FF50D::rva000FF50D()
{
	AsciiString fileName = m_file;
	char path[256];
	const char *data = *(const char **)&fileName;
	_mbscpy(path, data ? data + 8 : "");
	unsigned int len = strlen(path);
	_mbscpy(path + len - 4, ".wak");
	int trackCount = 0;
	struct _iobuf *file = fopen(path, "wb");
	if (file != 0)
	{
		WaterTracksObj *track = m_used;
		while (track != 0)
		{
			if (track->m_initTimeOffset == 0)
			{
				fwrite(&track->m_initStart, 8, 1, file);
				fwrite(&track->m_initEnd, 8, 1, file);
				fwrite(&track->m_type, 4, 1, file);
				++trackCount;
			}
			track = track->m_nextSystem;
		}
		fwrite(&trackCount, 4, 1, file);
		fclose(file);
	}
}
