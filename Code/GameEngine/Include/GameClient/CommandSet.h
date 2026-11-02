// Target facts (code addresses are RVAs, tables are VAs): constructor 0x00409FFA initializes Overridable's pointer +4, byte +8 and dword +0xC, installs 0x00C3906C at 0x0040A021, and constructs the name at +0x10. Destructor 0x0040A057 restores the same table at 0x0040A068, releases the name at 0x0040A075, then calls ~Overridable (0x001E3624) at 0x0040A080. That base restores its own table 0x00BDDC48 at 0x001E362C. CommandSet's only virtual slot is its deleting destructor: 0x00C3906C contains VA 0x0080A13F, whose call at RVA 0x0040A142 reaches 0x0040A057; the string at 0x00C39070 ends the table.
// Target fields: allocations 0x0031B072 and 0x0031E8E2 request 0x9C bytes before calls to 0x00409FFA at 0x0031B090 and 0x0031E903. Constructor 0x0040A027 copies the four-byte name, 0x0040A031 stores its int argument at +0x98, 0x0040A038 sets +0x94 to 32, and 0x0040A03E..0x0040A043 clears 32 dword pointers at +0x14. Getter 0x00409EE8 reads the name at +0x10 and a button at +0x14+4*i. ResetCommandSet 0x00409F83 and SetCommandButton 0x00409FA0 compare dword +0x98 with 1; the latter updates +0x94 with an unsigned maximum. These trailing fields keep neutral names. Zero Hour ControlBar.h supplies getName, m_name and m_command; its linked-list tail and pool base do not describe this target.
// Ledger declarations (RVA): constructor 0x00409FFA, virtual destructor 0x0040A057, getCommandButton 0x00409EE8, rva00409F1B 0x00409F1B, ResetCommandSet 0x00409F83, SetCommandButton 0x00409FA0, refreshIfStale 0x00409FCC and parseCommandButton 0x0040A092. The parser's target signature takes INI*, void*, const CommandButton** and int. Retail 0x0031B0A9 calls assignment 0x0031AB7F on the newly constructed CommandSet; that body calls Overridable::operator= at 0x0031AB89, assigns the name and copies the array and trailing dwords. Its ledger identity remains Rva0031AB7F::operator=; declaring CommandSet's assignment prevents a generated replacement. All rowed methods remain out of line; getName uses Zero Hour's inline body with the retail name offset. The field-parse table is bound at VA 0x00C38DD0 by the rowed getter 0x0031A9EC.
#ifndef BFME2_COMMANDSET_H
#define BFME2_COMMANDSET_H

#include "../Common/Overridable.h"
#include "CommandButton.h"

class AsciiString;
class CommandButton;
class INI;
struct FieldParse;

class CommandSet : public Overridable
{
public:
    CommandSet(const AsciiString &name, int mode);
    virtual ~CommandSet();
    CommandSet &operator=(const CommandSet &);

    const AsciiString &getName() const { return m_name; }
    const CommandButton *getCommandButton(int index) const;
    void rva00409F1B(int, int);
    void ResetCommandSet();
    void SetCommandButton(int value, int index);
    void refreshIfStale();
    static void parseCommandButton(INI *, void *, const CommandButton **, int);
    static const FieldParse m_commandSetFieldParseTable[];

    AsciiString m_name;
    const CommandButton *m_command[32];
    unsigned int m94;
    int m98;
};

#endif
