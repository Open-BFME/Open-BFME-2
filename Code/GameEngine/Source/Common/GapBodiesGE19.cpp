// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (nineteenth batch; see GapBodiesGE01.cpp). Each begins after its
// neighbour's padding and ends in its own ret. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "ascii_string.h"

// --- 0x0002BEFB (19B): exchange two dwords through their pointers.
void rva0002BEFB(int *first, int *second)
{
	int t = *first;
	*first = *second;
	*second = t;
}

// --- 0x0002C655 (20B): bucket of a key: the empty hash functor at +0 (the
// rowed rts::hash<AsciiString> 0x0002BF8C, whose header names this caller)
// modulo the bucket count.
namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
}

class Rva0002C655
{
public:
	unsigned int rva0002C655(const AsciiString &key, unsigned int bucketCount) const;
private:
	rts::hash<AsciiString> m_hash;
};

unsigned int Rva0002C655::rva0002C655(const AsciiString &key, unsigned int bucketCount) const
{
	return m_hash(key) % bucketCount;
}

// --- 0x0002C7E8 (21B): case-insensitive key equality through the rowed
// StringBase<char>::compareNoCase 0x00006A00; the functor's this is unused.
class Rva0002C7E8
{
public:
	bool rva0002C7E8(const AsciiString &a, const AsciiString &other) const;
};

bool Rva0002C7E8::rva0002C7E8(const AsciiString &asciiString, const AsciiString &other) const
{
	return ((const StringBase<char> &)asciiString).compareNoCase((const StringBase<char> &)other) == 0;
}

// --- 0x0002BA86 (18B), unreferenced in retail: forwards filename and access
// to the rowed three-argument FileSystem::openFile (0x00600C34) with a zero
// third argument, `this` passed straight through in ecx. The owner is the
// callee's class; the member name is address-derived.
class File;

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
	File *rva0002BA86(const char *filename, int access);
};

File *FileSystem::rva0002BA86(const char *filename, int access)
{
	return openFile(filename, access, 0);
}

// --- 0x0002BB71 (14B), unreferenced: whether the words at +0x24 and +0x20
// differ (the shape of Rva003B03F3 in VtableSlotBodiesR3.cpp).
class Rva0002BB71
{
public:
	bool rva0002BB71();
private:
	char m_pad00[0x20];
	int m_value20;
	int m_value24;
};

bool Rva0002BB71::rva0002BB71()
{
	return m_value24 != m_value20;
}

// --- 0x0002BF21 (14B), unreferenced: copy the byte at +0 out through the
// pointer argument and report success.
class Rva0002BF21
{
public:
	int rva0002BF21(char *out);
private:
	char m_00;
};

int Rva0002BF21::rva0002BF21(char *out)
{
	*out = m_00;
	return 1;
}
