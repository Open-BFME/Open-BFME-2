# Image TU: ImageCollectionDtor merged, FindImage waits for the census (2026-11-04)

Commits (claude seat, handed to the fleet publisher):

- Image.cpp adopts canonical `GameClient/Image.h`. Four typed ctor rows are ICF aliases
  (0x0033C432, 0x001F068F, 0x001F0534, 0x0014F3C4). Build 27/27; LINKS 1,210 -> 1,210.
- ImageCollectionFindImage.cpp adopts `Image.h` and drops the `bfme_image_name_fi` twin.
  Build 2/2; LINKS 101 -> 101.
- Rva0010461FCtor.cpp adopts `ImageClass.h`. Its private view's `getName` (+0x08) and
  `getImageSize` (+0x24) were `getFilename` and `getImageWidth`. Build 10/10; LINKS 978 -> 978.
- `tu_skeleton --merge Image.cpp` absorbed ImageCollectionDtor.cpp. Build 32/32;
  LINKS 1,210 -> 1,335.

Dry-run guard verdicts after the adoptions:

- ImageCollectionFindImage.cpp: "breaks another unit's copy of
  ?getName@Image@@QBEABVAsciiString@@XZ". The guard judges against the census view
  (2026-11-03 20:03 at 8661f15284). That view still holds Rva0010461FCtor's old
  unreferenced `getName` copy (`8d 41 08 c3`), and the merged TU's real copy is `8d 41 04 c3`.
  The current Rva0010461FCtor object no longer defines `getName@Image`. Retry the dry run
  after a census that includes the Rva0010461FCtor commit.
- FindImage still carries the header-queue row for class `Image`. The lane wants
  `ImageClass.h`, but `Image.h` defines its own copy of `class Image`. Unifying the two
  headers is a shared-header edit with about 51 includers.
- StlSweepW5Rva002D8FB7.cpp (bytes) and StlSweepW5Rva002D9186.cpp (`_M_erase` COMDAT,
  LINK-212) are unchanged.
