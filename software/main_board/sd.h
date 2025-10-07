#ifndef SD_H
#define SD_H

#include "FS.h"
#include "SD_MMC.h"

class SD {

    
private:
    int clk = 32;
    int cmd = 30;
    int d0 = 33;
    int d1 = 34;
    int d2 = 28;
    int d3 = 29;

    int det = 31;


public:
    SD();

    void createDir(fs::FS &fs, const char* path);

    void removeDir(fs::FS &fs, const char* path);

    void readFile(fs::FS &fs, const char* path);

    void writeFile(fs::FS &fs, const char* path);

    void appendFile(fs::FS &fs, const char* path, const char* message);

    void renameFile(fs::FS &fs, const char* path1, const char* path2);

    void deleteFile(fs::FS &fs, const char* path);

    void testFileIO(fs::FS &fs, const char* path);

};

#endif
