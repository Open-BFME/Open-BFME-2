#ifndef BFME_STL_RECORD_RVA0017341B_H
#define BFME_STL_RECORD_RVA0017341B_H

// Retail establishes a 48-byte stride and twelve scalar word copies.
// Splitting the words into four and eight is a source/codegen inference:
// MSVC 7.1 then uses retail's +24-byte bias in the inlined assignment.
struct Rva0017341BWordsFirst
{
    unsigned words[4];
    __forceinline Rva0017341BWordsFirst &operator=(const Rva0017341BWordsFirst &other)
    {
        words[0] = other.words[0];
        words[1] = other.words[1];
        words[2] = other.words[2];
        words[3] = other.words[3];
        return *this;
    }
};

struct Rva0017341BWordsTail
{
    unsigned words[8];
    __forceinline Rva0017341BWordsTail &operator=(const Rva0017341BWordsTail &other)
    {
        words[0] = other.words[0];
        words[1] = other.words[1];
        words[2] = other.words[2];
        words[3] = other.words[3];
        words[4] = other.words[4];
        words[5] = other.words[5];
        words[6] = other.words[6];
        words[7] = other.words[7];
        return *this;
    }
};

struct Rva0017341BWords
{
    Rva0017341BWordsFirst first;
    Rva0017341BWordsTail tail;
    __forceinline Rva0017341BWords &operator=(const Rva0017341BWords &other)
    {
        first = other.first;
        tail = other.tail;
        return *this;
    }
};

typedef char Rva0017341BWordsSizeCheck[sizeof(Rva0017341BWords) == 48 ? 1 : -1];
#endif
