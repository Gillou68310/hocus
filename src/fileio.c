#include "common.h"
#include "util.h"
#include "hocus.h"

// module: FILEIO
// size: 0x33
// addr: 05B3:0006
void open_database(void)
{
    if ((databasefp = fopen("HOCUS.DAT", "r+b")) == NULL)
    {
        terminate_emsg(1, "DB");
    }
}

// module: FILEIO
// size: 0x14
// addr: 05B3:0039
void close_database(void)
{
    fclose(databasefp);
}

// module: FILEIO
// size: 0x1e
// addr: 05B3:004D
void point_to_data(long offset)
{
    fseek(databasefp, offset, 0);
}

// module: FILEIO
// size: 0x27
// addr: 05B3:006B
void point_to_data_record(int db_rec)
{
    fseek(databasefp, db[db_rec].ofs, 0);
}

// module: FILEIO
// size: 0x3b
// addr: 05B3:0092
void load_to_byte_pointer(long offset, long length, void *ptr)
{
    fseek(databasefp, offset, 0);
    fread(ptr, length, 1, databasefp);
}

// module: FILEIO
// size: 0x3b
// addr: 05B3:00CD
void save_from_byte_pointer(long offset, long length, void *ptr)
{
    fseek(databasefp, offset, 0);
    fwrite(ptr, length, 1, databasefp);
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

    get_offset_length(db_rec, &offset, &length);
    fseek(databasefp, offset, 0);
    fread(ptr, length, 1, databasefp);
}

#if VERSION_PROTO
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

    fp = fopen(fln, "rb");
    if (fp == NULL)
    {
        terminate("Bad Disk File Name");
    }
    fseek(fp, 0, 2);
    length = ftell(fp);
    fseek(fp, 0, 0);
    fread(ptr, length, 1, fp);
    fclose(fp);
    return length;
}

// module: FILEIO
// size: 0x6c
// addr: 05B3:0206
void save_disk_file(unsigned char *fln, void *ptr, unsigned int length)
{
    // stack: [BP-4]
    // size: 4
    FILE *fp;

    unlink(fln);
    fp = fopen(fln, "wb");
    if (fp == NULL)
    {
        terminate("Cannot Save Disk File");
    }
    fwrite(ptr, length, 1, fp);
    fclose(fp);
}
#else
int load_disk_file(unsigned char *fln, void *ptr)
{
    FILE *fp;
    long length;

    fp = fopen(fln, "rb");
    if (fp == NULL)
    {
        return 0;
    }
    fseek(fp, 0, 2);
    length = ftell(fp);
    fseek(fp, 0, 0);
    if (fread(ptr, length, 1, fp) < 1)
    {
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

int save_disk_file(unsigned char *fln, void *ptr, unsigned int length)
{
    FILE *fp;

    unlink(fln);
    fp = fopen(fln, "wb");
    if (fp == NULL)
    {
        return 0;
    }
    if (fwrite(ptr, length, 1, fp) < 1)
    {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}
#endif

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

    get_offset_length(db_rec, &offset, &length);
    fseek(databasefp, offset, 0);
    fwrite(ptr, length, 1, databasefp);
}

// module: FILEIO
// size: 0x16
// addr: 05B3:02C7
unsigned char char_from_database(void)
{
    return fgetc(databasefp);
}