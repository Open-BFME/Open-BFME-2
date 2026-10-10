# docs/doxygen: the developer guide

A hand-written Doxygen guide to the reconstructed engine, for human
developers who are new to the code. It is built locally and not published,
and nothing in the build, the hooks or CI depends on it. Agents doing
matching work do not need to read it.

## Build and check

    mkdir -p build/doxygen && doxygen docs/doxygen/Doxyfile
    python3 tools/doc_lint.py --doxygen

The HTML lands in `build/doxygen/html/` and the warnings in
`build/doxygen/warnings.log` (`build/` is ignored). `doc_lint` is advisory;
`--doxygen` runs Doxygen and reports its warnings about files in this
directory, `--staged` lints the staged copies and refuses a docs commit that
touches `Code/`, `reference/` or `reverse/`. Its tests are
`tools/tests/test_doc_lint.py`.

## Layout

    Doxyfile               configuration
    sources.cfg            source files Doxygen reads declarations from
    strip_comments.py      input filter: strips every comment from those files
    pages/<slug>.md        guide pages
    pages/subsystems/<slug>.md
                           one page per subsystem
    api/<slug>.dox         per subsystem: its group, and class, function and
                           file docs written as triple-slash blocks

Documentation never goes into `Code/` or `reference/`. Comments there are
notes for byte matching, often in Doxygen syntax, so the filter removes all of
them before Doxygen parses a listed file. A `\class` block publishes without
any listed source, but a member's `\fn` block needs the file that declares the
class listed in `sources.cfg` (Doxygen warns and drops it otherwise), and a
`\file` block needs the file it describes. Undocumented members and the many
per-file partial views of a class stay hidden.

## Ids

Every id is global, so it carries a prefix naming its kind:

| Kind | File | Id |
|---|---|---|
| guide page | `pages/<slug>.md` | `page_<slug>` on the first heading |
| subsystem page | `pages/subsystems/<slug>.md` | `sub_<slug>` on the first heading |
| subsystem group | `api/<slug>.dox` | `\defgroup grp_<slug>` |
| section | inside a page | the page id, `_`, a section slug |
| subgroup | inside `api/<slug>.dox` | `grp_<slug>_<topic>` |

A subsystem page and its group share the slug and link to each other.
Reserved ids:

| Id | Page |
|---|---|
| `page_mainpage` | main page (`pages/mainpage.md`; Doxygen also calls it `index`) |
| `page_reading_code` | how to read this source, including the staging areas and generated placeholders (section `page_reading_code_staging`) |
| `page_architecture` | layers, singletons, the subsystem map |
| `page_startup` | process start to the first frame |
| `page_frame_loop` | the client frame and the logic tick |
| `page_glossary` | terms |
| `page_core_frameworks` | base types and math; global data; deterministic random values; messages and command lists; weapons, damage and armor; upgrades, sciences and special powers; command sets and buttons |
| `page_modding` | what game data controls and what a mod must keep intact |
| `page_remastering` | platform seams and the assumptions built into the code |

| Slug | Subsystem |
|---|---|
| `engine_core` | engine core, startup and main loop |
| `common_services` | file system, BIG archives, strings, name keys, debug and profile |
| `memory` | memory pools and allocators |
| `save_load_crc` | save and load, CRC and replay |
| `ini` | INI and data definition loading |
| `rts_model` | players, teams, things, templates and the module factory |
| `objects_modules` | game objects and their modules |
| `ai_pathfinding` | AI, pathfinding and skirmish AI |
| `scripting` | map scripts and Lua |
| `gamelogic_map` | the game logic system and the map |
| `living_world` | the Living World (War of the Ring) campaign |
| `gameclient` | drawables, FX, particles, input and the message stream |
| `gui_apt` | GUI and the Apt UI |
| `network` | lockstep networking, LAN and online services |
| `audio` | audio |
| `w3d_rendering` | W3D rendering |
| `wwlib_thirdparty` | the WWLib foundation and third-party libraries |

The main page lists the guide pages with `\subpage`; the architecture page
lists the subsystem pages.
A reserved subsystem page that is not written yet is a stub that says so,
with a matching stub group, so that links to it resolve; writing the page
replaces both.

## Writing rules

- Derive, never invent. In order of strength, a statement rests on the
  matched body, its matched callers and callees (`tools/callers_of.py`),
  retail data such as exports, vtables and assert strings
  (`tools/wb_show.py` shows the WorldBuilder twin), or a donor: the Zero Hour
  source under `reference/open-bfme-1/inputs/reference/` or Open-BFME-1's
  `game/` tree. State a donor fact as one ("Zero Hour: ...") unless BFME 2
  evidence confirms it, and say so where something is uncertain.
- Name functions and classes; never copy retail addresses, sizes or member
  offsets, which change as rows are repaired and layouts reconciled.
  Describe a field by its role.
- Skip placeholder-named code (address-named functions and files, `Bfme` and
  `bfme` names, generated and duplicate rows) and names the ledger marks as
  unconfirmed WorldBuilder leads.
- Code still under active reverse engineering gets its contract only.
- Never write the strings repository tools parse out of source comments,
  even as prose; `doc_lint` lists them. Keep the text ASCII.
- Keep pages short and skimmable, and link instead of repeating.

## Commits

A commit that touches only `docs/` takes the pre-commit hook's early exit
after its static checks; nothing is compiled. Stage explicit
paths, keep documentation commits separate from code and ledger changes, and
run `python3 tools/doc_lint.py --staged` first.
