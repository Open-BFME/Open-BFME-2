// Storage layout of the rowed Rva0023C641 constructor at 0x0023DBF9.
// The AsciiString subobjects at +4/+8 are represented by their one-pointer
// storage, without constructors or destructors. The existing retail initializer
// 0x007ADCAE and cleanup 0x007B7786 retain sole ownership of their lifecycle.
#ifndef RVA0023C641_STORAGE_H
#define RVA0023C641_STORAGE_H
#include <stddef.h>

struct Rva0023C641Storage
{
    unsigned char m_enabled;
    void *m_name04;
    void *m_name08;
    bool m_gotUnit;
    const void *m_curThing;
    bool m_startTiming;
    void *m_file18;
    unsigned int m_1C, m_20;
    int m_24;
    bool m_28;
    unsigned int m_2C;
    unsigned int m_30, m_34, m_38, m_3C, m_40, m_44, m_48;
    int m_4C;
    double m_50, m_58, m_60, m_68, m_70, m_78, m_80;
    float m_88, m_8C, m_90, m_94;
};
typedef char Rva0023C641StorageSize[(sizeof(Rva0023C641Storage) == 0x98) ? 1 : -1];
typedef char Rva0023C641StorageFirst[(offsetof(Rva0023C641Storage, m_name04) == 4) ? 1 : -1];
typedef char Rva0023C641StorageSecond[(offsetof(Rva0023C641Storage, m_name08) == 8) ? 1 : -1];
typedef char Rva0023C641StorageTiming[(offsetof(Rva0023C641Storage, m_startTiming) == 0x14) ? 1 : -1];
typedef char Rva0023C641StorageLast[(offsetof(Rva0023C641Storage, m_94) == 0x94) ? 1 : -1];
extern Rva0023C641Storage g_00DFE7A8;
#endif
