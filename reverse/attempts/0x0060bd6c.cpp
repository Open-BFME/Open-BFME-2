// ?compare@PooledString@@QBEHABV1@@Z
// partial score=0.95 date=2026-08-31
// ?compare@PooledString@@QBEHABV1@@Z
// partial score=0.95 date=2026-08-31
// cl: /O1
// Also covers ?compareNoCase@PooledString@@QBEHABV1@@Z at 0x0060BDB3, which is
// the same body against the case-insensitive worker.
//
// 34 bytes against 34, same instructions, same call targets. The only
// difference is where the entry pointer is dereferenced. Retail loads it into
// eax ahead of the register saves and then leas the text pointer:
//     mov eax,[esp+4] ; mov eax,[eax] ; push esi ; push edi ; lea esi,[eax+8]
// MSVC 7.1 saves first and folds the +8 into an add:
//     mov eax,[esp+4] ; push esi ; mov esi,[eax] ; push edi ; add esi,8
// A named entry local, a reference to the entry, &entry->m_text[0] and the
// fully inline expression all canonicalize to the second form.
int PooledString::compare(const PooledString &that) const
{
    const PooledStringEntry *entry = that.m_entry;
    const char *text = entry->m_text;

    return compare(text, (int)strlen(text));
}
