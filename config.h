/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/*#include "/home/manan/.cache/wal/colors-dwm.h"*/
#include "fibonacci.c"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 35;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Iosevka Nerd Font:size=13" };
static const char dmenufont[]       = "Iosevka Nerd Font:size=13";

// // gruvbox
// static const char col_gray1[]       = "#282828";
// static const char col_gray2[]       = "#504945";
// static const char col_gray3[]       = "#bdae93";
// static const char col_gray4[]       = "#ebdbb2";
// static const char col_cyan[]        = "#cc241d";
// static const char *colors[][3]      = {
// 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
// 	[SchemeSel]  = { col_gray4, col_gray1,  col_gray3  },
// };

// nerdy
// static const char col_bg[]       = "#212121";
// static const char col_fg[]       = "#eeffff";
// static const char col_gray[]     = "#4a4a4a";
// static const char col_accent[]   = "#13ca91";  // or use #7898fb or #f07178 for contrast
//
// static const char *colors[][3]   = {
// 	[SchemeNorm] = { col_fg, col_bg, col_gray },
// 	[SchemeSel]  = { col_fg, col_bg, col_accent },
// };

// nerdy-amoled
static const char col_bg[]       = "#000000";
static const char col_fg[]       = "#eeffff";
static const char col_gray[]     = "#202020";
static const char col_accent[]   = "#13ca91";  // vibrant accent, or "#ff5370" for red

static const char *colors[][3]   = {
	[SchemeNorm] = { col_fg, col_bg, col_gray },
	[SchemeSel]  = { col_fg, col_bg, col_accent },
};


/* tagging */
// static const char *tags[] = { "one", "two", "three", "four", "five", "six", "seven", "eight" };
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "[@]",      spiral },
    { "[//]",     dwindle },
    { "TTT",      bstack },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MOD4KEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run" ,NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *lockcmd[] = { "block", NULL };
static const char *scrcmd[]  = { "scr", NULL };
static const char *qrcmd[]  = { "qr", NULL };
static const char *mutetoggle[] = { "vol", "mute", NULL };
static const char *volinc[] = { "vol", "up", NULL };
static const char *voldec[] = { "vol", "down", NULL };
static const char *brinc[] = { "bri", "inc", NULL };
static const char *brdec[] = { "bri", "dec", NULL };
static const char *emoji[] = { "emojiselect", NULL };
static const char *dunsthist[] = { "dunstctl", "history-pop", NULL };
static const char *dunstclose[] = { "dunstctl", "close", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MOD4KEY,                      XK_l,      spawn,          {.v = lockcmd } },
	{ MOD4KEY,                      XK_q,      spawn,          {.v = qrcmd } },
	{ MOD4KEY,                      XK_s,      spawn,          {.v = scrcmd } },
	{ MOD4KEY,                      XK_e,      spawn,          {.v = emoji } },
	{ ControlMask,                  XK_space,  spawn,          {.v = dunstclose } },
	{ ControlMask|ShiftMask,        XK_space,  spawn,          {.v = dunsthist } },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_j,      moveresize,	   {.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY|ShiftMask,		XK_k,	   moveresize,	   {.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY|ShiftMask,		XK_l,      moveresize,	   {.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,		XK_h,      moveresize,	   {.v = (int []){ -25, 0, 0, 0 }}},
	{ MODKEY|ControlMask|ShiftMask,	XK_j,      moveresize,	   {.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ControlMask|ShiftMask,	XK_k,	   moveresize,	   {.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ControlMask|ShiftMask,	XK_l,      moveresize,	   {.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ControlMask|ShiftMask,	XK_h,      moveresize,	   {.v = (int []){ 0, 0, -25, 0 }}},
	{ MODKEY|ShiftMask,		XK_c,      setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_x,      setgaps,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_a,      setgaps,        {.i = 0 } },
	{ MODKEY,                       XK_c,      movecenter,     {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  viewtoleft,     {0} },
	{ MODKEY,                       XK_period, viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_comma,  tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_period, tagtoright,     {0} },
	{ MOD4KEY,                      XK_comma,  focusmon,       {.i = -1 } },
	{ MOD4KEY,                      XK_period, focusmon,       {.i = +1 } },
	{ MOD4KEY|ShiftMask,            XK_comma,  tagmon,         {.i = -1 } },
	{ MOD4KEY|ShiftMask,            XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0,                            XF86XK_AudioMute,          spawn,          {.v = mutetoggle} },
    { 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = voldec} },
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = volinc} },
    { 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brinc} },
    { 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brdec} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

