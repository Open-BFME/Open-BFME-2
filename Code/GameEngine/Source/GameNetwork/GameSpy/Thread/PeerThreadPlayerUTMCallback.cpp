// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// ZH semantic donor: PeerThread.cpp via BFME1
// 4367fc698990427e26cc1c399989d074d8ee9bbe. Target facts: Ghidra
// boundary 0x0038C405/134; callback pointer stored at 0x0038EEDF among
// the peer callback registrations; response tag 16; optional nick guard;
// string assignments at +0x10/+0xE8/+0xF4; response dispatch at slot +0x20.
// The recovered record constructor 0x00389F77 and destructor 0x0038A063,
// plus the response queue stride, establish its 840-byte size and lifetime.
// String field meanings and callback name follow donor context; offsets,
// guard and calls come from target bytes. Keep the record owner anonymous.
// Only declarations of the already-recovered string assignment are needed;
// its implementation remains stlport_narrow_string.cpp @0x0001B790.
// The global's existing definition in Rva0059FF9DDo.cpp is placed at
// VA0x00E02340 by independently matched references. No new pin or global.
// The registration is 0x40 bytes before independently rowed QRTeamKeyCallback
// 0x0038DE7B: its SDK slot 22 establishes this callback's playerUTM slot 6.
// Declarations for the already-rowed narrow-string assignment. This body
// never creates or destroys a string itself: the record lifetime calls do.
namespace _STL {
template<class T> class char_traits;
template<class T> class allocator;
template<class C, class T, class A> class basic_string {
public:
    basic_string &operator=(const C *);
};
typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

struct PeerResponse {
    union { unsigned int alignmentWitness; unsigned char bytes[840]; };
    PeerResponse();
    ~PeerResponse();
};
class GameSpyPeerMessageQueueInterface;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class UTMResponseQueueView {
public:
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void addResponse(const PeerResponse &resp);
};

void playerUTMCallback(void *peer, const char *nick, const char *command,
    const char *parameters, int authenticated, void *param)
{
    PeerResponse resp;
    *(int *)resp.bytes = 16;
    if (nick) {
        *(_STL::string *)(resp.bytes + 0x10) = nick;
        *(_STL::string *)(resp.bytes + 0xe8) = command;
        *(_STL::string *)(resp.bytes + 0xf4) = parameters;
        ((UTMResponseQueueView *)TheGameSpyPeerMessageQueue)->addResponse(resp);
    }
}

enum RoomType { TitleRoom, GroupRoom, StagingRoom };

// Retail callback registration at 0x0038EED5 selects SDK slot 2 (roomUTM).
// Ghidra 0x0038C379/140; same proven record lifetime and string offsets.
// Retail checks StagingRoom before constructing the record and checks nick
// before assigning strings and dispatching; it always destroys the record.
void roomUTMCallback(void *peer, RoomType roomType, const char *nick,
    const char *command, const char *parameters, int authenticated, void *param)
{
    if (roomType != StagingRoom)
        return;
    PeerResponse resp;
    *(int *)resp.bytes = 15;
    if (nick) {
        *(_STL::string *)(resp.bytes + 0x10) = nick;
        *(_STL::string *)(resp.bytes + 0xe8) = command;
        *(_STL::string *)(resp.bytes + 0xf4) = parameters;
        ((UTMResponseQueueView *)TheGameSpyPeerMessageQueue)->addResponse(resp);
    }
}
