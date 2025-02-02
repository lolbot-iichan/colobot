#include <physfs.h>

PHYSFS_File *LoudOpenWrite(const char *filename);
PHYSFS_File *LoudOpenAppend(const char *filename);
PHYSFS_File *LoudOpenRead(const char *filename);
