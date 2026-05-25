#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#define Rectangle WinRectangle
#define CloseWindow WinCloseWindow
#define ShowCursor WinShowCursor

#include <Winsock2.h>

#undef Rectangle
#undef CloseWindow
#undef ShowCursor

#pragma pack(push, 1)
typedef struct {
    uint8_t pid;
    int32_t room_id;
    int32_t player_uid;
    uint8_t ready;
} ReadyPacket;
#pragma pack(pop)

typedef struct {
    int32_t player_uid;
    uint8_t ready;
} PlayerReadyState;

#pragma pack(push, 1)
typedef struct {
    uint8_t pid;
    int32_t room_id;
    int32_t player_uid;
    int32_t score;
    int32_t total_loss;
    int32_t user_loss;
    int32_t combo;
    int32_t max_combo;
} ExchangePacket;
#pragma pack(pop)

typedef struct {
    int32_t player_uid;
    int32_t score;
    int32_t total_loss;
    int32_t user_loss;
    int32_t combo;
    int32_t max_combo;
} PlayerExchangeState;

typedef struct {
    SOCKET sock;
    SOCKADDR_IN addr;
    
    uint8_t ready;
    int32_t room_id;
    int32_t player_uid;
} UDPClient;

UDPClient* NewUDPClient();

void UDPClientSetRoomID(UDPClient* client, int32_t room_id);
void UDPClientSetReady(UDPClient* client, uint8_t ready);

int UDPClientRecvReadyStates(UDPClient* client, PlayerReadyState* states, int max_states);
int UDPClientRecvExchangeStates(UDPClient* client, PlayerExchangeState* states, int max_states, int32_t score, int32_t total_loss, int32_t user_loss, int32_t combo, int32_t max_combo);
