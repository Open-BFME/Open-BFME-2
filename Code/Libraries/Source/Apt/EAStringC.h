// Target facts: EAStringC has no base, vptr or virtual functions. Its default constructor (RVA 0x006D2F90), copy constructor (0x006D2FC0), reserve constructor (0x006D45F0), fill constructor (0x006D4640) and C-string constructor (0x006D4C80) write only the representation pointer at +0; the destructor (0x006D3010) loads it and calls FreeData (0x006D2EB0), without a table store. Array steps at 0x0070B603 and 0x0070DB95 prove sizeof 4. The ledger spells the type as class EAStringC.
// Target facts: the representation has unsigned words at +0 (GetInternalRefCount, 0x006D2E10), +2 (size, 0x006D3750 and SetSize, 0x006D3BC0), +4 (GetInternalMaxSize, 0x006D2DF0) and +6 (hash, 0x006D2F40 and 0x006D3BA0); text starts at +8 (0x00620090 and GetAt, 0x006D3020). FreeData decrements a word and frees capacity+9 bytes. The empty singleton at VA 0x00DDC020 starts 01 01 00 00 00 00 00 00 00; it is data, not a vtable. This is not BfmeStringData's 32-bit-refcount layout.
// Target facts: all declared method names and signatures below retain the EAStringC ledger rows or existing retail-call bindings. Copy construction (0x006D2FC0) increments the shared buffer's word refcount; assignment (0x006D3030) increments the source before releasing the destination. These and destruction stay out of line. The fill constructor (0x006D4640) reserves its second argument and fills with its first argument's low byte. The bounded Append call binds 0x006D52A0; the null predicate call at 0x0070B692 binds 0x006CD4A0; the adjacent-constant comparison at 0x0070B5FA binds 0x006D36C0; scoped lifetime calls in 0x006FD3F0 bind 0x006D2F90 and 0x006D3010. Method RVAs are given beside their declarations; data is a neutral name for the pointer retail assertions call m_pData.
#pragma once
#ifndef BFME2_EASTRINGC_H
#define BFME2_EASTRINGC_H

class EAStringC
{
public:
    class StringDataC
    {
    public:
        unsigned short m_uRefCount;
        unsigned short m_uSize;
        unsigned short m_uMaxSize;
        unsigned short m_uHash;
    };

    enum CBPushZero
    {
        CB_NO_PUSH_ZERO,
        CB_PUSH_ZERO
    };

    EAStringC(); // 0x006D2F90
    EAStringC(const EAStringC &other); // 0x006D2FC0
    EAStringC(const char *text); // 0x006D4C80
    EAStringC(unsigned int size); // 0x006D45F0
    EAStringC(unsigned int fillChar, unsigned int size); // 0x006D4640
    ~EAStringC(); // 0x006D3010
    EAStringC &operator=(const EAStringC &other); // 0x006D3030
    EAStringC operator+(const EAStringC &other) const; // 0x006D46C0
    EAStringC operator+(const char *other) const; // 0x006D4F70

    static void FreeData(StringDataC *data); // 0x006D2EB0
    unsigned int GetInternalMaxSize() const; // 0x006D2DF0
    void setCapacityWord_Rva006D2E00(unsigned int value); // 0x006D2E00
    unsigned int GetInternalRefCount() const; // 0x006D2E10
    void SetInternalRefCount(unsigned int value); // 0x006D2E20
    void rva006D2E70(); // 0x006D2E70
    bool IsEmpty() const; // 0x006D2F30
    unsigned short rva006D2F40() const; // 0x006D2F40
    EAStringC &clear(); // 0x006D2F90
    EAStringC *initializeEmpty_Rva006D2FA0(unsigned int ignored); // 0x006D2FA0
    int GetAt(int index) const; // 0x006D3020
    bool IsEqualTo(const EAStringC *other) const; // 0x006D3090
    bool rva006D30D0(const EAStringC *other) const; // 0x006D30D0
    bool operator<(const EAStringC &other) const; // 0x006D3130
    bool operator<=(const EAStringC &other) const; // 0x006D3190
    bool operator>(const EAStringC &other) const; // 0x006D31F0
    bool operator>=(const EAStringC &other) const; // 0x006D3210
    bool operator<(const char *other) const; // 0x006D32F0
    bool operator<=(const char *other) const; // 0x006D3350
    bool operator>(const char *other) const; // 0x006D33B0
    bool operator>=(const char *other) const; // 0x006D3410
    void rva006D3470(); // 0x006D3470
    bool rva006D3490(const char *text) const; // 0x006D3490
    bool rva006D3510(const char *text) const; // 0x006D3510
    bool rva006D3560(const EAStringC *other) const; // 0x006D3560
    int Compare(const char *text) const; // 0x006D35A0
    int Compare(const EAStringC &other) const; // 0x006D3610
    int rva006D3670(const char *text) const; // 0x006D3670
    int rva006D36C0(const EAStringC *other) const; // 0x006D36C0
    bool rva006D36F0(const EAStringC *other) const; // 0x006D36F0
    unsigned int rva006D3750() const; // 0x006D3750
    void Reserve(int size); // 0x006D3760
    int Find(const char *text, int start = 0); // 0x006D3870
    int Find(char character, int start = 0); // 0x006D38E0
    int rva006D3920(const char *text); // 0x006D3920
    int rva006D3980(int value); // 0x006D3980
    int rva006D39B0(int value, const char *text); // 0x006D39B0
    int rva006D3A10(int value, int value2); // 0x006D3A10
    int Replace(char oldCharacter, char newCharacter); // 0x006D3A40
    bool startsWith(const char *text) const; // 0x006D3AD0
    bool endsWith(const char *text) const; // 0x006D3B30
    void rva006D3BA0() const; // 0x006D3BA0
    void SetSize(int size); // 0x006D3BC0
    void rva006D3C20(); // 0x006D3C20
    void rva006D3C60(); // 0x006D3C60
    void rva006D3CA0(const EAStringC *other); // 0x006D3CA0
    unsigned short rva006D3D10() const; // 0x006D3D10
    void rva006D4190(int codepoint); // 0x006D4190
    int rva006D47F0(const char *oldText, const char *newText); // 0x006D47F0
    void Assign(const char *text); // 0x006D4BF0
    EAStringC &Rva006D4F00Append(const EAStringC &other); // 0x006D4F00
    EAStringC &Rva006D50A0Append(const char *text); // 0x006D50A0
    EAStringC &Append(const char *const text, unsigned int limit); // 0x006D52A0
    void __cdecl rva006D5300(const char *format, ...); // 0x006D5300
    void rva006D53F0(const char *format, char *arguments); // 0x006D53F0
    int rva006D54B0(int start, int count); // 0x006D54B0
    EAStringC Left(int count) const; // 0x006D55B0
    EAStringC rva006D5690(int count) const; // 0x006D5690
    EAStringC Mid(int start) const; // 0x006D5770
    EAStringC Mid(int start, int count) const; // 0x006D5850
    EAStringC &MakeLower(); // 0x006D5940
    EAStringC &MakeUpper(); // 0x006D5970
    EAStringC &rva006D59F0(const char *text); // 0x006D59F0
    EAStringC &TrimRight(const char *text); // 0x006D5B50
    bool rva006D5CD0(const char *text); // 0x006D5CD0
    bool rva006D5DA0(const char *text); // 0x006D5DA0
    int rva006D5EC0(); // 0x006D5EC0
    EAStringC rva006D5ED0(int start) const; // 0x006D5ED0
    EAStringC rva006d5f30(int start, int count) const; // 0x006D5F30
    EAStringC &rva006D5FE0(void *source, int codepointCount); // 0x006D5FE0
    int rva006d6070(const char *text, int start = 0); // 0x006D6070
    EAStringC &rva006D6100(); // 0x006D6100
    EAStringC &rva006D6170(); // 0x006D6170
    EAStringC &rva006D61E0(int codepoint); // 0x006D61E0
    EAStringC &Assign(const EAStringC &other); // 0x006D6250
    void __cdecl rva006D62C0(const char *format, ...); // 0x006D62C0
    const char *rva00620090() const; // 0x00620090
    bool rva006CD4A0() const; // 0x006CD4A0
    EAStringC &rva006D2F90Construct(); // 0x006D2F90
    void rva006D3010Destroy(); // 0x006D3010

    StringDataC *data;

private:
    friend class BfmeBufVKG;
    void ChangeBuffer(unsigned int reserve, unsigned int offset,
        unsigned int count, CBPushZero pushZero, unsigned int size); // 0x006D4AA0
};

#endif
