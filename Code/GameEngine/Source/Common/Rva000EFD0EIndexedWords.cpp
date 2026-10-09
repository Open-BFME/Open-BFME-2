// Native EFD0E/13 and F0D22/13 prove strides12/6 and base pointers+10/+0C.
// Donor1281192f68 Rva007B80D0Arr.cpp, unchanged from6d943; internal element types unknown.
// Opaque records preserve measured strides without asserting the donor element fields.
// Full receiver layouts and original class/method names remain unknown.
// cl: /GX- /MD

struct Rva000EFD0ERecord12
{
	unsigned char opaque[12];
};

class Rva000EFD0EIndexed
{
public:
	Rva000EFD0ERecord12 *rva000EFD0E(int index);

	char m_pad[0x10];
	Rva000EFD0ERecord12 *m_items;
};

Rva000EFD0ERecord12 *Rva000EFD0EIndexed::rva000EFD0E(int index)
{
	return m_items + index;
}

struct Rva000F0D22Record6
{
	unsigned char opaque[6];
};

class Rva000F0D22Indexed
{
public:
	Rva000F0D22Record6 *rva000F0D22(int index);

	char m_pad[0x0c];
	Rva000F0D22Record6 *m_items;
};

Rva000F0D22Record6 *Rva000F0D22Indexed::rva000F0D22(int index)
{
	return m_items + index;
}


// Clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d whole WWLib/
// mixfile.cpp emits VectorClass<FileInfoStruct>::operator[] as a source lead.
// Other donor element names emit the same bytes, so no container/element
// identity is asserted. NativeF0BE4..F0BF1 follows complete RET0 atF0BE3
// and precedes a new EH prologue: stack word times12 plus receiver word+4,
// returned in EAX with RET4 and no pointed data access or bounds test.
// This consumed-prefix view retains raw32 address arithmetic; original
// receiver, field meaning, signedness and complete layout remain unknown.
struct Rva000F0BE4IndexedWords
{
    unsigned int unknown0;
    unsigned int addressBits;
    unsigned int elementAddressBits(unsigned int index) const;
};
unsigned int Rva000F0BE4IndexedWords::elementAddressBits(unsigned int index) const
{
    return addressBits + index * 12u;
}
