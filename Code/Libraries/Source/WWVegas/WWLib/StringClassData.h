/* Target facts: StringClass has no bases, virtual functions or vtable. Constructors at RVAs 0x00065F34 (int, bool), 0x000F0ED1 (const char *, bool), 0x00129BF0 (const StringClass &, bool) and 0x00187CB0 (bool) store the buffer pointer at +0 from the empty-string pointer at VA 0x00DD528C, with no vptr store. The nonvirtual destructor at RVA 0x00065F5B tail-jumps to Free_String at 0x00610A40. The array destructor at 0x0011F6B0 passes that callback and an element size of 4 at 0x0011F6C1 and 0x0011F6CA; VectorClass<StringClass>'s constructor at 0x0011F980 independently uses a four-byte element stride and the same callback. Thus sizeof(StringClass) is 4 and its only instance member is char * at +0. There are no constructor/destructor vtables to reconcile.
 * Target facts: Allocate_Buffer at RVA 0x006109F0 allocates length+8, writes the allocated length at +0 and cached length at +4, and returns allocation+8. Get_Length at 0x0011FB10 reads the buffer at +0 and its cached length at buffer-4. Store_Allocated_Length at 0x00610A20 and Get_Allocated_Length at 0x00610AB0 use buffer-8. The int/bool constructor reads m_NullChar at VA 0x00E08C18. The ledger supplies the out-of-line declarations below: assignments 0x000F0E8D/0x00121450, appends 0x001214C0/0x00129C80/0x006133D0, Compare_No_Case 0x00154190, Is_Empty 0x00130FEA, Get_Buffer 0x0013B190, Format_Args 0x00610D70, Format 0x00610DD0, Copy_Wide 0x00610E30, Get_String 0x00610B00, Resize 0x00610C70, Uninitialised_Grow 0x00610CF0 and Set_Buffer_And_Allocated_Length 0x00610AC0. The copy constructor calls assignment at 0x00129C6D; the C-string constructor calls assignment at 0x000F0F0D. These rowed methods remain declarations.
 * Donor facts: Zero Hour GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h supplies the names m_Buffer, m_EmptyString, m_NullChar and HEADER's allocated_length/length, constructor defaults, and the non-rowed accessor declarations. BFME2's ledger mangles StringClass with class key V and its character pointers as single-byte char pointers. The donor is naming evidence and is not included. Friend declarations preserve the existing rowed consumers' access to the private helpers and statics. */
#pragma once

#ifndef BFME2_STRINGCLASS_DATA_H
#define BFME2_STRINGCLASS_DATA_H

#include <stdarg.h>

class StringClass
{
public:
    StringClass(bool hint_temporary);
    StringClass(int initial_len = 0, bool hint_temporary = false);
    StringClass(const StringClass &string, bool hint_temporary = false);
    StringClass(const char *string, bool hint_temporary = false);
    ~StringClass();

    const StringClass &operator=(const StringClass &string);
    const StringClass &operator=(const char *string);
    const StringClass &operator+=(const StringClass &string);
    const StringClass &operator+=(const char *string);
    const StringClass &operator+=(char ch);

    const char &operator[](int index) const;
    char &operator[](int index);
    operator const char *() const;
    int Compare(const char *string) const;
    int Compare_No_Case(const char *string) const;
    int Get_Length() const;
    bool Is_Empty() const;
    char *Get_Buffer(int new_length);
    char *Peek_Buffer();
    const char *Peek_Buffer() const;
    int __cdecl Format(const char *format, ...);
    int __cdecl Format_Args(const char *format, const va_list &arg_list);
    bool Copy_Wide(const unsigned short *source);

    friend StringClass operator+(const char *string1, const StringClass &string2);

private:
    friend class BfmeG1035;
    friend class Rva000EF9A8;
    friend class Rva00131BE5;
    friend class Rva00131D07;

    typedef struct _HEADER
    {
        int allocated_length;
        int length;
    } HEADER;

    void Get_String(int length, bool is_temp);
    char *Allocate_Buffer(int length);
    void Resize(int size);
    void Uninitialised_Grow(int length);
    void Free_String();
    void Store_Length(int length);
    void Store_Allocated_Length(int allocated_length);
    HEADER *Get_Header() const;
    int Get_Allocated_Length() const;
    void Set_Buffer_And_Allocated_Length(char *buffer, int length);

    char *m_Buffer;
    static char m_NullChar;
    static char *m_EmptyString;
};

#endif
