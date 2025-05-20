#ifndef __DECLS_H__
#define __DECLS_H__

// addr: 192E:1B44
// size: 72
extern int song2play[4][9];

// addr: 192E:1B8C
// size: 160
extern int lrelev[4][10][2];

// addr: 192E:1C2C
// size: 8
extern int b4x[4];

// addr: 192E:1C34
// size: 8
extern int b4y[4];

// addr: 192E:1C3C
// size: 8
extern int b4m[4];

// addr: 192E:1C44
// size: 8
extern int b4d[4];

// addr: 192E:1C4C
// size: 8
extern int b4s[4];

// addr: 192E:1C54
// size: 50
extern int hsjumpadd[25];

// addr: 192E:1C86
// size: 38
extern int hnjumpadd[19];

// addr: 192E:1CAC
// size: 8
extern int hurtpower[4];

// addr: 192E:2452
// size: 4
extern unsigned char *buf64;

// addr: 192E:2456
// size: 956
extern struct struct_31 game_config;

// addr: 192E:2812
// size: 2880
extern long l_sine_cosine_table[360][2];

// addr: 192E:3352
// size: 2880
extern float sine_cosine_table[360][2];

// addr: 192E:3E92
// size: 4
extern struct struct_46 grphdr;

// addr: 192E:3E96
// size: 48
extern long pcs_sample_length[12];

// addr: 192E:3EC6
// size: 2
extern int pcs_sampleplaying;

// addr: 192E:3EC8
// size: 2
extern int pcs_sample_pnt;

// addr: 192E:3ECA
// size: 2
extern int pcs_sample;

// addr: 192E:3ECC
// size: 48
extern int *pcs_mem[12];

// addr: 192E:3EFC
// size: 48
extern unsigned char *sfx_mem[12];

// addr: 192E:3F2C
// size: 2
extern int current_sound_priority;

// addr: 192E:3F2E
// size: 4
extern int *imf_music;

// addr: 192E:3F32
// size: 2
extern int nocard;

// addr: 192E:3F34
// size: 2
extern int noblaster;

// addr: 192E:3F36
// size: 2
extern int blaster;

// addr: 192E:3F38
// size: 2
extern int adlib;

// addr: 192E:3F3A
// size: 4
extern unsigned char *font;

// addr: 192E:3F3E
// size: 2
extern int vpg;

// addr: 192E:3F40
// size: 2
extern int apg;

// addr: 192E:3F42
// size: 8
extern unsigned int vgapofs[4];

// addr: 192E:3F4A
// size: 16
extern unsigned char *vgap[4];

// addr: 192E:3F5A
// size: 4
extern unsigned char *vga;

// addr: 192E:3F5E
// size: 768
extern unsigned char temppal[768];

// addr: 192E:425E
// size: 768
extern unsigned char tpal[768];

// addr: 192E:455E
// size: 768
extern unsigned char palette[768];

// addr: 192E:485E
// size: 4
extern FILE *databasefp;

// addr: 192E:4862
// size: 724
extern struct struct_59 anminfo;

// addr: 192E:4B36
// size: 8
extern struct struct_62 lvlinfo;

// addr: 192E:4B3E
// size: 2
extern int oldhfirepower;

// addr: 192E:4B40
// size: 2
extern int hfirepower;

// addr: 192E:4B42
// size: 2
extern int crystals_found;

// addr: 192E:4B44
// size: 2
extern int crystals;

// addr: 192E:4B46
// size: 2
extern int health;

// addr: 192E:4B48
// size: 4
extern long oldscore;

// addr: 192E:4B4C
// size: 4
extern long score;

// addr: 192E:4B50
// size: 4
extern unsigned char *swe;

// addr: 192E:4B54
// size: 4
extern int *fnc;

// addr: 192E:4B58
// size: 4
extern unsigned char *sldsav;

// addr: 192E:4B5C
// size: 4
extern unsigned char *sld;

// addr: 192E:4B60
// size: 4
extern unsigned char *bkg;

// addr: 192E:4B64
// size: 2
extern int skill;

// addr: 192E:4B66
// size: 2
extern int level;

// addr: 192E:4B68
// size: 2
extern int game;

// addr: 192E:4B6A
// size: 40
extern unsigned char *spr_code[10];

// addr: 192E:4B92
// size: 1
extern unsigned char pause;

// addr: 192E:4B93
// size: 1
extern unsigned char gkey;

// addr: 192E:4B94
// size: 1
extern unsigned char anykey;

// addr: 192E:4B95
// size: 1
extern unsigned char sndkey;

// addr: 192E:4B96
// size: 1
extern unsigned char muskey;

// addr: 192E:4B97
// size: 1
extern unsigned char calkey;

// addr: 192E:4B98
// size: 1
extern unsigned char helpkey;

// addr: 192E:4B99
// size: 1
extern unsigned char f10key;

// addr: 192E:4B9A
// size: 1
extern unsigned char f3key;

// addr: 192E:4B9B
// size: 1
extern unsigned char f2key;

// addr: 192E:4B9C
// size: 1
extern unsigned char pgdnkey;

// addr: 192E:4B9D
// size: 1
extern unsigned char pgupkey;

// addr: 192E:4B9E
// size: 1
extern unsigned char fkeyclr;

// addr: 192E:4B9F
// size: 1
extern unsigned char jkeyclr;

// addr: 192E:4BA0
// size: 1
extern unsigned char ukeyclr;

// addr: 192E:4BA1
// size: 1
extern unsigned char qkey;

// addr: 192E:4BA2
// size: 1
extern unsigned char jkey;

// addr: 192E:4BA3
// size: 1
extern unsigned char fkey;

// addr: 192E:4BA4
// size: 1
extern unsigned char rkey;

// addr: 192E:4BA5
// size: 1
extern unsigned char lkey;

// addr: 192E:4BA6
// size: 1
extern unsigned char dkey;

// addr: 192E:4BA7
// size: 1
extern unsigned char ukey;

// addr: 192E:4BA8
// size: 1
extern unsigned char cukey;

// addr: 192E:4BA9
// size: 1
extern unsigned char skiptitle;

// addr: 192E:4BAA
// size: 21
extern unsigned char dumnum[21];

// addr: 192E:4BBF
// size: 81
extern unsigned char dline[81];

// addr: 192E:4C10
// size: 2
extern int rndnum;

// addr: 192E:4C12
// size: 2000
extern int rnd[1000];

// addr: 192E:53E2
// size: 4
extern long musiclooped;

// addr: 192E:53E6
// size: 4
extern long total_ticks;

// addr: 192E:53EA
// size: 4
extern long clk_times;

// addr: 192E:53EE
// size: 2
extern int indemo;

// addr: 192E:53F0
// size: 2
extern unsigned int bytes;

// addr: 192E:53F2
// size: 2
extern unsigned int depth;

// addr: 192E:53F4
// size: 2
extern unsigned int width;

// addr: 192E:53F6
// size: 128
extern PCXHEAD header;

// addr: 192E:5476
// size: 75
extern unsigned char star_clrplus[75];

// addr: 192E:54C1
// size: 75
extern unsigned char star_clrcnt[75];

// addr: 192E:550C
// size: 75
extern unsigned char star_radplus[75];

// addr: 192E:5558
// size: 150
extern int star_rad[75];

// addr: 192E:55EE
// size: 150
extern int star_deg[75];

// addr: 192E:5684
// size: 4
extern int *textbase;

// addr: 192E:5688
// size: 2
extern int playmenuip;

// addr: 192E:568A
// size: 2
extern int menu_first_title;

// addr: 192E:568C
// size: 2
extern int menu_footer;

// addr: 192E:568E
// size: 2
extern int menu_item_num;

// addr: 192E:5690
// size: 40
extern unsigned char *menu_item_labels[10];

// addr: 192E:56B8
// size: 1686
extern struct struct_98 inf;

// addr: 192E:5D4E
// size: 2
extern int gmenunum;

// addr: 192E:5D50
// size: 2
extern int iconmax;

// addr: 192E:5D52
// size: 2
extern int iconpos;

// addr: 192E:5D54
// size: 40
extern int icony[20];

// addr: 192E:5D7C
// size: 2
extern int iconx;

// addr: 192E:5D7E
// size: 768
extern unsigned char savepalette[768];

// addr: 192E:607E
// size: 2
extern int block;

// addr: 192E:6080
// size: 2
extern int bby;

// addr: 192E:6082
// size: 2
extern int bty;

// addr: 192E:6084
// size: 2
extern int brx;

// addr: 192E:6086
// size: 2
extern int blx;

// addr: 192E:6088
// size: 2
extern int palette_pnt;

// addr: 192E:608A
// size: 2
extern int mofs;

// addr: 192E:608C
// size: 2
extern int sdy;

// addr: 192E:608E
// size: 2
extern int sdx;

// addr: 192E:6090
// size: 2
extern int dy;

// addr: 192E:6092
// size: 2
extern int dx;

// addr: 192E:6094
// size: 2
extern int dlevel;

// addr: 192E:6096
// size: 8000
extern struct struct_115 mtriggers[250];

// addr: 192E:7FD6
// size: 240
extern struct struct_118 mtags[10];

// addr: 192E:80C6
// size: 300
extern struct struct_120 etrips[25];

// addr: 192E:81F2
// size: 300
extern struct struct_120 rtrips[25];

// addr: 192E:831E
// size: 506
extern struct struct_124 switches[23];

// addr: 192E:8518
// size: 40
extern struct struct_128 warps[10];

// addr: 192E:8540
// size: 2
extern int mode;

// addr: 192E:8542
// size: 6
extern int layer[3];

// addr: 192E:8548
// size: 5040
extern struct struct_153 wiznotes[10];

// addr: 192E:98F8
// size: 16
extern int sc_bounce[8];

// addr: 192E:9908
// size: 16
extern int sc_seek[8];

// addr: 192E:9918
// size: 16
extern int sc_yp[8];

// addr: 192E:9928
// size: 16
extern int sc_xp[8];

// addr: 192E:9938
// size: 16
extern int sc_spr[8];

// addr: 192E:9948
// size: 16
extern int sc_dir[8];

// addr: 192E:9958
// size: 16
extern int sc_yl[8];

// addr: 192E:9968
// size: 16
extern int sc_xw[8];

// addr: 192E:9978
// size: 16
extern int sc_y[8];

// addr: 192E:9988
// size: 16
extern int sc_x[8];

// addr: 192E:9998
// size: 16
extern int sc_life[8];

// addr: 192E:99A8
// size: 16
extern int sc_fend[8];

// addr: 192E:99B8
// size: 16
extern int sc_frm[8];

// addr: 192E:99C8
// size: 16
extern int sc_wobble[8];

// addr: 192E:99D8
// size: 16
extern int sc_pause[8];

// addr: 192E:99E8
// size: 16
extern int mc_ohits[8];

// addr: 192E:99F8
// size: 16
extern int mc_begin[8];

// addr: 192E:9A08
// size: 16
extern int mc_charge[8];

// addr: 192E:9A18
// size: 16
extern int mc_jump[8];

// addr: 192E:9A28
// size: 16
extern int mc_cnt[8];

// addr: 192E:9A38
// size: 16
extern int mc_speed[8];

// addr: 192E:9A48
// size: 16
extern int mc_type[8];

// addr: 192E:9A58
// size: 16
extern int mc_mnum[8];

// addr: 192E:9A68
// size: 16
extern int mc_snum[8];

// addr: 192E:9A78
// size: 16
extern int mc_org[8];

// addr: 192E:9A88
// size: 16
extern int mc_flash[8];

// addr: 192E:9A98
// size: 16
extern int mc_hits[8];

// addr: 192E:9AA8
// size: 16
extern int mc_frm[8];

// addr: 192E:9AB8
// size: 16
extern int mc_dir[8];

// addr: 192E:9AC8
// size: 16
extern int mc_yl[8];

// addr: 192E:9AD8
// size: 16
extern int mc_xw[8];

// addr: 192E:9AE8
// size: 16
extern int mc_mdly[8];

// addr: 192E:9AF8
// size: 16
extern int mc_yp[8];

// addr: 192E:9B08
// size: 16
extern int mc_xp[8];

// addr: 192E:9B18
// size: 16
extern int mc_y[8];

// addr: 192E:9B28
// size: 16
extern int mc_x[8];

// addr: 192E:9B38
// size: 16
extern int mc_sink[8];

// addr: 192E:9B48
// size: 16
extern int mc_vo[8];

// addr: 192E:9B58
// size: 16
extern int mc_stopshoot[8];

// addr: 192E:9B68
// size: 16
extern int mc_seek[8];

// addr: 192E:9B78
// size: 16
extern int mc_canshoot[8];

// addr: 192E:9B88
// size: 16
extern int mc_mustface[8];

// addr: 192E:9B98
// size: 16
extern int mc_shooting[8];

// addr: 192E:9BA8
// size: 64
extern int mr_offset[32];

// addr: 192E:9BE8
// size: 20
extern int sload[10];

// addr: 192E:9BFC
// size: 2
extern unsigned int sprbase;

// addr: 192E:9BFE
// size: 20
extern unsigned int sdatabase[10];

// addr: 192E:9C12
// size: 2200
extern struct struct_159 sprite[10];

// addr: 192E:A4AA
// size: 8
extern signed char expcnt[8];

// addr: 192E:A4B2
// size: 384
extern signed char expmisc[8][16][3];

// addr: 192E:A632
// size: 512
extern int exppos[8][16][2];

// addr: 192E:A832
// size: 2
extern int expnum;

// addr: 192E:A834
// size: 64
extern int twinkpos[8][4];

// addr: 192E:A874
// size: 2
extern int twinknum;

// addr: 192E:A876
// size: 100
extern int stag[10][5];

// addr: 192E:A8DA
// size: 2
extern int treasures;

// addr: 192E:A8DC
// size: 2
extern int treasuresfound;

// addr: 192E:A8DE
// size: 2
extern int monstershit;

// addr: 192E:A8E0
// size: 2
extern int monsters;

// addr: 192E:A8E2
// size: 2
extern int reddata;

// addr: 192E:A8E4
// size: 2
extern int whitedata;

// addr: 192E:A8E6
// size: 2
extern int ouchcnt;

// addr: 192E:A8E8
// size: 2
extern int switchcnt;

// addr: 192E:A8EA
// size: 2
extern int flash_flag;

// addr: 192E:A8EC
// size: 2
extern int scry;

// addr: 192E:A8EE
// size: 2
extern int scrxh;

// addr: 192E:A8F0
// size: 2
extern int scrmx;

// addr: 192E:A8F2
// size: 2
extern int scrx;

// addr: 192E:A8F4
// size: 2
extern int hgkey;

// addr: 192E:A8F6
// size: 2
extern int hskey;

// addr: 192E:A8F8
// size: 2
extern int holdshots;

// addr: 192E:A8FA
// size: 2
extern int hsupershot;

// addr: 192E:A8FC
// size: 2
extern int hdone;

// addr: 192E:A8FE
// size: 2
extern int hdead;

// addr: 192E:A900
// size: 2
extern int hinvis;

// addr: 192E:A902
// size: 2
extern int hdir;

// addr: 192E:A904
// size: 2
extern int hfrm;

// addr: 192E:A906
// size: 2
extern int hlaser;

// addr: 192E:A908
// size: 2
extern int hlaserdisplaycnt;

// addr: 192E:A90A
// size: 2
extern int hlaserdisplay;

// addr: 192E:A90C
// size: 10
extern int hfirelaser[5];

// addr: 192E:A916
// size: 2
extern int hfireaway;

// addr: 192E:A918
// size: 2
extern int hfirenum;

// addr: 192E:A91A
// size: 10
extern int hfired[5];

// addr: 192E:A924
// size: 10
extern int hfireup[5];

// addr: 192E:A92E
// size: 10
extern int hfirey[5];

// addr: 192E:A938
// size: 10
extern int hfirex[5];

// addr: 192E:A942
// size: 2
extern int hwarpdx;

// addr: 192E:A944
// size: 2
extern int hwarpdy;

// addr: 192E:A946
// size: 2
extern int hinwarp;

// addr: 192E:A948
// size: 2
extern int hfall;

// addr: 192E:A94A
// size: 2
extern int hstopjump;

// addr: 192E:A94C
// size: 2
extern int hjump;

// addr: 192E:A94E
// size: 2
extern int htwinkletoes;

// addr: 192E:A950
// size: 2
extern int hjumphigh;

// addr: 192E:A952
// size: 2
extern int hjumpposlimit;

// addr: 192E:A954
// size: 2
extern int hjumpposmid;

// addr: 192E:A956
// size: 2
extern int hjumppos;

// addr: 192E:A958
// size: 4
extern int *hjumpadd;

// addr: 192E:A95C
// size: 2
extern int hwalking;

// addr: 192E:A95E
// size: 2
extern int hwuright;

// addr: 192E:A960
// size: 2
extern int hwuleft;

// addr: 192E:A962
// size: 2
extern int hmright;

// addr: 192E:A964
// size: 2
extern int hmleft;

// addr: 192E:A966
// size: 2
extern int hylspos;

// addr: 192E:A968
// size: 2
extern int hylpos;

// addr: 192E:A96A
// size: 2
extern int hxbspos;

// addr: 192E:A96C
// size: 2
extern int hxbpos;

// addr: 192E:A96E
// size: 2
extern int hypos;

// addr: 192E:A970
// size: 2
extern int hxmpos;

// addr: 192E:A972
// size: 2
extern int hxpos;

// addr: 192E:A974
// size: 2
extern int scrolldelay;

// addr: 192E:A976
// size: 2
extern int ylevel;

// addr: 192E:A978
// size: 2
extern int snapcoords;

// addr: 192E:A97A
// size: 2
extern int playlevel;

// addr: 192E:A97C
// size: 2
extern int demolimit;

// addr: 192E:A97E
// size: 2
extern int demonum;

// addr: 192E:A980
// size: 6
extern struct struct_172 demo;

// addr: 192E:A986
// size: 2
extern int b4p;

// addr: 192E:A988
// size: 1
extern unsigned char conup;

// addr: 192E:A989
// size: 1
extern unsigned char conshoot;

// addr: 192E:A98A
// size: 2
extern int relevator;

// addr: 192E:A98C
// size: 2
extern int lelevator;

// addr: 192E:A98E
// size: 2
extern int uppressed;

#endif