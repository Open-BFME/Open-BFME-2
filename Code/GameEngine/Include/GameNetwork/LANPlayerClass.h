/* Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
 * LANPlayer has no virtual functions, vptr or base. RequestSetName allocates
 * 0x1C bytes at 0x0044B864/0x0044B866 and initializes dwords +0/+4/+8/+0xC/
 * +0x10/+0x14 and a word +0x18 at 0x0044B870..0x0044B881, without a table store.
 * LANGameSlot construction (0x00448150) repeats those stores at this+0x1AC;
 * its table 0x00C3E4FC is stored at the enclosing this+0, at 0x00448160.
 * The copy constructor (0x0044A901) calls StringBase<unsigned short>'s copy
 * (0x00037050) for +0/+4/+8, then copies dwords +0xC/+0x10/+0x14/+0x18.
 * The nonvirtual destructor (0x00447ACA) releases +8/+4/+0 through 0x00036E70;
 * the scalar deleting wrapper (0x0044AAD1) calls it directly at 0x0044AAD4.
 * LANGameSlot copies/destroys this member at +0x1AC (0x0044B2B1/0x00447B3B),
 * and its next member starts at +0x1C8 (0x00447B1F), confirming sizeof 0x1C.
 * LookupPlayer passes +0x14 to BfmeNetAddress::Rva00248CBF at 0x004499A2;
 * the port is a word (+4 within the address, 0x004499AB), not a dword.
 * RequestSetName sets name/login/host at +0/+4/+8 (0x0044B8B0/0x0044B8C8/
 * 0x0044B8BC), and the timeGetTime result at +0xC (0x0044B8D6).
 * removePlayer reads/writes the +0x10 link (0x004499D6..0x004499F8);
 * addPlayer compares the +0 string and +0x14 IP (0x0044B42B/0x0044B445).
 * Donor names: Zero Hour GameNetwork/LANPlayer.h names the three strings,
 * m_lastHeard, m_next and the name/link/IP accessors. m_address/getAddress
 * describe the BfmeNetAddress subobject passed at the LookupPlayer call site.
 */
#pragma once

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "BfmeNetAddress.h"

class LANPlayer
{
public:
    LANPlayer() : m_lastHeard(0), m_next(0)
    {
        m_address.ip = 0;
        m_address.port = 0;
    }
    LANPlayer(const LANPlayer &other);
    ~LANPlayer();

    const UnicodeString &getName() const { return m_name; }
    LANPlayer *getNext() { return m_next; }
    LANPlayer *getNext() const { return m_next; }
    void setNext(LANPlayer *next) { m_next = next; }
    unsigned int getIP() const { return m_address.ip; }
    const BfmeNetAddress *getAddress() const { return &m_address; }

    UnicodeString m_name;
    UnicodeString m_login;
    UnicodeString m_host;
    unsigned int m_lastHeard;
    LANPlayer *m_next;
    BfmeNetAddress m_address;
};
