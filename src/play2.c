#include "common.h"
#include "gr.h"

// module: PLAY2
// size: 0x2ac
// addr: 134C:0007
void asm_show_background(unsigned char *srcp, unsigned char *destp)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // stack: [BP-10]
    // size: 2
    int bofs;
    // stack: [BP-12]
    // size: 2
    int ofs;
    // stack: [BP-14]
    // size: 2
    int bxs;

    latches(1);
    enable_pixels(0xf);
    mpos = scry * 0xf0 + scrmx;
    bxs = scrx % 0x50;
    ofs = 0;
    bofs = bxs;
    for (y = 0; y < 10; y++)
    {
        for (x = 0; x < 0x14; x++)
        {
            if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
            {
                if (bxs <= 0x4C)
                {
                    asm push    ds
                    asm lds     si, [srcp]
                    asm add     si, [bofs]
                    asm les     di, [destp]
                    asm add     di, [ofs]
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm pop     ds
                    ofs += 4;
                    bofs += 4;
                    bxs += 4;
                    if (bxs >= 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                }
            }
            else
            {
                ofs += 4;
                bofs += 4;
                bxs += 4;
                if (bxs >= 0x50)
                {
                    bxs -= 0x50;
                    bofs -= 0x50;
                }
            }
            mpos++;
        }
        ofs += 0x4B0;
        bofs += 0x500;
        mpos += 0xDC;
    }
}

// module: PLAY2
// size: 0x5b7
// addr: 134C:02B3
void asm_show_background_h(unsigned char *srcp, unsigned char *destp)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // stack: [BP-10]
    // size: 2
    int ofs;
    // stack: [BP-12]
    // size: 2
    int bofs;
    // stack: [BP-14]
    // size: 2
    int bxs;

    latches(1);
    enable_pixels(0xf);
    mpos = scry * 0xf0 + scrmx;
    bxs = scrx % 0x50;
    ofs = 0;
    bofs = bxs;
    for (y = 0; y < 10; y++)
    {
        if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
        {
            if (bxs <= 0x4E)
            {
                asm push    ds
                asm lds     si, [srcp]
                asm add     si, [bofs]
                asm les     di, [destp]
                asm add     di, [ofs]
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm pop     ds
                ofs += 2;
                bofs += 2;
                bxs += 2;
                if (bxs >= 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }

                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }
            }
        }
        else
        {
            ofs += 2;
            bofs += 2;
            bxs++;
            if (bxs == 0x50)
            {
                bxs = 0;
                bofs -= 0x50;
            }
            bxs++;
            if (bxs == 0x50)
            {
                bxs = 0;
                bofs -= 0x50;
            }
        }
        mpos++;
        for (x = 0; x < 0x13; x++)
        {
            if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
            {
                if (bxs <= 0x4C)
                {
                    asm push    ds
                    asm lds     si, [srcp]
                    asm add     si, [bofs]
                    asm les     di, [destp]
                    asm add     di, [ofs]
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm add     si, 4Ch
                    asm add     di, 4Ch
                    asm movsb
                    asm movsb
                    asm movsb
                    asm movsb
                    asm pop     ds
                    ofs += 4;
                    bofs += 4;
                    bxs += 4;
                    if (bxs >= 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                }
            }
            else
            {
                ofs += 4;
                bofs += 4;
                bxs += 4;
                if (bxs >= 0x50)
                {
                    bxs -= 0x50;
                    bofs -= 0x50;
                }
            }
            mpos++;
        }
        if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
        {
            if (bxs <= 0x4E)
            {
                asm push    ds
                asm lds     si, [srcp]
                asm add     si, [bofs]
                asm les     di, [destp]
                asm add     di, [ofs]
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm add     si, 4Eh
                asm add     di, 4Eh
                asm movsb
                asm movsb
                asm pop     ds
                ofs += 2;
                bofs += 2;
                bxs += 2;
                if (bxs >= 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }

                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }
            }
        }
        else
        {
            ofs += 2;
            bofs += 2;
            bxs += 2;
            if (bxs > 0x50)
            {
                bxs -= 0x50;
                bofs -= 0x50;
            }
        }
        ofs += 0x4B0;
        bofs += 0x500;
        mpos += 0xDC;
    }
}

// module: PLAY2
// size: 0x241
// addr: 134C:086A
void show_background(void)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // register: SI
    // size: 2
    int bofs;
    // register: DI
    // size: 2
    int ofs;
    // stack: [BP-10]
    // size: 2
    int bxs;

    latches(1);
    enable_pixels(0xf);
    mpos = scry * 0xf0 + scrmx;
    bxs = scrx % 0x50;
    ofs = 0;
    bofs = bxs;
    for (y = 0; y < 10; y++)
    {
        for (x = 0; x < 0x14; x++)
        {
            if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
            {
                if (bxs <= 0x4C)
                {
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        ofs += 0x4C;
                        bofs += 0x4C;
                    }
                    ofs -= 0x4FC;
                    bofs -= 0x4FC;
                    bxs += 4;
                    if (bxs >= 0x50)
                    {
                        bxs -= 0x50;
                        bofs -= 0x50;
                    }
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                }
            }
            else
            {
                ofs += 4;
                bofs += 4;
                bxs += 4;
                if (bxs >= 0x50)
                {
                    bxs -= 0x50;
                    bofs -= 0x50;
                }
            }
            mpos++;
        }
        ofs += 0x4B0;
        bofs += 0x500;
        mpos += 0xDC;
    }
}

// module: PLAY2
// size: 0x48b
// addr: 134C:0AAB
void show_background_h(void)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // register: DI
    // size: 2
    int ofs;
    // register: SI
    // size: 2
    int bofs;
    // stack: [BP-10]
    // size: 2
    int bxs;

    latches(1);
    enable_pixels(0xf);
    mpos = scry * 0xf0 + scrmx;
    bxs = scrx % 0x50;
    ofs = 0;
    bofs = bxs;
    for (y = 0; y < 10; y++)
    {
        if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
        {
            if (bxs <= 0x4E)
            {
                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs++;
                    bofs++;
                    vga[ofs] = vgap[3][bofs];
                    ofs++;
                    bofs++;
                    ofs += 0x4E;
                    bofs += 0x4E;
                }
                ofs -= 0x4FE;
                bofs -= 0x4FE;
                bxs += 2;
                if (bxs >= 0x50)
                {
                    bxs -= 0x50;
                    bofs -= 0x50;
                }
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }

                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }
            }
        }
        else
        {
            ofs += 2;
            bofs += 2;
            bxs++;
            if (bxs == 0x50)
            {
                bxs = 0;
                bofs -= 0x50;
            }
            bxs++;
            if (bxs == 0x50)
            {
                bxs = 0;
                bofs -= 0x50;
            }
        }
        mpos++;
        for (x = 0; x < 0x13; x++)
        {
            if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
            {
                if (bxs <= 0x4C)
                {
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        vga[ofs] = vgap[3][bofs];
                        ofs++;
                        bofs++;
                        ofs += 0x4C;
                        bofs += 0x4C;
                    }
                    ofs -= 0x4fc;
                    bofs -= 0x4fc;
                    bxs += 4;
                    if (bxs >= 0x50)
                    {
                        bxs -= 0x50;
                        bofs -= 0x50;
                    }
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }

                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                    for (i = 0; i < 16; i++)
                    {
                        vga[ofs] = vgap[3][bofs];
                        ofs += 0x50;
                        bofs += 0x50;
                    }
                    ofs -= 0x4FF;
                    bofs -= 0x4FF;
                    bxs++;
                    if (bxs == 0x50)
                    {
                        bxs = 0;
                        bofs -= 0x50;
                    }
                }
            }
            else
            {
                ofs += 4;
                bofs += 4;
                bxs += 4;
                if (bxs >= 0x50)
                {
                    bxs -= 0x50;
                    bofs -= 0x50;
                }
            }
            mpos++;
        }
        if ((bkg[mpos] == 0xff) && (sld[mpos] == 0xff))
        {
            if (bxs <= 0x4E)
            {
                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs++;
                    bofs++;
                    vga[ofs] = vgap[3][bofs];
                    ofs++;
                    bofs++;
                    ofs += 0x4E;
                    bofs += 0x4E;
                }
                ofs -= 0x4fe;
                bofs -= 0x4fe;
                bxs += 2;
                if (bxs >= 0x50)
                {
                    bxs -= 0x50;
                    bofs -= 0x50;
                }
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }

                for (i = 0; i < 16; i++)
                {
                    vga[ofs] = vgap[3][bofs];
                    ofs += 0x50;
                    bofs += 0x50;
                }
                ofs -= 0x4FF;
                bofs -= 0x4FF;
                bxs++;
                if (bxs == 0x50)
                {
                    bxs = 0;
                    bofs -= 0x50;
                }
            }
        }
        else
        {
            ofs += 2;
            bofs += 2;
            bxs += 2;
            if (bxs > 0x50)
            {
                bxs -= 0x50;
                bofs -= 0x50;
            }
        }
        ofs += 0x4B0;
        bofs += 0x500;
        mpos += 0xDC;
    }
}

// module: PLAY2
// size: 0xd0
// addr: 134C:0F36
void show_screen(unsigned char *vdest, unsigned char *vsrc, unsigned char *msld, unsigned char *mbkg, int mbx)
{
    asm cld
    asm push    ds
    asm mov     bx, [mbx]
    asm les     di, [vdest]
    asm mov     dh, 0Ah
label1:
    asm mov     dl, 14h
label2:
    asm lds     si, [msld]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label3
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label5
label3:
    asm lds     si, [mbkg]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label4
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label5
label4:
    asm add     di, 4
    asm jmp     label6
label5:
    asm lds     si, [vsrc]
    asm add     si, ax
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm sub     di, 4B0h
label6:
    asm inc     bx
    asm dec     dl
    asm jz      label7
    asm jmp     label2
label7:
    asm add     di, 4B0h
    asm add     bx, 0DCh 
    asm dec     dh
    asm jz      label8
    asm jmp     label1
label8:
    asm pop     ds
}

// module: PLAY2
// size: 0x236
// addr: 134C:1006
void show_screen_h(unsigned char *vdest, unsigned char *vsrc, unsigned char *msld, unsigned char *mbkg, int mbx)
{
    asm cld
    asm push    ds
    asm mov     bx, [mbx]
    asm les     di, [vdest]
    asm mov     dh, 0Ah
label1:
    asm lds     si, [msld]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label2
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label4
label2:
    asm lds     si, [mbkg]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label3
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label4
label3:
    asm add     di, 2
    asm jmp     label5
label4:  
    asm lds     si, [vsrc]
    asm add     si, ax
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm sub     di, 4B0h
label5:
    asm inc     bx
    asm mov     dl, 13h
label6:
    asm lds     si, [msld]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label7
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label9
label7:
    asm lds     si, [mbkg]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label8
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label9
label8:
    asm add     di, 4
    asm jmp     label10
label9:
    asm lds     si, [vsrc]
    asm add     si, ax
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm add     di, 4Ch 
    asm movsb
    asm movsb
    asm movsb
    asm movsb
    asm sub     di, 4B0h
label10:
    asm inc     bx
    asm dec     dl
    asm jz      label11
    asm jmp     label6
label11:
    asm lds     si, [msld]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label12
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label14
label12:
    asm lds     si, [mbkg]
    asm add     si, bx
    asm mov     ax, 0
    asm mov     al, [si]
    asm cmp     al, 0FFh
    asm jz      label13
    asm mov     cl, 6
    asm shl     ax, cl
    asm jmp     label14
label13:
    asm add     di, 2
    asm jmp     label15
label14:
    asm lds     si, [vsrc]
    asm add     si, ax
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm add     di, 4Eh 
    asm add     si, 2
    asm movsb
    asm movsb
    asm sub     di, 4B0h
label15:
    asm add     di, 4B0h
    asm add     bx, 0DCh 
    asm dec     dh
    asm jz      label16
    asm jmp     label1
label16:
    asm pop     ds
}