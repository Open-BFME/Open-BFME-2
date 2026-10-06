// cl: /MD /EHsc
// Address-derived recovery of 0x006FFC30 (174B), an AptActionInterpreter string
// worker sibling of the recovered 0x006FFCE0. Retail clears the EAStringC out
// parameter through the const char* ctor 0x006D4C80 (empty literal 0x00BBAC1C)
// and operator= 0x006D3030, calls the unrowed filler 0x006FF980 with
// (value, sBuf, 0), and when the resulting string is empty assigns the default
// literal "/" at 0x00BD60D0. The SEH frame is the EAStringC temporary
// destructor 0x006D3010; because this body holds a second temporary slot the
// prolog reserves 8 bytes (sub esp,8) instead of the sibling's single push ecx,
// and the second block's EH state is 1 rather than 0. The handler and callee
// names are address-derived; the "/" default string address is read from the
// retail DIR32 immediate.

class EAStringC
{
    void *m_pData;
public:
    EAStringC(const char *value);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &other);
    unsigned int rva006D3750() const;
};

class AptValue;

void rva006ff980(AptValue *value, EAStringC &sBuf, int arg);

void rva006ffc30(AptValue *value, EAStringC &sBuf)
{
    {
        EAStringC tmp("");
        sBuf = tmp;
    }
    rva006ff980(value, sBuf, 0);
    if (sBuf.rva006D3750() == 0) {
        EAStringC tmp2("/");
        sBuf = tmp2;
    }
}
