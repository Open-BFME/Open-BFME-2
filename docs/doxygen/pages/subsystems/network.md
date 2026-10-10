# Network: lockstep, LAN and online services {#sub_network}

BFME 2 multiplayer is deterministic lockstep. Machines never send game
state to each other: they send the player commands for each logic frame,
and every machine runs the same simulation on the same commands. The
network layer packs those commands into UDP packets, collects them per
logic frame and tells the engine when a logic frame may run. Around that
core sit the LAN lobby, peer-to-peer port negotiation and firewall
detection, map and Create-a-Hero transfer before a game, the disconnect
screen, and the online stacks: the GameSpy SDK and EA's FESL services over
the DirtySock library.

The API group is \ref grp_network. \ref page_frame_loop shows where the
network is consulted in a frame, \ref page_core_frameworks covers the
messages and command lists it carries, and \ref sub_save_load_crc covers
the checksums that detect a desync.

## Where it lives {#sub_network_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/GameNetwork/` | the lockstep core (`ConnectionManager`, `Connection`, `NetPacket`, the `NetCommandMsg` family, `NetCommandList`, `FrameData`), the sockets (`Transport`, `UDP`), the LAN lobby (`LANAPI`, `LANGameInfo`), game setup (`GameInfo`, `GameSlot`, `SkirmishGameInfo`), `DisconnectManager`, `NAT`, `FirewallHelperClass`, `IPEnumeration`, `DownloadManager` |
| `GameEngine/Source/Common/NetworkInterface*.cpp`, `ConnectionManager*.cpp`, `FrameDataManager*.cpp` | the frame-admission queries, connection-manager setup and the per-player frame rings |
| `GameEngine/Source/GameNetwork/GameSpy/` | the GameSpy SDK modules in C (`gp/`, `gstats/`, `ghttp/`, `qr2/`, `serverbrowsing/` and others, plus the reconstructed `chat/` and `peer/`) and the game's C++ glue around them (`GameSpyStagingRoom`, `PeerDefs`, `BuddyDefs`, `LadderDefs`, `MainMenuUtils`) |
| `GameEngine/Source/GameNetwork/` files named `Fesl*`, `Y2Fesl*`, `Y4Fesl*`, `V2Fesl*` | EA FESL online services; the prefixed names are staging names |
| `Libraries/Source/DirtySock/` | EA's DirtySock networking, ProtoSSL and the ProtoMangle NAT-traversal client |
| `GameEngine/Source/GameNetwork/WOLBrowser/` | COM wrappers for an embedded web browser |

Many files here are split units named after one function or an address
(\ref page_reading_code_staging). Search `reverse/functions.csv` for a
class name to find all of its files.

## Key classes {#sub_network_classes}

- `NetworkInterface` (`TheNetwork`) is the engine's view of a network
  game: an abstract interface; the game constructs one implementation
  of it. The engine starts with none; the lobby creates a fresh one when
  a LAN or online game starts (the LAN opens its own transport; the
  online launch attaches the transport prepared by NAT negotiation when
  there is one). A failed start deletes it again, and
  `GameEngine::reset` deletes it when it runs after a multiplayer game
  (BFME 2 adds one further condition whose meaning is not yet
  established). Zero Hour's `GameEngine::reset` makes the same deletion.
- `ConnectionManager` owns the game's connections, the transport and the
  frame rings. It receives packets, sorts their commands into frames,
  acknowledges and relays them, and sends what is queued. It also runs
  the in-game chat, file transfer and disconnect traffic.
- `Connection` is one peer: its address and its queue of unacknowledged
  outgoing commands.
- `NetCommandMsg` and its subclasses are the commands on the wire: game
  commands (`NetGameCommandMsg`, built from a `GameMessage`), frame info,
  acknowledgements, keep-alives, chat, player leave and destroy, router
  fallback, disconnect votes, file transfer and progress. `NetCommandRef`
  and `NetCommandList` hold them; `NetCommandWrapperList` reassembles
  commands too large for one packet.
- `NetPacket` serialises commands into a packet and parses them out again.
- `FrameData` and `FrameDataManager`: one manager per player slot, each a
  ring of per-frame entries that counts the commands received for a frame
  and the number expected.
- `Transport` and `UDP` wrap Winsock. `Transport` queues outgoing and
  incoming packets and obfuscates them; `UDP` is a socket.
- `DisconnectManager` handles players who stop responding: the disconnect
  screen, its timeouts and the vote to drop a player.
- `LANAPI` (`TheLAN`) is the LAN lobby: discovery by broadcast, game
  announce, join, leave, chat and the start countdown. `GameInfo`,
  `GameSlot` and `LANGameInfo` describe a game being set up.
- `NAT` and `FirewallHelperClass` negotiate ports between peers and probe
  the local firewall (Zero Hour: against EA's "mangler" servers).

## How a network game runs {#sub_network_flow}

1. **Setup.** The LAN or online lobby fills a `GameInfo`: map, map
   checksum and size, random seed and eight slots. The host's options
   string keeps Zero Hour's key=value style (map, map checksum, size,
   seed, then one record per slot), but BFME 2 rewrites the header keys
   (it adds `GSID`, `GT`, `SI` and a `GR` list of ten game-rule values,
   and drops several of Zero Hour's) and extends each slot record with
   hero data. LAN game announcements carry the options in a binary form.
2. **Network.** At start, the LAN lobby and the GameSpy staging room
   both create `TheNetwork` through the same function and give it a
   transport. On a LAN the game transport binds the lobby's address on a
   port eight above the lobby port. The online launch takes its port and
   transport from the NAT negotiation object when there is one.
3. **Transfers.** Over that new network, BFME 2 first checks the
   Create-a-Hero transfer, then sends the map to any player who lacks
   it. Either failure deletes `TheNetwork` and cancels the start
   ("GUI:CouldNotTransferHero", "GUI:CouldNotTransferMap").
4. **Launch.** On success the lobby posts the new-game message and seeds
   the logic random numbers from the game's seed, so every machine starts
   from the same seed. The LAN and GameSpy paths both do this.
5. **Commands out.** The local player's commands on `TheCommandList`
   become `NetGameCommandMsg`s for a later logic frame. Zero Hour does
   this in `Network::GetCommandsFromCommandList`, with the delay set by
   the run-ahead; BFME 2's matched counterpart still has a placeholder
   name. Each peer also sends frame info: how many commands it issued
   for a frame, so receivers know when that frame is complete.
6. **Transport.** `ConnectionManager::update` receives, updates the
   disconnect manager, relays, sends every connection's queue and flushes
   the `Transport`. `ConnectionManager::processNetCommand` dispatches each
   received command by type. The network's own update runs the command
   pump and then its light update, which calls
   `ConnectionManager::update`; the client half of the frame also calls
   the light update.
7. **Admission.** A client runs the next logic frame only when it is
   below the frame ceiling and every player's commands for that frame have
   arrived (`NetworkInterface::getFrameAdvanceCount`). The commands then
   go back on `TheCommandList` and `GameLogic` executes them
   (\ref sub_gamelogic_map).
   In Zero Hour, the `Network` class's `RelayCommandsToCommandList` does
   the hand-back.
8. **Checks.** At the CRC interval each machine sends a checksum of its
   logic state; a mismatch is a desync (\ref sub_save_load_crc).

### The packet router {#sub_network_router}

One player is the packet router. A client may run logic only up to the
frame ceiling, the newest frame the router has published; the headroom is
that ceiling minus the current logic frame. The router itself paces by
time instead: it accumulates `QueryPerformanceCounter` time and admits one
logic frame per logic-rate quantum. The client half of the main loop
reads `NetworkInterface::getFramePacingStatus` (network headroom, or
router pacing) to decide whether to run a client frame and to adjust its
adaptive limit; without a network it never skips. The router detects a
stall when a peer falls too far behind, and it broadcasts a
latency-sorted list of fallback routers that peers step through to pick
the next router. `docs/bfme2-network-timing-path.md` has the details and
the evidence.

The main-loop routine that calls these queries is still being reverse
engineered; \ref page_frame_loop describes its contract.

## Entry points {#sub_network_entry}

| Function | Role | State |
|---|---|---|
| `NetworkInterface::getFrameAdvanceCount` | how many logic frames may run now | matched |
| `NetworkInterface::getFramePacingStatus` | headroom or router pacing, for client-frame admission | matched |
| `NetworkInterface::isPacketRouter` | whether this machine is the router | matched |
| `ConnectionManager::update` | one pass of receive, relay and send | matched |
| `DisconnectManager::update` | disconnect timeouts and screen | matched |
| `LANAPI::init` | binds the LAN lobby socket and reads the user and machine names | matched |
| `LANAPI::OnGameStart` | creates the network, runs the transfers and launches a LAN game | matched |
| `LANAPI::update` | LAN lobby pump | not yet reconstructed |
| the network's own update and light update | pump commands and call `ConnectionManager::update` | matched, under address names |

## How it connects {#sub_network_connects}

- **Engine.** The main loop asks the network whether logic may advance
  and gives it a light update (\ref page_frame_loop,
  \ref sub_engine_core). While the game window is minimised,
  `Win32GameEngine::update` keeps pumping `TheLAN`.
- **Messages.** Input and UI put `GameMessage`s on `TheCommandList`; the
  network carries them and hands them back for `GameLogic` to execute
  (\ref page_core_frameworks, \ref sub_gameclient).
- **Checksums and replays.** The logic CRC travels as a game message,
  and `TheRecorder` records the command stream (\ref sub_save_load_crc).
- **UI.** The lobby, staging-room and online screens drive `LANAPI`,
  `GameInfo` and the GameSpy and FESL code; the disconnect screen belongs
  to `DisconnectManager` (\ref sub_gui_apt).
- **Living World.** War of the Ring multiplayer starts through its own
  twins of the LAN and GameSpy launch paths, which take the map from the
  campaign battle (\ref sub_living_world).
- **Maps.** After a map transfer the lobby refreshes `TheMapCache` and
  looks the map up again before starting.

## BFME 2 compared with Zero Hour {#sub_network_zh}

- **Sockets.** Zero Hour's `Transport` owns one UDP socket. BFME 2's has
  eight per-player socket slots that may share a socket. Packet bytes are
  obfuscated with Zero Hour's scheme (each 32-bit word XORed with a
  rolling mask, then byte-swapped), but with BFME 1's mask constants
  rather than Zero Hour's.
- **LAN ports.** Zero Hour uses one fixed lobby port, 8086. BFME 2 binds
  the first free port from 8086 upward, offset by an instance number from
  the `_EA_RTS_HEADLESS` environment variable, and plays on the lobby port
  plus eight.
- **Commands.** BFME 2 adds one more command header field, believed (from
  BFME 1's layout) to be a timestamp. Like Zero Hour's header fields
  (frame, relay, player), it is written only when it changes from the
  previous command's; Zero Hour has no such header field. BFME 2 adds
  command types (GameSpy stats keys, leave and frame-data requests,
  Create-a-Hero data serialised with `Xfer`, a save-game command), so its
  type numbers differ from Zero Hour's from type 5 onward. The router
  fallback plan and the GameSpy stats key exchange are shared with
  BFME 1. Parsed game messages are range-checked. Received commands go
  through one switch on the command type, as in BFME 1, where Zero Hour
  used a chain of tests.
- **Options string.** BFME 2 rewrites the header of the game options
  string and extends its slot records (see step 1 above).
- **Join check.** The LAN join request carries an executable check value,
  the INI CRC and a third BFME checksum. In Zero Hour's source the host's
  comparison of these values is commented out. BFME 2 keeps the
  CRC-mismatch error and its "LAN:ErrorCRCMismatch" text, but the host's
  join handler is not yet reconstructed, so whether it compares them is
  not known.
- **Online.** BFME 2 keeps the GameSpy SDK and adds EA's FESL services on
  DirtySock.

## Modding notes {#sub_network_modding}

- **Little is data-driven.** Zero Hour and BFME 1 read network timing
  from `GameData` INI fields (`NetworkRunAheadSlack`,
  `NetworkKeepAliveDelay`, `NetworkDisconnectTime`,
  `NetworkPlayerTimeoutTime` and others); whether BFME 2 keeps them is not
  yet established. The lobby and error texts come from the string table
  ("LAN:...", "GUI:..." keys) and the screens are UI data
  (\ref sub_gui_apt). Limits, the command set and the wire format are
  code.
- **Every player needs the same data.** Lockstep sends commands, not
  state, so any change to INI, maps or scripts that alters logic results
  makes modded and unmodded players desync. The periodic logic CRC
  detects this during the game (\ref sub_save_load_crc); the INI CRC sent
  with a LAN join request may not be checked (see above).
- **Only maps and heroes are sent.** When a game starts, a player who
  lacks the map is sent it, and players' Create-a-Hero data is exchanged.
  Zero Hour's map transfer sends the map and, as its contents mask says,
  the files in the map's folder (preview image, `map.ini`, `map.str`,
  `solo.ini`, asset usage and readme), and nothing game-wide; BFME 2's
  transfer routine is not yet reconstructed. Plan on every player
  installing the same mod.
- **New actions reuse existing messages.** A new command button or power
  that uses an existing `GameMessage` type needs no network change. A new
  message or command type changes the wire format, and parsed game
  messages outside the known type range are dropped.
- **Hard-coded limits.** Eight player slots throughout (frame rings,
  connections, sockets, game slots) and the LAN port range.
- **Frame rates.** The logic and client frame rates are read from two
  globals that hold 5 and 30 per second in the shipped game; whether any
  data file sets them is not yet established.

## Remastering notes {#sub_network_remastering}

- **Seams.** `NetworkInterface` is the engine-facing seam, and one
  small function creates it for both lobbies. In the lockstep path the
  sockets sit behind `Transport` and `UDP`, so a replacement transport
  goes there and keeps the command layer. `LANAPI` and the GameSpy glue
  are lobby front ends that each start the same `NetworkInterface`.
- **Online services.** The GameSpy SDK and FESL/DirtySock code serve
  lobbies, chat, buddies, stats and ladders, and also NAT traversal and
  connection setup for online games (EA's ProtoMangle in DirtySock, and
  the NAT object whose transport the online launch attaches). The game
  packets themselves go through `Transport`. For online games the game
  socket comes from the NAT negotiation, which hands its transport to
  `TheNetwork`, so a replacement online service has to provide that
  peer-to-peer transport as well as the lobby screens.
- **Wire format is memory images.** Commands write fields as
  little-endian integers, IEEE floats and UTF-16 text, and packet bytes are
  obfuscated in 32-bit words with BFME 2's own mask constants, not Zero
  Hour's. Playing against retail clients needs the same layout,
  obfuscation, command numbering and checksums, and bit-identical logic
  results (\ref sub_save_load_crc).
- **Timing.** In a network game, logic frames are admitted by the
  network, not by the render rate; the router paces with
  `QueryPerformanceCounter`, and keep-alives and timeouts use
  `timeGetTime` (\ref page_frame_loop).
- **Platform calls.** Winsock, `GetUserNameA` and `GetComputerNameA` for
  LAN names, and an environment variable for the instance offset.

## State of the reconstruction {#sub_network_state}

The lockstep core is largely named and matched: `NetPacket`'s serialisers
and parsers, `ConnectionManager` and its command handlers, the frame
rings, the frame-admission queries, `Transport` and `UDP`, the LAN
handlers and much of `GameInfo` and `GameSlot`. The network's update and
light update are matched but still carry address names; the LAN lobby's
update is not yet reconstructed. Many BFME 2-only connection-manager
methods carry class and method names carried over from the BFME 1
reconstruction rather than from retail evidence. Most GameSpy SDK modules
are vendored C, matched and named; `chat/` and `peer/` are
reconstructions transcribed from the public SDK (see their
`PROVENANCE.txt` files). The FESL and DirtySock code is mostly
address-named. To refresh this picture, search `reverse/functions.csv`
and `reverse/link_status.csv` for the directories above.

## Reading list {#sub_network_reading}

- `docs/bfme2-network-timing-path.md`: frame admission, router pacing and
  the frame ceiling, with the evidence.
- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/`:
  `Include/GameNetwork/NetworkDefs.h` (command types and limits),
  `Source/GameNetwork/ConnectionManager.cpp`, `Network.cpp`,
  `NetPacket.cpp`, `Transport.cpp`, `FileTransfer.cpp`, `LANAPI.cpp` and
  `LANAPIhandlers.cpp`.
- BFME 1, in Open-BFME-1's `game/` tree:
  `GameEngine/Source/GameNetwork/native_connection_timing.cpp` and
  `native_network.cpp`.
- `Code/GameEngine/Source/GameNetwork/GameSpy/PROVENANCE.txt`, with
  `chat/PROVENANCE.txt` and `peer/PROVENANCE.txt`: which GameSpy SDK
  snapshot is vendored and how `chat/` and `peer/` were reconstructed.
