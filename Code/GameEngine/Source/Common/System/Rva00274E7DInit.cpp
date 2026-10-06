// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /DNDEBUG /MD /GX
// ?Rva00274E7DInit@@YAXXZ, retail 0x00274E7D (1147B): UI image table init.
// Evidence: 4 literal finds via ImageCollection 0x002D92F6 into g_00DFEB70/74/80/84,
// new 0x38 array into g_00DFEB78, 12 rva finds via 0x002D752D from g_00DBB660..694
// into array slots 0-2/4-9/11-13 with slot 10 zeroed, 4 literal finds into
// g_00DFEB88/8C/90/94, flag g_00DFEB6C; unblocks 0x002797BD; prev/next flags.
#include "ascii_string.h"

void *__cdecl operator new[](unsigned int size);

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

struct Rva002D752DNode;
class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

extern ImageCollection *g_00DFF078;
extern Rva002D752D *g_00DFF068;
extern const Image *g_00DFEB70;
extern const Image *g_00DFEB74;
extern const Image *g_00DFEB80;
extern const Image *g_00DFEB84;
extern const Image *g_00DFEB88;
extern const Image *g_00DFEB8C;
extern const Image *g_00DFEB90;
extern const Image *g_00DFEB94;
extern Rva002D752DNode **g_00DFEB78;
extern unsigned char g_00DFEB6C;
extern const char *g_00DBB660;
extern const char *g_00DBB664;
extern const char *g_00DBB668;
extern const char *g_00DBB670;
extern const char *g_00DBB674;
extern const char *g_00DBB678;
extern const char *g_00DBB67C;
extern const char *g_00DBB680;
extern const char *g_00DBB684;
extern const char *g_00DBB68C;
extern const char *g_00DBB690;
extern const char *g_00DBB694;

void Rva00274E7DInit(void)
{
	if (g_00DFEB6C)
		return;
	{
		AsciiString tmp("SCPAmmoFull");
		g_00DFEB70 = g_00DFF078->findImageByName(tmp);
	}
	{
		AsciiString tmp("SCPAmmoEmpty");
		g_00DFEB74 = g_00DFF078->findImageByName(tmp);
	}
	{
		AsciiString tmp("ContainPip");
		g_00DFEB80 = g_00DFF078->findImageByName(tmp);
	}
	{
		AsciiString tmp("ContainPipFrame");
		g_00DFEB84 = g_00DFF078->findImageByName(tmp);
	}
	g_00DFEB78 = (Rva002D752DNode **)operator new[](0x38);
	{
		AsciiString tmp(g_00DBB660);
		g_00DFEB78[0] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB664);
		g_00DFEB78[1] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB668);
		g_00DFEB78[2] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB670);
		g_00DFEB78[4] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB674);
		g_00DFEB78[5] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB678);
		g_00DFEB78[6] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB67C);
		g_00DFEB78[7] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB680);
		g_00DFEB78[8] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB684);
		g_00DFEB78[9] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	g_00DFEB78[10] = 0;
	{
		AsciiString tmp(g_00DBB68C);
		g_00DFEB78[11] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB690);
		g_00DFEB78[12] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB694);
		g_00DFEB78[13] = g_00DFF068->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp("Good_Vet");
		g_00DFEB88 = g_00DFF078->findImageByName(tmp);
	}
	{
		AsciiString tmp("Good_Vet_Dot");
		g_00DFEB8C = g_00DFF078->findImageByName(tmp);
	}
	{
		AsciiString tmp("Evil_Vet");
		g_00DFEB90 = g_00DFF078->findImageByName(tmp);
	}
	{
		AsciiString tmp("Evil_Vet_Dot");
		g_00DFEB94 = g_00DFF078->findImageByName(tmp);
	}
	g_00DFEB6C = 1;
}
