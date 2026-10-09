// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target 0x000C9251 returns its receiver after initializing a 40-byte envelope.
// OrnamentData is the existing consumer spelling; no independent target name proof.
// BF1 f98983a7d FadeAndDieOrnamentUpdateCtorThunk.cpp provides the same defaults.
// Target stores and the three existing consumers establish the field offsets.
struct OrnamentData {
    OrnamentData *init() throw();
    float m_f00, m_f04, m_f08;
    int m_reset0C, m_i10, m_i14, m_i18, m_i1C, m_i20, m_reset24;
};
OrnamentData *OrnamentData::init() throw() {
    float one = 1.0f;
    OrnamentData *self = this;
    int ione = 1;
    self->m_reset0C = 0;
    self->m_i1C = -1;
    self->m_i20 = -1;
    self->m_reset24 = 0;
    self->m_f00 = one;
    self->m_f04 = one;
    self->m_f08 = one;
    self->m_i10 = ione;
    self->m_i14 = ione;
    self->m_i18 = ione;
    return self;
}
