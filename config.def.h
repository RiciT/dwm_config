/* See LICENSE file for copyright and license details. */

/* alt-tab configuration */
static const unsigned int tabModKey =
    0x40; /* if this key is hold the alt-tab functionality stays acitve. This
             key must be the same as key that is used to active functin
             altTabStart `*/
static const unsigned int tabCycleKey =
    0x17; /* if this key is hit the alt-tab program moves one position forward
             in clients stack. This key must be the same as key that is used to
             active functin altTabStart */
static const unsigned int tabCycleKey2 = 0x31; /* grave key */
static const unsigned int tabPosY =
    1; /* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX =
    1; /* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab = 600; /* tab menu width */
static const unsigned int maxHTab = 200; /* tab menu height */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int gappx = 0;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappih = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv = 10;  /* vert inner gap between windows */
static const unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    10; /* vert outer gap between windows and screen edge */
static int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int showbar = 1;               /* 0 means no bar */
static const int topbar = 1;                /* 0 means bottom bar */
static const int usealtbar = 1;             /* 1 means use non-dwm status bar */
static const char *altbarclass = "Polybar"; /* Alternate bar class name */
static const char *alttrayname = "tray";    /* Polybar tray instance name */
static const char *altbarcmd =
    "~/.config/polybar/launch_dwm.sh"; /* Polybar launch command */
static char font[] = "Aptos:size=10";
static char dmenufont[] = "JetBrainsMono-Bold:size=10";
static const char *fonts[] = {font};

#include "/home/br4mos/.cache/wal/colors-wal-dwm-minimal.h"
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

static char dmenulines[] = "8";
static char *colorsdark[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
    [SchemeSel] = {sel_fg, sel_bg, sel_border},
};
static char *colorslight[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
    [SchemeSel] = {sel_fg, sel_bg, sel_border},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating  canfocus
       monitor */
    {"Gimp", NULL, NULL, 0, 1, 1, -1},
    {"Conky", NULL, NULL, 0, 1, 0, -1},
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int decorhints = 1; /* 1 means respect decor hints */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate =
    120; /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const float fgw = .6, fgh = .6;

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[@]", spiral}, {"[\\]", dwindle}, {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
/* Dmenu commands */
static char dmenumon[2] =
    "0"; /* component of dmenu{dark,light}, manipulated in spawndmenu() */
static const char *dmenudark[] = {"dmenu_run", "-m",  dmenumon,    "-fn",
                                  dmenufont,   "-nb", normbgcolor, "-nf",
                                  normfgcolor, "-sb", selbgcolor,  "-sf",
                                  selfgcolor,  "-l",  dmenulines,  NULL};
static const char *dmenulight[] = {
    "j4-wrapper", "-m",  dmenumon,    "-fn", dmenufont,  "-nb",
    normbgcolor,  "-nf", normfgcolor, "-sb", selbgcolor, "-sf",
    selfgcolor,   "-l",  dmenulines,  "-i",  NULL};

static const char *clipcmd[] = {
    "clipmenu",  "-m",  dmenumon,    "-fn", dmenufont,  "-nb",
    normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf",
    selfgcolor,  "-l",  dmenulines,  "-i",  NULL};

static const char *powermenucmd[] = {
    "powermenu", "-m",  dmenumon,    "-fn", dmenufont,  "-nb",
    normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf",
    selfgcolor,  "-l",  dmenulines,  "-i",  NULL};

/* Terminal command */
static const char *termcmd[] = {"terminator", NULL};

/* Brightness and Volume commands */
static const char *brightnessup[] = {"/home/br4mos/.dwm/backlight.sh", "up",
                                     NULL};
static const char *brightnessdown[] = {"/home/br4mos/.dwm/backlight.sh", "down",
                                       NULL};

static const char *volup[] = {"/home/br4mos/.dwm/volume.sh", "up", NULL};
static const char *voldown[] = {"/home/br4mos/.dwm/volume.sh", "down", NULL};
static const char *volmute[] = {"/home/br4mos/.dwm/volume.sh", "mute", NULL};

/* Screenshot */
static const char *screenshot[] = {"flameshot", "gui", NULL};

/* Music Player Control */
static const char *playcmd[] = {"playerctl", "play-pause", NULL};
static const char *nextcmd[] = {"playerctl", "next", NULL};
static const char *prevcmd[] = {"playerctl", "previous", NULL};

/* Lockscreen command */
static const char *lockscreen[] = {"slock", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"font", STRING, &font},
    {"dmenufont", STRING, &dmenufont},
    {"background", STRING, &normbgcolor},
    {"color2", STRING, &normbordercolor},
    {"foreground", STRING, &normfgcolor},
    {"color4", STRING, &selbgcolor},
    {"color3", STRING, &selbordercolor},
    {"foreground", STRING, &selfgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
};

#include <X11/XF86keysym.h>
static const Key keys[] = {
    /* modifier                     key        function        argument */
    /* Brightness */
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightnessup}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightnessdown}},
    /* Volume */
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volup}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = voldown}},
    {0, XF86XK_AudioMute, spawn, {.v = volmute}},
    /* Media Control */
    {0, XF86XK_AudioPlay, spawn, {.v = playcmd}},
    {0, XF86XK_AudioNext, spawn, {.v = nextcmd}},
    {0, XF86XK_AudioPrev, spawn, {.v = prevcmd}},
    /* Lockscreen: Mod + Shift + L */
    {MODKEY | ShiftMask, XK_l, spawn, {.v = lockscreen}},
    /* Screenshot */
    {0, XK_Print, spawn, {.v = screenshot}},
    /* Dmenu commands */
    {MODKEY, XK_p, spawndmenu, {.i = 1}},             // only desktop
    {MODKEY | ShiftMask, XK_p, spawndmenu, {.i = 0}}, // normal
    {MODKEY | ShiftMask, XK_s, spawn, {.v = powermenucmd}},
    {MODKEY, XK_v, spawn, {.v = clipcmd}},
    /* Base */
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_q, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_r, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_r, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | Mod4Mask, XK_space, toggleforegrounded, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_F5, xrdb, {.v = NULL}},
    {Mod1Mask, XK_Tab, altTabStart, {.i = 1}},
    {Mod1Mask, XK_grave, altTabStart, {.i = 0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
    IPCCOMMAND(view, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(toggleview, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(tag, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(toggletag, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(tagmon, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(focusmon, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(focusstack, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(zoom, 1, {ARG_TYPE_NONE}),
    IPCCOMMAND(incnmaster, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(killclient, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(togglefloating, 1, {ARG_TYPE_NONE}),
    IPCCOMMAND(setmfact, 1, {ARG_TYPE_FLOAT}),
    IPCCOMMAND(setlayoutsafe, 1, {ARG_TYPE_PTR}),
    IPCCOMMAND(quit, 1, {ARG_TYPE_NONE})};
