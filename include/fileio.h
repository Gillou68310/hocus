#ifndef __FILEIO_H__
#define __FILEIO_H__

void open_database(void);
void close_database(void);
void point_to_data(long offset);
void point_to_data_record(int db_rec);
void load_to_byte_pointer(long offset, long length, void *ptr);
void save_from_byte_pointer(long offset, long length, void *ptr);
void load_file_to_byte_pointer(int db_rec, void *ptr);
long load_disk_file(unsigned char *fln, void *ptr);
void save_disk_file(unsigned char *fln, void *ptr, unsigned int length);
void save_file_from_byte_pointer(int db_rec, void *ptr);
unsigned char char_from_database(void);

#endif