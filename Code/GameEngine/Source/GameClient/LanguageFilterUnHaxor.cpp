// cl: /O1 /MD /EHsc /G7 /arch:SSE /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Donor LanguageFilter normalization with the target StringBase ABI.
// init and filterLine call this on a UnicodeString reference. Target header:
// refcount at 0, length at 4, capacity at 6, wide characters at 8.
typedef unsigned short WideChar;
typedef int Int;
typedef bool Bool;
extern "C" __declspec(dllimport) WideChar *__cdecl wcsrchr(const WideChar *, WideChar);
class UnicodeString;
template <typename T> class StringBase
{
    friend class UnicodeString;
public:
    int getLength() const { Header *h = m_data; return h ? h->length : 0; }
    T getCharAt(Int index) const;
    void concat(const T *text, Int length);
    void set(const StringBase<T> &other);
private:
    StringBase(const T *text);
    void releaseBuffer();
    struct Header { int refs; unsigned short length; unsigned short capacity; T data[1]; };
    Header *m_data;
};
class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
    ~UnicodeString() { ((StringBase<WideChar>*)this)->releaseBuffer(); }
    Int getLength() const { return ((const StringBase<WideChar>*)this)->getLength(); }
    WideChar getCharAt(Int index) const { return ((const StringBase<WideChar>*)this)->getCharAt(index); }
    void concat(WideChar c) { ((StringBase<WideChar>*)this)->concat(&c, 1); }
    void set(const UnicodeString &other) { ((StringBase<WideChar>*)this)->set(*(const StringBase<WideChar>*)&other); }
};
class LanguageFilter { protected: void unHaxor(UnicodeString &word); };
// Target RVA 0x9C0728 contains these five ignored characters and terminator.
WideChar ignoredChars[] = L"-_*'\"";
void LanguageFilter::unHaxor(UnicodeString &word)
{
    Int len = word.getLength();
    UnicodeString newWord(L"");
    for (Int i = 0; i < len; ++i) {
        WideChar c = word.getCharAt(i);
        if ((c == L'p') || (c == L'P')) {
            if (((i + 1) < len) && ((word.getCharAt(i + 1) == L'h') || (word.getCharAt(i + 1) == L'H'))) {
                newWord.concat(L'f');
                ++i;
            } else {
                newWord.concat(c);
            }
        } else if (c == L'1') newWord.concat(L'l');
        else if (c == L'3') newWord.concat(L'e');
        else if (c == L'4') newWord.concat(L'a');
        else if (c == L'5') newWord.concat(L's');
        else if (c == L'6') newWord.concat(L'b');
        else if (c == L'7') newWord.concat(L't');
        else if (c == L'0') newWord.concat(L'o');
        else if (c == L'@') newWord.concat(L'a');
        else if (c == L'$') newWord.concat(L's');
        else if (c == L'+') newWord.concat(L't');
        else if (wcsrchr(ignoredChars, c) == 0) newWord.concat(c);
    }
    word.set(newWord);
}

