// cl: /MD
// ?Rva006CD230Path@@YAXPBURva006CD230Node@@PAPAD@Z, retail 0x006CD230 (112 bytes, cdecl). The owner is
// unproven (address token): appends a node's path to the buffer cursor, parents first, each joined by
// '/'; a root writes "_level" and its 17-bit signed level at +0x58. The cursor ends on the terminator.
// The name at +0x08 is an EAStringC (rowed data-plus-eight accessor 0x00620090).
extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" char *__cdecl strcpy(char *dest, const char *src);
extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strcpy, strlen)

class EAStringC
{
public:
	const char *rva00620090() const;
};

struct Rva006CD230Node
{
	char m_pad00[8];
	EAStringC m_name;		// +0x08
	char m_pad0c[0x48 - 0x0C];
	const Rva006CD230Node *m_parent;	// +0x48
	char m_pad4c[0x58 - 0x4C];
	int m_level : 17;		// +0x58
};

void Rva006CD230Path(const Rva006CD230Node *node, char **cursor)
{
	if (node->m_parent) {
		Rva006CD230Path(node->m_parent, cursor);
		**cursor = '/';
		*cursor = *cursor + 1;
		strcpy(*cursor, node->m_name.rva00620090());
	} else {
		sprintf(*cursor, "_level%d", node->m_level);
	}
	*cursor += strlen(*cursor);
}
