// ?find@?$StringBase@D@@QBEPBDD@Z
// partial score=0.9 date=2026-08-31
// ?find@?$StringBase@D@@QBEPBDD@Z
// partial score=0.9 date=2026-08-31
// cl: /O2
// 40 bytes against 44, same structure: the begin pointer and the end pointer
// are both built from the header with the empty-literal fallback, and the scan
// is a do/while that returns the pointer on a hit and null on running off the
// end.
//
// The four missing bytes are one operand choice inside the loop. Retail keeps
// the character parameter as a memory operand and loads the string byte into
// the register:
//     mov dl,[eax] ; cmp dl,[esp+4]
// MSVC 7.1 hoists the parameter out of the loop instead:
//     mov dl,[esp+4] (before the loop) ; cmp [eax],dl
// A do/while with the increment in the condition, a named local for the loaded
// character, a while over the negated test, and a for with the end check moved
// into the body all produce the hoisted form.
template <typename T>
const T *StringBase<T>::find(T c) const
{
    const T *p = m_data ? &m_data->data[0] : "";
    const T *end = p + (m_data ? m_data->length : 0);

    do {
        if (*p == c) {
            return p;
        }
        ++p;
    } while (p != end);

    return 0;
}
