#ifndef CANONICAL_APTACTIONQUEUEC_H
#define CANONICAL_APTACTIONQUEUEC_H

class AptCIH;
class AptValue;
struct Rva006E3230Action;

class AptActionQueueC
{
    Rva006E3230Action *m_aActionPool;
    Rva006E3230Action *m_pCurrent;
    Rva006E3230Action *m_pEnd;
    Rva006E3230Action *m_pExec;
    int m_iActionPoolSize;

public:
    AptActionQueueC(int size);

    void ClearActions();
    void rva006E3230(Rva006E3230Action *cursor);
    Rva006E3230Action *rva006E32A0(Rva006E3230Action *cursor);
    int rva006E38D0();
    Rva006E3230Action *rva006E3920(int index);
    Rva006E3230Action *getCurrent();
    void RemoveActionFor(AptValue *pArg);
    void enqueueAction(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4);
    void enqueueFront(AptValue *, AptValue *, AptValue *, int, int);
    void prependAction(void *actions, AptCIH *target, int type, int value);
    void rva006E3740(AptValue *, AptValue *, AptValue *, int, int);
    void rva006E39A0();
};

#endif // CANONICAL_APTACTIONQUEUEC_H
