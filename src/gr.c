#include "common.h"
#include "gr.h"
#include "fileio.h"
#include "util.h"
#include "hocus.h"

// module: GR
// size: 0x4b
// addr: 0520:000B
void settext()
{
    // stack: [BP-16]
    // size: 16
    union REGS regs;
    // register: SI
    // size: 2
    int i;

    regs.h.ah = 0;
    regs.h.al = 3;
    int86(0x10, &regs, &regs);
    screen(0);
    for (i = 0; i < 0x37; i++)
    {
        wait_for_retrace();
    }
    screen(1);
}

#ifndef VERSION_PROTO
void gr_15D8E(int page)
{
    unsigned int addr;
    unsigned char raddr;

    addr = vgapofs[page];
    while ((inportb(0x3da) & 8))
        ;

    outportb(0x3d4, 0xc);
    raddr = addr >> 8;
    outportb(0x3d5, raddr);
    outportb(0x3d4, 0xd);
    raddr = addr;
    outportb(0x3d5, raddr);
    while (!(inportb(0x3da) & 8))
        ;
    vpg = page;
}
#endif

// module: GR
// size: 0x48
// addr: 0520:0056
void setvpage(int page)
{
    // register: SI
    // size: 2
    // int page;
    // stack: [BP-2]
    // size: 2
    unsigned int addr;
    // stack: [BP-3]
    // size: 1
    unsigned char raddr;

    addr = vgapofs[page];
    outportb(0x3d4, 0xc);
    raddr = addr >> 8;
    outportb(0x3d5, raddr);
    outportb(0x3d4, 0xd);
    raddr = addr;
    outportb(0x3d5, raddr);
    vpg = page;
}

// module: GR
// size: 0x23
// addr: 0520:009E
void setapage(int page)
{
    // register: SI
    // size: 2
    // int page;
    vga = vgap[page];
    apg = page;
}

// module: GR
// size: 0x1f
// addr: 0520:00C1
void wait_for_retrace(void)
{
    while ((inportb(0x3da) & 8))
        ;
    while (!(inportb(0x3da) & 8))
        ;
}

// module: GR
// size: 0x12
// addr: 0520:00E0
void setreadplane(unsigned char plane)
{
    outportb(0x3ce, 4);
    outportb(0x3cf, plane);
}

// module: GR
// size: 0x23
// addr: 0520:00F2
void screen(unsigned char on)
{
    outportb(0x3c4, 1);
    if (on != 0)
    {
        outportb(0x3c5, inportb(0x3c5) & 0xdf);
    }
    else
    {
        outportb(0x3c5, inportb(0x3c5) | 0x20);
    }
}

// module: GR
// size: 0x12
// addr: 0520:0115
void enable_pixels(unsigned char mask)
{
    outportb(0x3c4, 2);
    outportb(0x3c5, mask);
}

// module: GR
// size: 0x1c
// addr: 0520:0127
void latches(int on)
{
    outportb(0x3ce, 8);
    outportb(0x3cf, (!on) * 0xFF);
}

// module: GR
// size: 0x73
// addr: 0520:0143
void setvga(void)
{
    // register: DI
    // size: 2
    int i;

    SET320X200();
    for (i = 0; i < VGA_PAGE_COUNT; i++)
    {
#ifndef VERSION_PROTO
        vgapofs[i] = i * (VGA_PAGE_SIZE + 128);
        vgap[i] = vgabase + i * (VGA_PAGE_SIZE + 128);
#else
        vgapofs[i] = i * VGA_PAGE_SIZE;
        vgap[i] = vgabase + i * VGA_PAGE_SIZE;
#endif
        setmem(vgap[i], VGA_PAGE_SIZE, 0);
    }
    setapage(0);
    setvpage(0);
}

// module: GR
// size: 0x40
// addr: 0520:01B6
void scopy(int dest, int src)
{
    latches(1);
    enable_pixels(0xf);
    MCPY(vgap[dest], vgap[src], VGA_PAGE_SIZE);
}

// module: GR
// size: 0x81
// addr: 0520:01F6
void copyblock(int sp, int lx, int ty, int rx, int by, int dp, int dx, int dy)
{
    // register: DI
    // size: 2
    // int lx;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-2]
    // size: 2
    int l;

    l = (rx - lx) + 1;
    latches(1);
    enable_pixels(0xf);
    for (y = ty; y <= by; y++)
    {
        MCPY(&((line_t)vgap[dp])[dy][dx], &((line_t)vgap[sp])[y][lx], l);
        // MCPY(vgap[dp]+dy*VGA_PLANE_WIDTH+dx, vgap[sp]+y*VGA_PLANE_WIDTH+lx, l);
    }
}

// module: GR
// size: 0x2c
// addr: 0520:0277
void clearscreen(void)
{
    latches(0);
    enable_pixels(0xf);
    setmem(vga, VGA_PAGE_SIZE, 0);
}

// module: GR
// size: 0x4d
// addr: 0520:02A3
void clearbox(int lx, int ty, int rx, int by)
{
    // register: SI
    // size: 2
    // int ty;
    // register: DI
    // size: 2
    // int lx;

    latches(0);
    enable_pixels(0xf);
    for (; ty <= by; ty++)
    {
        setmem(&((line_t)vga)[ty][lx], (rx - lx) + 1, 0);
        // setmem(vga + ty * VGA_PLANE_WIDTH + lx, (rx - lx) + 1, 0);
    }
}

// module: GR
// size: 0x37
// addr: 0520:02F0
int pixel_clr(int x, int y)
{
    // register: SI
    // size: 2
    // int x;

    setreadplane(x % VGA_PLANE_COUNT);
    return ((line_t)vga)[y][x / VGA_PLANE_COUNT];
    // return *((vga + y * VGA_PLANE_WIDTH) + x / 4);
}

// module: GR
// size: 0x3a
// addr: 0520:0327
void pixel(int x, int y, int c)
{
    // register: SI
    // size: 2
    // int x;

    enable_pixels(1 << ((x % VGA_PLANE_COUNT)));
    ((line_t)vga)[y][x >> VGA_PLANE_SHIFT] = c;
    //*(vga + y * VGA_PLANE_WIDTH + (x >> 2)) = c;
}

// module: GR
// size: 0x2b
// addr: 0520:0361
void blankpixelbox(int lx, int ty, int rx, int by)
{
    // register: SI
    // size: 2
    // int ty;
    // register: DI
    // size: 2
    int i;

    for (; ty <= by; ty++)
    {
        for (i = lx; i <= rx; i++)
        {
            pixel(i, ty, 0);
        }
    }
}

// module: GR
// size: 0x3e
// addr: 0520:038C
void write_pels(unsigned char *rgb, unsigned char pel_start, int pel_count)
{
    // register: CX
    // size: 2
    // int pel_count;

    outportb(0x3c8, pel_start);
    while (pel_count-- > 0)
    {
        outportb(0x3c9, *rgb++);
        outportb(0x3c9, *rgb++);
        outportb(0x3c9, *rgb++);
    }
}

// module: GR
// size: 0x3f
// addr: 0520:03CA
void read_pels(unsigned char *rgb, unsigned char pel_start, int pel_count)
{
    // register: CX
    // size: 2
    // int pel_count;

    outportb(0x3c7, pel_start);
    while (pel_count-- > 0)
    {
        *rgb++ = inportb(0x3c9);
        *rgb++ = inportb(0x3c9);
        *rgb++ = inportb(0x3c9);
    }
}

// module: GR
// size: 0x58
// addr: 0520:0409
void fade_out(int scans)
{
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int j;

    for (i = 0; i < sizeof(tpal); i++)
    {
        tpal[i] = palette[i];
    }
    for (j = scans; j >= 0; j--)
    {
        for (i = 0; i < sizeof(tpal); i++)
        {
            tpal[i] = (palette[i] * j) / scans;
        }
        wait_for_retrace();
        write_pels(tpal, 0, 0x100);
    }
}

// module: GR
// size: 0x45
// addr: 0520:0461
void fade_in(int scans)
{
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int j;

    for (j = 0; j <= scans; j++)
    {
        for (i = 0; i < sizeof(tpal); i++)
        {
            tpal[i] = (palette[i] * j) / scans;
        }
        wait_for_retrace();
        write_pels(tpal, 0, 0x100);
    }
}

// module: GR
// size: 0x46
// addr: 0520:04A6
void fade_in_white(void)
{
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int j;

    for (j = 0; j < 0x46; j++)
    {
        for (i = 0; i < sizeof(palette); i++)
        {
            if (palette[i] < 0x3f)
            {
                palette[i] = palette[i] + 1;
            }
        }
        wait_for_retrace();
        write_pels(palette, 0, 0x100);
    }
}

// module: GR
// size: 0x2a
// addr: 0520:04EC
void clear_palette(void)
{
    // register: SI
    // size: 2
    int i;

    for (i = 0; i < sizeof(tpal); i++)
    {
        tpal[i] = 0;
    }

    write_pels(tpal, 0, 0x100);
}

// module: GR
// size: 0x18
// addr: 0520:0516
void turn_on_palette(void)
{
    write_pels(palette, 0, 0x100);
}

// module: GR
// size: 0x15e
// addr: 0520:052E
void unpackpcxfile(void)
{
    // register: SI
    // size: 2
    int nn;
    // register: DI
    // size: 2
    int n;
    // stack: [BP-2]
    // size: 2
    int c;
    // stack: [BP-4]
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 2
    int j;
    // stack: [BP-326]
    // size: 320
    unsigned char line[4][VGA_PLANE_WIDTH];

    for (i = 0; i < depth; i++)
    {
        n = nn = 0;
        do
        {
            c = char_from_database() & 0xFF;
            if ((c & 0xc0) == 0xc0)
            {
                j = c & 0x3f;
                c = char_from_database();
                while (j-- != 0)
                {
                    line[nn][n >> VGA_PLANE_SHIFT] = c;
                    n++;
                    nn++;
                    if (nn > 3)
                    {
                        nn = 0;
                    }
                }
            }
            else
            {
                line[nn][n >> VGA_PLANE_SHIFT] = c;
                n++;
                nn++;
                if (nn > 3)
                {
                    nn = 0;
                }
            }
        } while (n < bytes);

        latches(0);
        outportb(0x3c4, 2);
        j = i * sizeof(line[0]);
        outportb(0x3c5, 1);
        MCPY(&vga[j], line[0], sizeof(line[0]));
        outportb(0x3c5, 2);
        MCPY(&vga[j], line[1], sizeof(line[0]));
        outportb(0x3c5, 4);
        MCPY(&vga[j], line[2], sizeof(line[0]));
        outportb(0x3c5, 8);
        MCPY(&vga[j], line[3], sizeof(line[0]));
    }
}

// module: GR
// size: 0xc4
// addr: 0520:068C
void load_pcx(int db_rec, int setpal)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-4]
    // size: 4
    long offset;
    // stack: [BP-8]
    // size: 4
    long length;

#ifndef VERSION_PROTO
    open_database();
#endif
    get_offset_length(db_rec, &offset, &length);
    load_to_byte_pointer(offset, sizeof(PCXHEAD), &header.manufacturer);
    load_to_byte_pointer((offset + length) - sizeof(palette), sizeof(palette), palette);

    for (i = 0; i < sizeof(palette); i++)
    {
        palette[i] >>= 2;
    }
    if (setpal != 0)
    {
        write_pels(palette, 0, 0x100);
    }

    point_to_data(offset + sizeof(PCXHEAD));
    width = header.xmax - header.xmin + 1;
    depth = header.ymax - header.ymin + 1;
    bytes = header.bytes_per_line;
    unpackpcxfile();
#ifndef VERSION_PROTO
    close_database();
#endif
}

#if VERSION_11 || VERSION_DEMO11
void unpackpcxfile_from_file(void)
{
    // register: SI
    // size: 2
    int nn;
    // register: DI
    // size: 2
    int n;
    // stack: [BP-2]
    // size: 2
    int c;
    // stack: [BP-4]
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 2
    int j;
    // stack: [BP-326]
    // size: 320
    unsigned char line[4][VGA_PLANE_WIDTH];

    for (i = 0; i < depth; i++)
    {
        n = nn = 0;
        do
        {
            c = fgetc(database_file) & 0xFF;
            if ((c & 0xc0) == 0xc0)
            {
                j = c & 0x3f;
                c = fgetc(database_file);
                while (j-- != 0)
                {
                    line[nn][n >> VGA_PLANE_SHIFT] = c;
                    n++;
                    nn++;
                    if (nn > 3)
                    {
                        nn = 0;
                    }
                }
            }
            else
            {
                line[nn][n >> VGA_PLANE_SHIFT] = c;
                n++;
                nn++;
                if (nn > 3)
                {
                    nn = 0;
                }
            }
        } while (n < bytes);

        latches(0);
        outportb(0x3c4, 2);
        j = i * sizeof(line[0]);
        outportb(0x3c5, 1);
        MCPY(&vga[j], line[0], sizeof(line[0]));
        outportb(0x3c5, 2);
        MCPY(&vga[j], line[1], sizeof(line[0]));
        outportb(0x3c5, 4);
        MCPY(&vga[j], line[2], sizeof(line[0]));
        outportb(0x3c5, 8);
        MCPY(&vga[j], line[3], sizeof(line[0]));
    }
}

int load_pcx_from_file(char *path)
{
    int i;

    database_file = fopen(path, "rb");
    if (database_file == NULL)
        return 0;

    fread(&header, sizeof(PCXHEAD), 1, database_file);
    fseek(database_file, -(int)sizeof(palette), 2);
    fread(palette, sizeof(palette), 1, database_file);
    for (i = 0; i < sizeof(palette); i++)
    {
        palette[i] >>= 2;
    }
    fseek(database_file, sizeof(PCXHEAD), 0);
    width = header.xmax - header.xmin + 1;
    depth = header.ymax - header.ymin + 1;
    bytes = header.bytes_per_line;
    unpackpcxfile_from_file();
    fclose(database_file);
    return 1;
}
#endif

// module: GR
// size: 0x8a
// addr: 0520:0750
void capture_screen(void)
{
    // stack: [BP-2]
    // size: 2
    int p;
    // register: SI
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 4
    FILE *fp;

    fp = fopen("screen1.bin", "w+b");
    fwrite(palette, sizeof(palette), 1, fp);
    for (p = 0; p < 4; p++)
    {
        setreadplane(p);
        for (i = 0; i < VGA_PAGE_SIZE; i++)
        {
            fputc(vga[i], fp);
        }
    }
    fclose(fp);
}

// module: GR
// size: 0x8c
// addr: 0520:07DA
void show_bin(int db_rec)
{
    // stack: [BP-2]
    // size: 2
    int p;
    // register: SI
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 4
    long offset;

#ifndef VERSION_PROTO
    open_database();
#endif
    get_offset(db_rec, &offset);
    load_to_byte_pointer(offset, sizeof(palette), palette);
    point_to_data(offset + sizeof(palette));
    for (p = 0; p < 4; p++)
    {
        enable_pixels(1 << p);
        for (i = 0; i < VGA_PAGE_SIZE; i++)
        {
            vga[i] = fgetc(databasefp);
        }
    }
#ifndef VERSION_PROTO
    close_database();
#endif
}

// module: GR
// size: 0x92
// addr: 0520:0866
void restore_graphics_fragment(int db_rec, int sx, int sy)
{
    // register: SI
    // size: 2
    int x;
    // register: DI
    // size: 2
    int y;
    // stack: [BP-2]
    // size: 2
    int p;
    // stack: [BP-6]
    // size: 4
    long offset;

#ifndef VERSION_PROTO
    open_database();
#endif
    get_offset(db_rec, &offset);
    load_to_byte_pointer(offset, sizeof(grphdr_t), &grphdr);
    latches(0);
    for (p = 0; p < 4; p++)
    {
        enable_pixels(1 << p);
        for (y = 0; y < grphdr.yw; y++)
        {
            for (x = 0; x < grphdr.xw; x++)
            {
                ((line_t)vga)[sy + y][sx + x] = char_from_database();
            }
        }
    }
#ifndef VERSION_PROTO
    close_database();
#endif
}

// module: GR
// size: 0x3e
// addr: 0520:08F8
void restore_palette_fragment(int db_rec, int s, int setpal)
{
    // register: SI
    // size: 2
    // int s;

#ifndef VERSION_PROTO
    open_database();
#endif
    s *= 3;
    load_file_to_byte_pointer(db_rec, palette + s);
    if (setpal != 0)
    {
        write_pels(palette, 0, 0x100);
    }
#ifndef VERSION_PROTO
    close_database();
#endif
}