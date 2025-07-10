#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#ifdef __GLOBALS_C__
#define EXTERN
#else
#define EXTERN extern
#endif

// addr: 192E:A98E
// size: 2
EXTERN int uppressed;

// addr: 192E:A98C
// size: 2
EXTERN int lelevator;

// addr: 192E:A98A
// size: 2
EXTERN int relevator;

// addr: 192E:A989
// size: 1
EXTERN unsigned char conshoot;

// addr: 192E:A988
// size: 1
EXTERN unsigned char conup;

// addr: 192E:A986
// size: 2
EXTERN int b4p;

// addr: 192E:A980
// size: 6
EXTERN struct_172 demo;

// addr: 192E:A97E
// size: 2
EXTERN int demonum;

// addr: 192E:A97C
// size: 2
EXTERN int demolimit;

// addr: 192E:A97A
// size: 2
EXTERN int playlevel;

// addr: 192E:A978
// size: 2
EXTERN int snapcoords;

// addr: 192E:A976
// size: 2
EXTERN int ylevel;

// addr: 192E:A974
// size: 2
EXTERN int scrolldelay;

// addr: 192E:A972
// size: 2
EXTERN int hxpos;

// addr: 192E:A970
// size: 2
EXTERN int hxmpos;

// addr: 192E:A96E
// size: 2
EXTERN int hypos;

// addr: 192E:A96C
// size: 2
EXTERN int hxbpos;

// addr: 192E:A96A
// size: 2
EXTERN int hxbspos;

// addr: 192E:A968
// size: 2
EXTERN int hylpos;

// addr: 192E:A966
// size: 2
EXTERN int hylspos;

// addr: 192E:A964
// size: 2
EXTERN int hmleft;

// addr: 192E:A962
// size: 2
EXTERN int hmright;

// addr: 192E:A960
// size: 2
EXTERN int hwuleft;

// addr: 192E:A95E
// size: 2
EXTERN int hwuright;

// addr: 192E:A95C
// size: 2
EXTERN int hwalking;

// addr: 192E:A958
// size: 4
EXTERN int *hjumpadd;

// addr: 192E:A956
// size: 2
EXTERN int hjumppos;

// addr: 192E:A954
// size: 2
EXTERN int hjumpposmid;

// addr: 192E:A952
// size: 2
EXTERN int hjumpposlimit;

// addr: 192E:A950
// size: 2
EXTERN int hjumphigh;

// addr: 192E:A94E
// size: 2
EXTERN int htwinkletoes;

// addr: 192E:A94C
// size: 2
EXTERN int hjump;

// addr: 192E:A94A
// size: 2
EXTERN int hstopjump;

// addr: 192E:A948
// size: 2
EXTERN int hfall;

// addr: 192E:A946
// size: 2
EXTERN int hinwarp;

// addr: 192E:A944
// size: 2
EXTERN int hwarpdy;

// addr: 192E:A942
// size: 2
EXTERN int hwarpdx;

// addr: 192E:A938
// size: 10
EXTERN int hfirex[5];

// addr: 192E:A92E
// size: 10
EXTERN int hfirey[5];

// addr: 192E:A924
// size: 10
EXTERN int hfireup[5];

// addr: 192E:A91A
// size: 10
EXTERN int hfired[5];

// addr: 192E:A918
// size: 2
EXTERN int hfirenum;

// addr: 192E:A916
// size: 2
EXTERN int hfireaway;

// addr: 192E:A90C
// size: 10
EXTERN int hfirelaser[5];

// addr: 192E:A90A
// size: 2
EXTERN int hlaserdisplay;

// addr: 192E:A908
// size: 2
EXTERN int hlaserdisplaycnt;

// addr: 192E:A906
// size: 2
EXTERN int hlaser;

// addr: 192E:A904
// size: 2
EXTERN int hfrm;

// addr: 192E:A902
// size: 2
EXTERN int hdir;

// addr: 192E:A900
// size: 2
EXTERN int hinvis;

// addr: 192E:A8FE
// size: 2
EXTERN int hdead;

// addr: 192E:A8FC
// size: 2
EXTERN int hdone;

// addr: 192E:A8FA
// size: 2
EXTERN int hsupershot;

// addr: 192E:A8F8
// size: 2
EXTERN int holdshots;

// addr: 192E:A8F6
// size: 2
EXTERN int hskey;

// addr: 192E:A8F4
// size: 2
EXTERN int hgkey;

// addr: 192E:A8F2
// size: 2
EXTERN int scrx;

// addr: 192E:A8F0
// size: 2
EXTERN int scrmx;

// addr: 192E:A8EE
// size: 2
EXTERN int scrxh;

// addr: 192E:A8EC
// size: 2
EXTERN int scry;

// addr: 192E:A8EA
// size: 2
EXTERN int flash_flag;

// addr: 192E:A8E8
// size: 2
EXTERN int switchcnt;

// addr: 192E:A8E6
// size: 2
EXTERN int ouchcnt;

// addr: 192E:A8E4
// size: 2
EXTERN int whitedata;

// addr: 192E:A8E2
// size: 2
EXTERN int reddata;

// addr: 192E:A8E0
// size: 2
EXTERN int monsters;

// addr: 192E:A8DE
// size: 2
EXTERN int monstershit;

// addr: 192E:A8DC
// size: 2
EXTERN int treasuresfound;

// addr: 192E:A8DA
// size: 2
EXTERN int treasures;

// addr: 192E:A876
// size: 100
EXTERN int stag[10][5];

// addr: 192E:A874
// size: 2
EXTERN int twinknum;

// addr: 192E:A834
// size: 64
EXTERN int twinkpos[8][4];

// addr: 192E:A832
// size: 2
EXTERN int expnum;

// addr: 192E:A632
// size: 512
EXTERN int exppos[8][16][2];

// addr: 192E:A4B2
// size: 384
EXTERN signed char expmisc[8][16][3];

// addr: 192E:A4AA
// size: 8
EXTERN signed char expcnt[8];

// addr: 192E:9C12
// size: 2200
EXTERN sprite_t sprite[SPRITES_COUNT];

// addr: 192E:9BFE
// size: 20
EXTERN unsigned int sdatabase[10];

// addr: 192E:9BFC
// size: 2
EXTERN unsigned int sprbase;

// addr: 192E:9BE8
// size: 20
EXTERN int sload[10];

// addr: 192E:9BA8
// size: 64
EXTERN int mr_offset[32];

// addr: 192E:9B98
// size: 16
EXTERN int mc_shooting[8];

// addr: 192E:9B88
// size: 16
EXTERN int mc_mustface[8];

// addr: 192E:9B78
// size: 16
EXTERN int mc_canshoot[8];

// addr: 192E:9B68
// size: 16
EXTERN int mc_seek[8];

// addr: 192E:9B58
// size: 16
EXTERN int mc_stopshoot[8];

// addr: 192E:9B48
// size: 16
EXTERN int mc_vo[8];

// addr: 192E:9B38
// size: 16
EXTERN int mc_sink[8];

// addr: 192E:9B28
// size: 16
EXTERN int mc_x[8];

// addr: 192E:9B18
// size: 16
EXTERN int mc_y[8];

// addr: 192E:9B08
// size: 16
EXTERN int mc_xp[8];

// addr: 192E:9AF8
// size: 16
EXTERN int mc_yp[8];

// addr: 192E:9AE8
// size: 16
EXTERN int mc_mdly[8];

// addr: 192E:9AD8
// size: 16
EXTERN int mc_xw[8];

// addr: 192E:9AC8
// size: 16
EXTERN int mc_yl[8];

// addr: 192E:9AB8
// size: 16
EXTERN int mc_dir[8];

// addr: 192E:9AA8
// size: 16
EXTERN int mc_frm[8];

// addr: 192E:9A98
// size: 16
EXTERN int mc_hits[8];

// addr: 192E:9A88
// size: 16
EXTERN int mc_flash[8];

// addr: 192E:9A78
// size: 16
EXTERN int mc_org[8];

// addr: 192E:9A68
// size: 16
EXTERN int mc_snum[8];

// addr: 192E:9A58
// size: 16
EXTERN int mc_mnum[8];

// addr: 192E:9A48
// size: 16
EXTERN int mc_type[8];

// addr: 192E:9A38
// size: 16
EXTERN int mc_speed[8];

// addr: 192E:9A28
// size: 16
EXTERN int mc_cnt[8];

// addr: 192E:9A18
// size: 16
EXTERN int mc_jump[8];

// addr: 192E:9A08
// size: 16
EXTERN int mc_charge[8];

// addr: 192E:99F8
// size: 16
EXTERN int mc_begin[8];

// addr: 192E:99E8
// size: 16
EXTERN int mc_ohits[8];

// addr: 192E:99D8
// size: 16
EXTERN int sc_pause[8];

// addr: 192E:99C8
// size: 16
EXTERN int sc_wobble[8];

// addr: 192E:99B8
// size: 16
EXTERN int sc_frm[8];

// addr: 192E:99A8
// size: 16
EXTERN int sc_fend[8];

// addr: 192E:9998
// size: 16
EXTERN int sc_life[8];

// addr: 192E:9988
// size: 16
EXTERN int sc_x[8];

// addr: 192E:9978
// size: 16
EXTERN int sc_y[8];

// addr: 192E:9968
// size: 16
EXTERN int sc_xw[8];

// addr: 192E:9958
// size: 16
EXTERN int sc_yl[8];

// addr: 192E:9948
// size: 16
EXTERN int sc_dir[8];

// addr: 192E:9938
// size: 16
EXTERN int sc_spr[8];

// addr: 192E:9928
// size: 16
EXTERN int sc_xp[8];

// addr: 192E:9918
// size: 16
EXTERN int sc_yp[8];

// addr: 192E:9908
// size: 16
EXTERN int sc_seek[8];

// addr: 192E:98F8
// size: 16
EXTERN int sc_bounce[8];

// addr: 192E:8548
// size: 5040
EXTERN wiznote_t wiznotes[10];

// addr: 192E:8542
// size: 6
EXTERN int layer[3];

// addr: 192E:8540
// size: 2
EXTERN int mode;

// addr: 192E:8518
// size: 40
EXTERN warp_t warps[WARPS_COUNT];

// addr: 192E:831E
// size: 506
EXTERN switch_t switches[SWITCHES_COUNT];

// addr: 192E:81F2
// size: 300
EXTERN trip_t rtrips[RTRIPS_COUNT];

// addr: 192E:80C6
// size: 300
EXTERN trip_t etrips[ETRIPS_COUNT];

// addr: 192E:7FD6
// size: 240
EXTERN tag_t mtags[MTAGS_COUNT];

// addr: 192E:6096
// size: 8000
EXTERN trigger_t mtriggers[MTRIGGERS_COUNT];

// addr: 192E:6094
// size: 2
EXTERN int dlevel;

// addr: 192E:6092
// size: 2
EXTERN int dx;

// addr: 192E:6090
// size: 2
EXTERN int dy;

// addr: 192E:608E
// size: 2
EXTERN int sdx;

// addr: 192E:608C
// size: 2
EXTERN int sdy;

// addr: 192E:608A
// size: 2
EXTERN int mofs;

// addr: 192E:6088
// size: 2
EXTERN int palette_pnt;

// addr: 192E:6086
// size: 2
EXTERN int blx;

// addr: 192E:6084
// size: 2
EXTERN int brx;

// addr: 192E:6082
// size: 2
EXTERN int bty;

// addr: 192E:6080
// size: 2
EXTERN int bby;

// addr: 192E:607E
// size: 2
EXTERN int block;

// addr: 192E:5D7E
// size: 768
EXTERN unsigned char savepalette[768];

// addr: 192E:5D7C
// size: 2
EXTERN int iconx;

// addr: 192E:5D54
// size: 40
EXTERN int icony[20];

// addr: 192E:5D52
// size: 2
EXTERN int iconpos;

// addr: 192E:5D50
// size: 2
EXTERN int iconmax;

// addr: 192E:5D4E
// size: 2
EXTERN int gmenunum;

// addr: 192E:56B8
// size: 1686
EXTERN inf_t inf;

// addr: 192E:5690
// size: 40
EXTERN unsigned char *menu_item_labels[10];

// addr: 192E:568E
// size: 2
EXTERN int menu_item_num;

// addr: 192E:568C
// size: 2
EXTERN int menu_footer;

// addr: 192E:568A
// size: 2
EXTERN int menu_first_title;

// addr: 192E:5688
// size: 2
EXTERN int playmenuip;

// addr: 192E:5684
// size: 4
EXTERN int *textbase;

// addr: 192E:55EE
// size: 150
EXTERN int star_deg[75];

// addr: 192E:5558
// size: 150
EXTERN int star_rad[75];

// addr: 192E:550C
// size: 75
EXTERN unsigned char star_radplus[75];

// addr: 192E:54C1
// size: 75
EXTERN unsigned char star_clrcnt[75];

// addr: 192E:5476
// size: 75
EXTERN unsigned char star_clrplus[75];

// addr: 192E:53F6
// size: 128
EXTERN PCXHEAD header;

// addr: 192E:53F4
// size: 2
EXTERN unsigned int width;

// addr: 192E:53F2
// size: 2
EXTERN unsigned int depth;

// addr: 192E:53F0
// size: 2
EXTERN unsigned int bytes;

// addr: 192E:53EE
// size: 2
EXTERN int indemo;

// addr: 192E:53EA
// size: 4
EXTERN long clk_times;

// addr: 192E:53E6
// size: 4
EXTERN long total_ticks;

// addr: 192E:53E2
// size: 4
EXTERN long musiclooped;

// addr: 192E:4C12
// size: 2000
EXTERN int16_t rnd[1000];

// addr: 192E:4C10
// size: 2
EXTERN int rndnum;

// addr: 192E:4BBF
// size: 81
EXTERN unsigned char dline[81];

// addr: 192E:4BAA
// size: 21
EXTERN unsigned char dumnum[21];

// addr: 192E:4BA9
// size: 1
EXTERN unsigned char skiptitle;

// addr: 192E:4BA8
// size: 1
EXTERN unsigned char cukey;

// addr: 192E:4BA7
// size: 1
EXTERN unsigned char ukey;

// addr: 192E:4BA6
// size: 1
EXTERN unsigned char dkey;

// addr: 192E:4BA5
// size: 1
EXTERN unsigned char lkey;

// addr: 192E:4BA4
// size: 1
EXTERN unsigned char rkey;

// addr: 192E:4BA3
// size: 1
EXTERN unsigned char fkey;

// addr: 192E:4BA2
// size: 1
EXTERN unsigned char jkey;

// addr: 192E:4BA1
// size: 1
EXTERN unsigned char qkey;

// addr: 192E:4BA0
// size: 1
EXTERN unsigned char ukeyclr;

// addr: 192E:4B9F
// size: 1
EXTERN unsigned char jkeyclr;

// addr: 192E:4B9E
// size: 1
EXTERN unsigned char fkeyclr;

// addr: 192E:4B9D
// size: 1
EXTERN unsigned char pgupkey;

// addr: 192E:4B9C
// size: 1
EXTERN unsigned char pgdnkey;

// addr: 192E:4B9B
// size: 1
EXTERN unsigned char f2key;

// addr: 192E:4B9A
// size: 1
EXTERN unsigned char f3key;

// addr: 192E:4B99
// size: 1
EXTERN unsigned char f10key;

// addr: 192E:4B98
// size: 1
EXTERN unsigned char helpkey;

// addr: 192E:4B97
// size: 1
EXTERN unsigned char calkey;

// addr: 192E:4B96
// size: 1
EXTERN unsigned char muskey;

// addr: 192E:4B95
// size: 1
EXTERN unsigned char sndkey;

// addr: 192E:4B94
// size: 1
EXTERN unsigned char anykey;

// addr: 192E:4B93
// size: 1
EXTERN unsigned char gkey;

// addr: 192E:4B92
// size: 1
EXTERN unsigned char pause;

// addr: 192E:4B6A
// size: 40
EXTERN unsigned char *spr_code[10];

// addr: 192E:4B68
// size: 2
EXTERN int game;

// addr: 192E:4B66
// size: 2
EXTERN int level;

// addr: 192E:4B64
// size: 2
EXTERN int skill;

// addr: 192E:4B60
// size: 4
EXTERN unsigned char *bkg;

// addr: 192E:4B5C
// size: 4
EXTERN unsigned char *sld;

// addr: 192E:4B58
// size: 4
EXTERN unsigned char *sldsav;

// addr: 192E:4B54
// size: 4
EXTERN int16_t *fnc;

// addr: 192E:4B50
// size: 4
EXTERN unsigned char *swe;

// addr: 192E:4B4C
// size: 4
EXTERN long score;

// addr: 192E:4B48
// size: 4
EXTERN long oldscore;

// addr: 192E:4B46
// size: 2
EXTERN int health;

// addr: 192E:4B44
// size: 2
EXTERN int crystals;

// addr: 192E:4B42
// size: 2
EXTERN int crystals_found;

// addr: 192E:4B40
// size: 2
EXTERN int hfirepower;

// addr: 192E:4B3E
// size: 2
EXTERN int oldhfirepower;

// addr: 192E:4B36
// size: 8
EXTERN lvlinfo_t lvlinfo;

// addr: 192E:4862
// size: 724
EXTERN anminfo_t anminfo;

// addr: 192E:485E
// size: 4
EXTERN FILE *databasefp;

// addr: 192E:455E
// size: 768
EXTERN unsigned char palette[768];

// addr: 192E:425E
// size: 768
EXTERN unsigned char tpal[768];

// addr: 192E:3F5E
// size: 768
EXTERN unsigned char temppal[768];

// addr: 192E:3F5A
// size: 4
EXTERN unsigned char *vga;

// addr: 192E:3F4A
// size: 16
EXTERN unsigned char *vgap[VGA_PAGE_COUNT];

// addr: 192E:3F42
// size: 8
EXTERN unsigned int vgapofs[VGA_PAGE_COUNT];

// addr: 192E:3F40
// size: 2
EXTERN int apg;

// addr: 192E:3F3E
// size: 2
EXTERN int vpg;

// addr: 192E:3F3A
// size: 4
EXTERN unsigned char *font;

// addr: 192E:3F38
// size: 2
EXTERN int adlib;

// addr: 192E:3F36
// size: 2
EXTERN int blaster;

// addr: 192E:3F34
// size: 2
EXTERN int noblaster;

// addr: 192E:3F32
// size: 2
EXTERN int nocard;

// addr: 192E:3F2E
// size: 4
EXTERN int16_t *imf_music;

// addr: 192E:3F2C
// size: 2
EXTERN int current_sound_priority;

// addr: 192E:3EFC
// size: 48
EXTERN unsigned char *sfx_mem[12];

// addr: 192E:3ECC
// size: 48
EXTERN int16_t *pcs_mem[12];

// addr: 192E:3ECA
// size: 2
EXTERN int pcs_sample;

// addr: 192E:3EC8
// size: 2
EXTERN int pcs_sample_pnt;

// addr: 192E:3EC6
// size: 2
EXTERN int pcs_sampleplaying;

// addr: 192E:3E96
// size: 48
EXTERN long pcs_sample_length[12];

// addr: 192E:3E92
// size: 4
EXTERN grphdr_t grphdr;

// addr: 192E:3352
// size: 2880
EXTERN float sine_cosine_table[360][2];

// addr: 192E:2812
// size: 2880
EXTERN long l_sine_cosine_table[360][2];

// addr: 192E:2456
// size: 956
EXTERN config_t game_config;

// addr: 192E:2452
// size: 4
EXTERN unsigned char *buf64;

#endif