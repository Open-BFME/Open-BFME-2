#pragma once
// Native string-record hash ABI. The insertion at 0x00418A12 compares the key through
// StringBase<char>; copy at 0x0041890F constructs it before the verified 32-byte value.
// Node creator at 0x004189ED allocates 40 bytes and constructs the 36-byte record at +4.
// Original application identities and field meanings remain unasserted.
#include "ascii_string.h"

class Rva004186F2
{
public:
	Rva004186F2(const Rva004186F2 &other);
	~Rva004186F2();

private:
	char m_pad[0xC];
};

// Each 12-byte member is reached through an inline copy of a holder,
// which gives retail's lea/lea/push argument order at +0xC.
struct Rva004188B6Part
{
	__forceinline Rva004188B6Part(const Rva004188B6Part &other) : m_value(other.m_value) {}

	Rva004186F2 m_value;
};

struct Rva004188B6
{
	Rva004188B6(const Rva004188B6 &other);
	~Rva004188B6();

	Rva004188B6Part m_00;
	Rva004188B6Part m_0C;
	AsciiString m_18;
	char m_1C;
	char m_1D;
};


struct Rva0041890FRecord
{
    Rva0041890FRecord(const Rva0041890FRecord &other);
    Rva0041890FRecord(const AsciiString &name, const Rva004188B6 &mapped);
    AsciiString key;
    Rva004188B6 value;
};
struct Rva00418A12Node
{
    Rva00418A12Node *next;
    Rva0041890FRecord value;
};
struct Rva00418A12Result
{
    Rva00418A12Node *node;
    void *table;
    bool inserted;
};
class Rva00418A8EHost
{
public:
    int outer(int outputAddress, int recordAddress);
    Rva00418A12Result *apply(Rva00418A12Result *output, const Rva0041890FRecord &record);
    Rva00418A12Node *newNode(const Rva0041890FRecord &record);
private:
    void *m_unused00;
    Rva00418A12Node **m_buckets;
    Rva00418A12Node **m_end;
    int m_unused0C;
    int m_size;
};
typedef char VerifyStringRecord32[(sizeof(Rva004188B6)==32)?1:-1];
typedef char VerifyStringHashValue36[(sizeof(Rva0041890FRecord)==36)?1:-1];
typedef char VerifyStringHashNode40[(sizeof(Rva00418A12Node)==40)?1:-1];
typedef char VerifyStringHashResult12[(sizeof(Rva00418A12Result)==12)?1:-1];
