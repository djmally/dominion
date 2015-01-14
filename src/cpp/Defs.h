/* DOMINION
 * David Mally, Richard Roberts
 * Defs.h
 * Defines const strings used in colors,
 * game rules, splash screen, etc.
 */


#ifndef __DEFS_H__
#define __DEFS_H__

#define MAX_BUF_LEN 1024

const char BLACK[]        = { 0x1b, '[', '0', ';', '3', '0', 'm', 0 };
const char RED[]          = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
const char GREEN[]        = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
const char BROWN[]        = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
const char BLUE[]         = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
const char PURPLE[]       = { 0x1b, '[', '0', ';', '3', '5', 'm', 0 };
const char CYAN[]         = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
const char GRAY[]         = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
const char DARK_GRAY[]    = { 0x1b, '[', '1', ';', '3', '0', 'm', 0 };
const char LIGHT_RED[]    = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
const char LIGHT_GREEN[]  = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
const char YELLOW[]       = { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
const char LIGHT_BLUE[]   = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
const char LIGHT_PURPLE[] = { 0x1b, '[', '1', ';', '3', '5', 'm', 0 };
const char LIGHT_CYAN[]   = { 0x1b, '[', '1', ';', '3', '6', 'm', 0 };
const char WHITE[]        = { 0x1b, '[', '1', ';', '3', '7', 'm', 0 };

const char BLACK_BG[]   = "\033[40m\0";
const char RED_BG[]     = "\033[41m\0";
const char GREEN_BG[]   = "\033[42m\0";
const char BROWN_BG[]   = "\033[43m\0";
const char BLUE_BG[]    = "\033[44m\0";
const char MAGENTA_BG[] = "\033[45m\0";
const char CYAN_BG[]    = "\033[46m\0";
const char WHITE_BG[]   = "\033[47m\0";

const char RESET_BG[] = "\033[0m\0";

const char LOGO[] ="\
                                                                                \n\
 ████████▄   ▄██████▄    ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█   ▄██████▄  ███▄▄▄▄   \n\
 ███   ▀███ ███    ███ ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███  ███    ███ ███▀▀▀██▄ \n\
 ███    ███ ███    ███ ███   ███   ███ ███▌ ███   ███ ███▌ ███    ███ ███   ███ \n\
 ███    ███ ███    ███ ███   ███   ███ ███▌ ███   ███ ███▌ ███    ███ ███   ███ \n\
 ███    ███ ███    ███ ███   ███   ███ ███▌ ███   ███ ███▌ ███    ███ ███   ███ \n\
 ███    ███ ███    ███ ███   ███   ███ ███  ███   ███ ███  ███    ███ ███   ███ \n\
 ███   ▄███ ███    ███ ███   ███   ███ ███  ███   ███ ███  ███    ███ ███   ███ \n\
 ████████▀   ▀██████▀   ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▀██████▀   ▀█   █▀  \n\
                                                                                \
";

const char PLOT_TEXT[] = "You are a monarch, like your parents before you, a ruler \
of a small pleasant kingdom of\nrivers and evergreens. Unlike your parents,\
 however, you have hopes and dreams! You\nwant a bigger and more pleasant\
 kingdom, with more rivers and a wider variety of\ntrees. You want a\
 Dominion! In all directions lie fiefs, freeholds, and feodums. All are\n\
small bits of land, controlled by petty lords and verging on anarchy. You\
 will bring\ncivilization to these people, uniting them under your banner.\n\
But wait! It must be something in the air; several other monarchs have had the\
exact\nsame idea. You must race to get as much of the unclaimed land as\
 possible, fending\nthem off along the way. To do this you will hire minions,\
 construct buildings, spruce\nup your castle, and fill your treasury.\
 Your parents wouldn't be proud, but your\ngrandparents, on your mother’s\
 side, would be delighted.";

const char RULES_TEXT_1[] = "This is a game of building a deck of cards. The deck\
 is your Dominion. It contains your resources,\n\
victory points, and the things you can do. It starts out a small sad\
 collection of Estates and Coppers,\n\
but you hope by the end of the game it will be brimming with Gold,\
 Provinces, and the inhabitants\n\
and structures of your castle and kingdom.\n\
The player with the most victory points\n\
 in his Deck at game end wins.";

const char RULES_TEXT_2[] = "Each turn has three phases (A, B, and C) in the\
 order shown:\nA) Action phase - the player may play an Action.\n\
B) Buy phase - the player may buy a card.\n\
C) Clean-up phase - the player must discard both played and\n\
unplayed cards and draws five new cards.\n\
After a player completes all three phases, his turn ends.";

const char PROMPT[] = "(Type \"next\" to continue)";

#endif
