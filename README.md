## samp-another-chat
Another chat for SA-MP

## Images
![Image](https://i.ibb.co/jWjLBwq/sa-mp-833.png)

## Installation
Simply install to your project:
```bash
sampctl p install emmett-white/samp-another-chat
```

## Functions
```pawn
// stock Chat_Create(const playerid)

public OnPlayerConnect(playerid)
{
    Chat_Create(playerid);
    return 1;
}
```
```pawn
// stock Chat_Message(const playerid, const message[])

YCMD:test(playerid, const params[], help)
{
    Chat_Message(playerid, "~r~Te~g~s~b~t.");
    return COMMAND_OK;
}
```
```pawn
// stock Chat_Destroy(const playerid)

public OnPlayerDisconnect(playerid, reason)
{
    Chat_Destroy(playerid);
    return 1;
}
```
```pawn
// stock Chat_Clear(const playerid)

YCMD:clearchat(playerid, const params[], help)
{
    Chat_Clear(playerid);
    return COMMAND_OK;
}
```
```pawn
// stock Chat_Toggle(const playerid, bool: toggle = true)

YCMD:togglechat(playerid, const params[], help)
{
    Chat_Toggle(playerid, (Chat_IsToggled(playerid) == 1) ? false : true);
    return COMMAND_OK;
}
```
```pawn
stock Chat_IsToggled(playerid)
// Getting chat status (True/False) 
```
