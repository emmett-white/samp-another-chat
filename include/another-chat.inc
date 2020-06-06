/**
  * Include: Another Chat
  * Author: Emmett
  * Date: 6th June
  * Git: github.com/emmett-white/samp-another-chat
  * Copyright (C) 2020
  */


#include <a_samp>
#tryinclude <YSI_Coding\y_hooks>

#if !defined MAX_CHAT_LINES
	#define MAX_CHAT_LINES                               10
#endif

#if defined strcpy_undefined__
    #define strcpy(%0,%1) strcat((%0[0] = '\0', %0), %1)
#endif


/// <summary>
/// Variables
/// </summary>

static
    PlayerText: Chat_TextDraw[MAX_CHAT_LINES],
    Chat_Text[MAX_PLAYERS][MAX_CHAT_LINES][128],
    Chat_Toggled[MAX_PLAYERS] = false;


/// <summary>
/// Functions
/// </summary>

/// <summary>
/// An example for this function:
///
/// YCMD:chat(playerid, const params[], help)
/// {
///    Chat_Create(playerid);
///    return COMMAND_OK;
/// }
///
/// </summary>

stock Chat_Create(const playerid)
{
    static Float: Chat_PosY = (229.573348);

    for (new i = 0; i < MAX_CHAT_LINES; ++i) {
        Chat_TextDraw[i] = CreatePlayerTextDraw(playerid, 35.599971, Chat_PosY,       " ");
        PlayerTextDrawLetterSize(playerid, Chat_TextDraw[i],                     0.21, 0.9);
        PlayerTextDrawAlignment(playerid, Chat_TextDraw[i],                              1);
        PlayerTextDrawColor(playerid, Chat_TextDraw[i],                                 -1);
        PlayerTextDrawSetOutline(playerid, Chat_TextDraw[i],                             1);
        PlayerTextDrawBackgroundColor(playerid, Chat_TextDraw[i],                      255);
        PlayerTextDrawFont(playerid, Chat_TextDraw[i],                                   1);
        PlayerTextDrawSetProportional(playerid, Chat_TextDraw[i],                        1);

        Chat_PosY += (240.026733 - 229.573348);
    }

    Chat_Toggled[playerid] = false;

    return 1;
}

/// <summary>
/// An example for this function:
///
/// hook OnPlayerText(playerid, text[])
/// {
///     Chat_Message(playerid, text);
///     return (Chat_IsToggled(playerid) ? 0 : 1);
/// }
///
/// </summary>

stock Chat_Message(const playerid, const message[])
{
    if (!Chat_Toggled[playerid]) 
        return 0;

    for (new i = 0; i < MAX_CHAT_LINES; ++i) {
        if (i == (MAX_CHAT_LINES - 1)) {
            strcpy(Chat_Text[playerid][i], message);
            break;
        }

        strcpy(Chat_Text[playerid][i], Chat_Text[playerid][i + 1]);
    }

    for (new i = 0; i < MAX_CHAT_LINES; ++i)
        PlayerTextDrawSetString(playerid, Chat_TextDraw[i], Chat_Text[playerid][i]);

    return 1;
}

/// <summary>
/// Destroying chat textdraw
/// </summary>

/// <summary>
/// An example for this function:
///
/// hook OnPlayerDisconnect(playerid, reason)
/// {
///     Chat_Destroy(playerid);
///     return 1;
/// }
///
/// </summary>

stock Chat_Destroy(const playerid)
{
    for (new i = 0; i < MAX_CHAT_LINES; ++i) {
        PlayerTextDrawDestroy(playerid, Chat_TextDraw[i]);
        Chat_TextDraw[i] = INVALID_TEXT_DRAW;
    }

    Chat_Toggled[playerid] = false;

    return 1;
}

/// <summary>
/// Clear all chat lines
/// </summary>

stock Chat_Clear(const playerid)
{
    for (new i = 0; i < MAX_CHAT_LINES; ++i) {
        strcpy(Chat_Text[playerid][i], " ");

        if (_: Chat_TextDraw[i] != INVALID_TEXT_DRAW) PlayerTextDrawSetString(playerid, Chat_TextDraw[i], " ");
    }

    return 1;
}

/// <summary>
/// Show/Hide chat for player
/// </summary>

/// <summary>
/// An example for this function:
///
/// YCMD:togglechat(playerid, const params[], help)
/// {
///    Chat_Toggle(playerid, true);
///    return COMMAND_OK;
/// }
///
/// </summary>

stock Chat_Toggle(const playerid, bool: toggle = true)
{
    if (toggle) for (new i = 0; i < MAX_CHAT_LINES; ++i) PlayerTextDrawShow(playerid, Chat_TextDraw[i]);
    else for (new i = 0; i < MAX_CHAT_LINES; ++i) PlayerTextDrawHide(playerid, Chat_TextDraw[i]);

    Chat_Toggled[playerid] = toggle;

    return 1;
}

/// <summary>
/// Getting status of chat (True/False)
/// </summary>

stock Chat_IsToggled(playerid)
{
    return Chat_Toggled[playerid];
}

/// <summary>
/// Hook
/// </summary>

hook OnPlayerText(playerid, text[])
{
    Chat_Message(playerid, text);
    return (Chat_IsToggled(playerid) ? 0 : 1);
}