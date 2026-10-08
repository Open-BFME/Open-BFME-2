// ?rva004B65E4@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.8 date=2026-10-08
// cl: /O1 /MD /DNDEBUG /arch:SSE /G7
// Retail 004b65e4..004b6691: a 591-bit model-condition INI range parser.
// The native count, nineteen-word complement, two-bit diagnostic and
// inclusive scan establish the behavior. WB identifies Common/BitFlags.h,
// but not the method name. The existing helper names describe only their
// verified storage/ABI; WeaponTemplateSetHead is the ledger's 76-byte view.
class INI;
class INIException {
public:
    INIException(int, const char *, ...);
    INIException(const INIException &);
    ~INIException();
private:
    char *message;
    int tag;
};
class WeaponTemplateSetHead {
public:
    WeaponTemplateSetHead(const WeaponTemplateSetHead &);
    void rva000B3ED3(const WeaponTemplateSetHead &);
    unsigned int words[19];
};
class Rva000B937E {
public:
    void rva000B937E(INI *, void *);
};
template<int N> class BitFlags {
public:
    int count() const;
};

// ?rva004B65E4@@YAXPAVINI@@PAX1PBX@Z present-unmatched
void rva004B65E4(INI *ini, void *, void *store, const void *)
{
    WeaponTemplateSetHead *destination = static_cast<WeaponTemplateSetHead *>(store);
    WeaponTemplateSetHead added(*destination);
    reinterpret_cast<Rva000B937E *>(destination)->rva000B937E(ini, 0);
    for (unsigned int word = 0; word < 19; ++word)
        added.words[word] = ~added.words[word];
    added.rva000B3ED3(*destination);
    if (reinterpret_cast<const BitFlags<591> *>(&added)->count() != 2)
        throw INIException(1, "you must specifly only two bit flags for a range.");
    bool started = false;
    bool finished = false;
    for (int bit = 0; bit < 591; ++bit) {
        unsigned int word = static_cast<unsigned int>(bit) >> 5;
        unsigned int mask = 1U << (bit & 31);
        if (!started) {
            if (!(added.words[word] & mask))
                continue;
            started = true;
        } else if (added.words[word] & mask) {
            finished = true;
        }
        destination->words[word] |= mask;
        if (finished)
            break;
    }
}
