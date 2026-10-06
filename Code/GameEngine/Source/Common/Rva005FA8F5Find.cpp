// cl: /MD
// ?rva005FA8F5@Rva005FA8F5@@QAEPAURva005FA8F5Entry@@H@Z, RVA 0x005FA8F5, 39 bytes.
// Linear search of inline stride-8 entries at +0x34 by key at +0 against int
// arg; count at +0x4C. Returns &entries[i] on match else one-past-end.
// Evidence: callers 0x005FA9AE 0x005FA9B8 in 0x005FA98C; unblocks 0x005FA98C.
struct Rva005FA8F5Entry {
    int m_key;
    int m_val;
};
struct Rva005FA8F5 {
    char m_pad[0x34];
    Rva005FA8F5Entry m_entries[3];
    int m_count;
    Rva005FA8F5Entry *rva005FA8F5(int key);
};
Rva005FA8F5Entry *Rva005FA8F5::rva005FA8F5(int key)
{
    int i = 0;
    for (; i < m_count; ++i) {
        if (m_entries[i].m_key == key)
            break;
    }
    return m_entries + i;
}
