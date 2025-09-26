#ifndef __DEFS_H__
#define __DEFS_H__

// SCREEN
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

// VGA
#define VGA_PLANE_SHIFT 2
#define VGA_PLANE_COUNT (1 << VGA_PLANE_SHIFT)
#define VGA_PAGE_COUNT 4
#define VGA_PLANE_WIDTH (SCREEN_WIDTH / VGA_PLANE_COUNT)
#define VGA_PAGE_SIZE (VGA_PLANE_WIDTH * SCREEN_HEIGHT)

// FNC
#define FNC_UPS_START 0
#define FNC_UPS_RUBY 0
#define FNC_UPS_DIAMOND 1
#define FNC_UPS_GOBLET 2
#define FNC_UPS_CROWN 3
#define FNC_UPS_HEAL 4
#define FNC_UPS_CRYSTAL 5
#define FNC_UPS_HURT 6
#define FNC_UPS_ADD_SHOT 7
#define FNC_UPS_INVISIBLE 8
#define FNC_UPS_SUPER_JUMP 9
#define FNC_UPS_SUPER_SHOT 10
#define FNC_UPS_SMART_BOMB 11
#define FNC_UPS_SILVER_KEY 12
#define FNC_UPS_GOLD_KEY 13
#define FNC_UPS_KILL 14
#define FNC_UPS_WIZARD_NOTE 15
#define FNC_UPS_LASER_SHOT 16
#define FNC_UPS_END 22
#define FNC_WARPS_START 23
#define FNC_WARPS_END 32
#define FNC_SWITCHES_START 33
#define FNC_SWITCHES_END 55
#define FNC_RTRIPS_START 56
#define FNC_RTRIPS_END 80
#define FNC_ETRIPS_START 81
#define FNC_ETRIPS_END 105
#define FNC_SPRITES_START 106
#define FNC_SPRITES_END 115
#define FNC_MTRIGGERS_START 116
#define FNC_MTRIGGERS_END 365
#define FNC_NONE 30000

// COUNTS
#define UPS_COUNT (FNC_UPS_END - FNC_UPS_START + 1)
#define WARPS_COUNT (FNC_WARPS_END - FNC_WARPS_START + 1)
#define SWITCHES_COUNT (FNC_SWITCHES_END - FNC_SWITCHES_START + 1)
#define RTRIPS_COUNT (FNC_RTRIPS_END - FNC_RTRIPS_START + 1)
#define ETRIPS_COUNT (FNC_ETRIPS_END - FNC_ETRIPS_START + 1)
#define SPRITES_COUNT (FNC_SPRITES_END - FNC_SPRITES_START + 1)
#define MTRIGGERS_COUNT (FNC_MTRIGGERS_END - FNC_MTRIGGERS_START + 1)
#define MTAGS_COUNT SPRITES_COUNT
#define GAME_COUNT 4
#define LEVEL_COUNT 9
#define STORY_COUNT 10
#define DEMO_COUNT 5

#if PROTO
#define CREDIT_COUNT 8
#define PREVIEW_COUNT 10
#define ORDER_COUNT 22
#define SOUND_COUNT 12
#else
#define CREDIT_COUNT 2
#define PREVIEW_COUNT 11
#define ORDER_COUNT 10
#define SOUND_COUNT 16
#endif

#if FINAL
#define HELP_COUNT 5
#else
#define HELP_COUNT 4
#endif

#if DEMO || PROTO
#define EPISODE_COUNT 1
#define MUSIC_COUNT 11
#else
#define EPISODE_COUNT 4
#define MUSIC_COUNT 12
#endif

// DB
#define DB_FONT 0

#if PROTO
#define DB_CONFIG (DB_FONT + 1)
#define DB_APOGEE (DB_CONFIG + 1)
#define DB_TITLE (DB_APOGEE + 1)
#define DB_WARP (DB_TITLE + 1)
#elif DEMO
#define DB_APOGEE (DB_FONT + 1)
#define DB_TITLE (DB_APOGEE + 1)
#define DB_WARP (DB_TITLE + 1)
#else
#define DB_APOGEE (DB_FONT + 1)
#define DB_TITLE (DB_APOGEE + 1)
#define DB_REGIST (DB_TITLE + 1)
#define DB_WARP (DB_REGIST + 1)
#endif

#define DB_SINCOS (DB_WARP + 1)
#define DB_RANDOM (DB_SINCOS + 1)
#define DB_GAMEPAL (DB_RANDOM + 1)
#define DB_MENUPAL (DB_GAMEPAL + 1)
#define DB_BOTTOM (DB_MENUPAL + 1)
#define DB_HOCUS (DB_BOTTOM + 1)
#define DB_HUDSTUFF (DB_HOCUS + 1)
#define DB_NEW_HUD (DB_HUDSTUFF + 1)
#define DB_OLD_HUD (DB_NEW_HUD + 1)
#define DB_BULLIT (DB_OLD_HUD + 1)

#if PROTO
#define DB_DEMO (DB_BULLIT + 1)
#elif DEMO
#define DB_VOL_BAR (DB_BULLIT + 1)
#define DB_CRYSTAL (DB_VOL_BAR + 1)
#define DB_DEMO (DB_CRYSTAL + 1)
#else
#define DB_VOL_BAR (DB_BULLIT + 1)
#define DB_CRYSTAL (DB_VOL_BAR + 1)
#define DB_PIRACY (DB_CRYSTAL + 1)
#define DB_DEMO (DB_PIRACY + 1)
#endif

#define DB_CREDIT (DB_DEMO + DEMO_COUNT)
#define DB_HELP (DB_CREDIT + CREDIT_COUNT)
#define DB_PREVIEW (DB_HELP + HELP_COUNT)
#define DB_ORDER (DB_PREVIEW + PREVIEW_COUNT)
#define DB_REGISTER (DB_ORDER + ORDER_COUNT)

#if PROTO
#define DB_BACKPAL (DB_REGISTER + 1)
#elif DEMO
#define DB_STORY (DB_REGISTER + 1)
#define DB_E1END (DB_STORY + STORY_COUNT)
#define DB_BACKPAL (DB_E1END + 2)
#else
#define DB_STORY (DB_REGISTER + 1)
#define DB_E1END (DB_STORY + STORY_COUNT)
#define DB_E2END (DB_E1END + 2)
#define DB_E3END (DB_E2END + 2)
#define DB_E4END (DB_E3END + 4)
#define DB_KISS (DB_E4END + 2)
#define DB_BACKPAL (DB_KISS + 1)
#endif

#define DB_BACKPCX (DB_BACKPAL + (4 * EPISODE_COUNT))
#define DB_TILE (DB_BACKPCX + (4 * EPISODE_COUNT))

#if PROTO
#define DB_WIN (DB_TILE + (4 * EPISODE_COUNT))
#define DB_SPRITES (DB_WIN + 1)
#else
#define DB_PIC1 (DB_TILE + (4 * EPISODE_COUNT))
#define DB_WIN (DB_PIC1 + 1)
#define DB_PIC2 (DB_WIN + 1)
#define DB_PIC3 (DB_PIC2 + 1)
#define DB_PIC4 (DB_PIC3 + 1)
#define DB_PIC5 (DB_PIC4 + 1)
#define DB_PIC6 (DB_PIC5 + 1)
#define DB_PIC7 (DB_PIC6 + 1)
#define DB_PIC8 (DB_PIC7 + 1)
#define DB_SPRITES (DB_PIC8 + 1)
#endif

#define DB_LVLINFO (DB_SPRITES + 1)
#define DB_ANMINFO (DB_LVLINFO + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_WIZNOTES (DB_ANMINFO + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_WARPS (DB_WIZNOTES + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_SWITCHES (DB_WARPS + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_RTRIPS (DB_SWITCHES + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_ETRIPS (DB_RTRIPS + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_MTAGS (DB_ETRIPS + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_MTRIGGERS (DB_MTAGS + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_BKG (DB_MTRIGGERS + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_SLD (DB_BKG + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_SLDSAV (DB_SLD + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_FNC (DB_SLDSAV + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_MUSIC (DB_FNC + (LEVEL_COUNT * EPISODE_COUNT))
#define DB_MUSIC_FANFARE (DB_MUSIC + 0)
#define DB_MUSIC_TITLE (DB_MUSIC + 3)
#define DB_SOUND (DB_MUSIC + MUSIC_COUNT)

#if PROTO
#define DB_SOUND1 (DB_SOUND + 0)
#define DB_SOUND2 (DB_SOUND1 + 2)
#define DB_SOUND3 (DB_SOUND2 + 1)
#define DB_SOUND4 (DB_SOUND3 + 1)
#define DB_SOUND5 (DB_SOUND4 + 1)
#define DB_SOUND6 (DB_SOUND5 + 1)
#define DB_SOUND7 (DB_SOUND6 + 2)
#define DB_SOUND8 (DB_SOUND7 + 2)
#define DB_SOUND9 (DB_SOUND8 + 2)
#define DB_SOUND10 (DB_SOUND9 + 2)
#define DB_SOUND11 (DB_SOUND10 + 2)
#define DB_SOUND12 (DB_SOUND11 + 2)
#define DB_SOUND13 (DB_SOUND12 + 2)
#define DB_SOUND14 (DB_SOUND13 + 2)
#define DB_SOUND15 (DB_SOUND14 + 2)
#define DB_SOUND16 (DB_SOUND15 + 2)
#define DB_DOSMSG (DB_SOUND16 + 2)
#define DB_COUNT (DB_DOSMSG + 1)
#else
#define DB_SOUND1 (DB_SOUND + 0)
#define DB_SOUND2 (DB_SOUND1 + 1)
#define DB_SOUND3 (DB_SOUND2 + 2)
#define DB_SOUND4 (DB_SOUND3 + 1)
#define DB_SOUND5 (DB_SOUND4 + 1)
#define DB_SOUND6 (DB_SOUND5 + 1)
#define DB_SOUND7 (DB_SOUND6 + 1)
#define DB_SOUND8 (DB_SOUND7 + 2)
#define DB_SOUND9 (DB_SOUND8 + 2)
#define DB_SOUND10 (DB_SOUND9 + 2)
#define DB_SOUND11 (DB_SOUND10 + 2)
#define DB_SOUND12 (DB_SOUND11 + 2)
#define DB_SOUND13 (DB_SOUND12 + 2)
#define DB_SOUND14 (DB_SOUND13 + 2)
#define DB_SOUND15 (DB_SOUND14 + 2)
#define DB_SOUND16 (DB_SOUND15 + 2)
#define DB_SOUND17 (DB_SOUND16 + 2)
#define DB_SOUND18 (DB_SOUND17 + 2)
#define DB_SOUND19 (DB_SOUND18 + 2)
#define DB_SOUND20 (DB_SOUND19 + 2)
#define DB_SOUND21 (DB_SOUND20 + 2)
#define DB_SOUND22 (DB_SOUND21 + 2)
#define DB_DOSSHARE (DB_SOUND22 + 2)
#define DB_DOSREG (DB_DOSSHARE + 1)
#define DB_COUNT (DB_DOSREG + 1)
#endif

// SIZE
#if PROTO
#define SPR_CODE_SIZE 9126
#else
#define SPR_CODE_SIZE 9939
#endif

// KEYS
#define KEY_RETURN 13
#define KEY_ESCAPE 27
#define KEY_SPACE 32
#define KEY_ALT_W 17
#define KEY_ALT_E 18
#define KEY_ALT_R 19
#define KEY_ALT_T 20
#define KEY_ALT_U 22
#define KEY_ALT_S 31
#define KEY_ALT_Z 44
#define KEY_ALT_B 48
#define KEY_ALT_M 50
#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10 68
#define KEY_HOME 71
#define KEY_UP 72
#define KEY_PGUP 73
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_END 79
#define KEY_DOWN 80
#define KEY_PGDN 81
#define KEY_INSERT 82
#define KEY_DELETE 83

#endif