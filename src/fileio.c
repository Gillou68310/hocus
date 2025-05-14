#include "common.h"

// module: FILEIO
// size: 0x33
// addr: 05B3:0006
void open_database(void)
{
}

// module: FILEIO
// size: 0x14
// addr: 05B3:0039
void close_database(void)
{
}

// module: FILEIO
// size: 0x1e
// addr: 05B3:004D
void point_to_data(long offset)
{
}

// module: FILEIO
// size: 0x27
// addr: 05B3:006B
void point_to_data_record(int db_rec)
{
}

// module: FILEIO
// size: 0x3b
// addr: 05B3:0092
void load_to_byte_pointer(long offset, long length, void *ptr)
{
}

// module: FILEIO
// size: 0x3b
// addr: 05B3:00CD
void save_from_byte_pointer(long offset, long length, void *ptr)
{
}

// module: FILEIO
// size: 0x55
// addr: 05B3:0108
void load_file_to_byte_pointer(int db_rec, void *ptr)
{
    // stack: [BP-4]
    // size: 4
    long offset;
    // stack: [BP-8]
    // size: 4
    long length;
}

// module: FILEIO
// size: 0xa9
// addr: 05B3:015D
long load_disk_file(unsigned char *fln, void *ptr)
{
    // stack: [BP-4]
    // size: 4
    FILE *fp;
    // stack: [BP-8]
    // size: 4
    long length;
}

// module: FILEIO
// size: 0x6c
// addr: 05B3:0206
void save_disk_file(unsigned char *fln, void *ptr, unsigned int length)
{
    // stack: [BP-4]
    // size: 4
    FILE *fp;
}

// module: FILEIO
// size: 0x55
// addr: 05B3:0272
void save_file_from_byte_pointer(int db_rec, void *ptr)
{
    // stack: [BP-4]
    // size: 4
    long offset;
    // stack: [BP-8]
    // size: 4
    long length;
}

// module: FILEIO
// size: 0x16
// addr: 05B3:02C7
unsigned char char_from_database(void)
{
}