// cl: /DNDEBUG /MD
// ?isValid@ObjectFilter@@QBE_NXZ @0x360CED (57B): ammo-descriptor validity gate.
// The descriptor's first dword is an index into a global table of 0x94-byte
// records; the entry is valid when its flag byte at +0x88 is non-zero, with
// negative and over-count indices rejected. Retail-measured facts:
//
// - Index load is [this+0x00] (mov ecx,[ecx]); no other member is read.
// - Table bounds come from the consecutive .data globals at 0xE01E68 (begin)
//   and 0xE01E6C (end): 23/11 image-wide refs, all inside the 0x360xxx-0x362xxx
//   science cluster, so TU-local externs (DIR32 patches from retail, no pins).
// - Count is (end - begin) / 0x94 via signed idiv (cdq, divisor in edi); /O1
//   keeps the outlined idiv where /O2 magic-multiplies (prereqs precedent).
// - The name is BFME1-attested: reference/open-bfme-1/.../Object/Weapon/
//   Weapon_getRemainingAmmo.cpp declares this exact QBE_NXZ member and calls
//   it in the same guard position (pin 2008 pre-exists; pin+row coexistence).
// - Shaping laws (each load-bearing, probe-proven): nested-positive ifs share
//   the single xor-al fail tail (sequential ifs+returns split it); (int)sizeof
//   keeps the division signed (bare sizeof goes unsigned div); the
//   `Bool valid = ... != 0; return valid;` temp materializes cmp-imm + setne
//   (direct return folds to xor+cmp-reg).
typedef bool Bool;

// TU-local replica of one 0x94-byte validity-table record. Only the extent
// (sizeof must stay 0x94: the divisor and the imul stride) and the flag byte
// at +0x88 are retail-constrained; all other bytes are padding.
struct ValidityRecord
{
    char m_pad00[0x88];
    unsigned char m_validFlag;
    char m_pad89[0x94 - 0x89];
};

extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;

class ObjectFilter
{
public:
    Bool isValid() const;

private:
    int m_entryIndex;
};

// ?isValid@ObjectFilter@@QBE_NXZ
Bool ObjectFilter::isValid() const
{
    int index = m_entryIndex;
    if (index >= 0)
    {
        int count = (g_validityEnd - g_validityBegin) / (int)sizeof(ValidityRecord);
        if (index < count)
        {
            const ValidityRecord *table = (const ValidityRecord *)g_validityBegin;
            Bool valid = table[index].m_validFlag != 0;
            return valid;
        }
    }
    return false;
}
