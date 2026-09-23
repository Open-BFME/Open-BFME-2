// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour Overridable.h donor with target global-delete semantics.
// Target layout: destructor slot 0, next override +4, override flag +8.
class Overridable {
public:
    virtual ~Overridable();
    Overridable *m_nextOverride;
    bool m_isOverride;
    Overridable *deleteOverrides();
};
Overridable *Overridable::deleteOverrides() {
    if (m_isOverride) {
        ::delete this;
        return 0;
    }
    if (m_nextOverride)
        m_nextOverride = m_nextOverride->deleteOverrides();
    return this;
}
