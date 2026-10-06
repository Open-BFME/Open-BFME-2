// cl: /DNDEBUG /MD
// BFME1 T3CommandLineParsers global-flag family; BFME2 live table81FBA0
// binds -preferLocalFiles to3B9455 (9 bytes). The -mod handler independently
// sets the same global at VA E06940. Global name is descriptive.
extern bool BFME2PreferLocalFiles;
// BFME2PreferLocalFiles: VA 0xe06940 (zero-filled .bss).
bool BFME2PreferLocalFiles;
int parsePreferLocalFiles(char *args[],int num) {
    BFME2PreferLocalFiles=true;
    return 1;
}
