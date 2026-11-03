// Target facts (code addresses are RVAs): ModuleInfo has no virtual functions or base class. Constructor 0x001F81BF calls 0x00211E58 on unchanged this; stores 0x00211E65/0x00211E67 clear +0/+4, and 0x00211E6A initializes +8 through 0x0014F3C4. Destructor 0x0033CF2F tail-calls vector destruction 0x0033CD02, which destroys the range [+0,+4) through 0x002D028F and frees +0. Neither lifetime chain stores a vptr; no constructor or destructor vftable belongs to this class. ThingTemplate constructor 0x0033E1B8 constructs four adjacent instances at +0x2E4/+0x2F0/+0x2FC/+0x308 (calls 0x0033E2E4/0x0033E2EF/0x0033E2FA/0x0033E305), proving sizeof 0x0C; +0/+4/+8 are the vector's begin, end and storage end. Push-back 0x0033D433 compares finish +4 with storage end +8 at 0x0033D43C and advances finish by 0x14 at 0x0033D44A. The VA 0x00C10C4C stores at 0x0033E1F0/0x0033DDB2 belong to the enclosing ThingTemplate at its own +0.
// Target facts: getNuggetWithTag 0x0033C21C compares the string at Nugget +4 and advances by 0x14; getNthData 0x0033ACE8 reads Nugget +8. Nugget destructor 0x002CF51B releases strings at +4 then +0 through 0x00036410; assignment 0x002CEFCD assigns those strings through 0x000366F0, copies dwords +8/+0x0C and bytes +0x10/+0x11, and does not copy +0x12. setCopiedFromDefault 0x0033B18A writes byte +0x10; filter 0x0033C84A tests mask +0x0C and flags +0x10/+0x11. Zero Hour ThingTemplate.h names first, m_moduleTag, second, interfaceMask, copiedFromDefault and inheritable; its third flag is not a BFME2 member. Nugget construction 0x0033B13B clears +0x10 at 0x0033B178 and initializes +0x11 at 0x0033B175, without a +0x12 store.
// Target facts: out-of-line methods are getNthName 0x001F12DF, getNthData 0x0033ACE8, getNuggetWithTag 0x0033C21C, clearModuleDataWithTag 0x0033C807, rva0033C84A 0x0033C84A, clearAiModuleInfo 0x0033C882, rva0033C8B5 0x0033C8B5, addModuleInfo 0x0033D553 and setCopiedFromDefault 0x0033B18A. The addModuleInfo ABI takes both bool arguments even though a Nugget stores only the inheritable argument. The enclosing-object accesses +0x3A0/+0x3AC in 0x0033C259/0x0033C288 respectively are not ModuleInfo fields. Zero Hour's getCount supplies the inline count accessor; native 0x0033ACE8 divides the pointer difference by the same 0x14 stride.
#ifndef BFME2_COMMON_MODULEINFOCLASS_H
#define BFME2_COMMON_MODULEINFOCLASS_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ModuleData;
class ThingTemplate;

class ModuleInfo
{
public:
    struct Nugget
    {
        ~Nugget();
        Nugget &operator=(const Nugget &other);

        AsciiString first;
        AsciiString m_moduleTag;
        const ModuleData *second;
        int interfaceMask;
        bool copiedFromDefault;
        bool inheritable;
    };

    ModuleInfo();
    ~ModuleInfo();

    int getCount() const { return m_end - m_begin; }
    AsciiString getNthName(int index) const;
    const ModuleData *getNthData(int index) const;
    const Nugget *getNuggetWithTag(const AsciiString &tag) const;
    void setCopiedFromDefault(bool value);
    void addModuleInfo(ThingTemplate *thingTemplate, const AsciiString &name, const AsciiString &moduleTag, const ModuleData *data, int interfaceMask, bool inheritable, bool overrideableByLikeKind = false);
    bool clearModuleDataWithTag(const AsciiString &tag, AsciiString &out);
    bool clearAiModuleInfo();
    bool rva0033C84A(int mask);
    bool rva0033C8B5();

    Nugget *m_begin;
    Nugget *m_end;
    Nugget *m_capacity;
};

#endif
