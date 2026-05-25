#include "compete/protocol.h"

#include <process.h>
#include "constant/protocol.h"

UDPClient* NewUDPClient() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return NULL;
    }

    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) {
        WSACleanup();
        return NULL;
    }

    u_long mode = 1;
    if (ioctlsocket(s, FIONBIO, &mode) != 0) {
        closesocket(s);
        WSACleanup();
        return NULL;
    }

    SOCKADDR_IN local_addr;
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(0);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(s, (struct sockaddr*)&local_addr, sizeof(local_addr)) == SOCKET_ERROR) {
        closesocket(s);
        WSACleanup();
        return NULL;
    }

    UDPClient* client = (UDPClient*)malloc(sizeof(UDPClient));
    if (client == NULL) {
        closesocket(s);
        WSACleanup();
        return NULL;
    }

    client->sock = s;
    client->room_id = 0;
    client->ready = 0;
    
    client->player_uid = (int32_t)GetCurrentProcessId();

    memset(&(client->addr), 0, sizeof(client->addr));
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(PROTOCOL_SERVER_PORT);
    client->addr.sin_addr.s_addr = inet_addr(PROTOCOL_SERVER_IP);

    return client;
}

void UDPClientSetRoomID(UDPClient* client, int32_t room_id) {
    if (client != NULL) {
        client->room_id = room_id;
    }
}

void UDPClientSetReady(UDPClient* client, uint8_t ready) {
    if (client != NULL) {
        client->ready = ready;
    }
}

int UDPClientRecvReadyStates(UDPClient* client, PlayerReadyState* states, int max_states) {
    if (client == NULL || client->sock == INVALID_SOCKET) {
        return -1;
    }

    ReadyPacket packet;
    packet.pid = 1;
    packet.room_id = htonl(client->room_id);
    packet.player_uid = htonl(client->player_uid);
    packet.ready = client->ready;

    int bytesSent = sendto(
        client->sock,
        (const char*)&packet,
        sizeof(packet),
        0,
        (struct sockaddr*)&(client->addr),
        sizeof(client->addr)
    );

    if (bytesSent == SOCKET_ERROR) {
        return -1;
    }

    if (states == NULL || max_states <= 0) {
        return -1;
    }

    char buf[PROTOCOL_BUFFER_SIZE];
    int bytesRecv = recvfrom(client->sock, buf, sizeof(buf), 0, NULL, NULL);

    if (bytesRecv == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK || err == WSAEINTR) {
            return 0;
        }
        return -1;
    }

    if (bytesRecv < 5) {
        return -1;
    }

    uint8_t pid = (uint8_t)buf[0];
    if (pid != 2) {
        return -1;
    }

    int32_t n;
    memcpy(&n, &buf[1], sizeof(n));
    n = ntohl(n);

    if (n < 0) {
        return -1;
    }

    int expectedSize = 5 + n * 5;
    if (bytesRecv < expectedSize) {
        return -1;
    }

    int count = (n < max_states) ? n : max_states;
    for (int i = 0; i < count; i++) {
        int offset = 5 + i * 5;
        int32_t puid;
        memcpy(&puid, &buf[offset], sizeof(puid));
        states[i].player_uid = ntohl(puid);
        states[i].ready = (uint8_t)buf[offset + 4];
    }

    return count;
}

int UDPClientRecvExchangeStates(UDPClient* client, PlayerExchangeState* states, int max_states, int32_t score, int32_t total_loss, int32_t user_loss, int32_t combo, int32_t max_combo) {
    if (client == NULL || client->sock == INVALID_SOCKET) {
        return -1;
    }

    ExchangePacket packet;
    packet.pid = 3;
    packet.room_id = htonl(client->room_id);
    packet.player_uid = htonl(client->player_uid);
    packet.score = htonl(score);
    packet.total_loss = htonl(total_loss);
    packet.user_loss = htonl(user_loss);
    packet.combo = htonl(combo);
    packet.max_combo = htonl(max_combo);

    int bytesSent = sendto(
        client->sock,
        (const char*)&packet,
        sizeof(packet),
        0,
        (struct sockaddr*)&(client->addr),
        sizeof(client->addr)
    );

    if (bytesSent == SOCKET_ERROR) {
        return -1;
    }

    if (states == NULL || max_states <= 0) {
        return -1;
    }

    char buf[PROTOCOL_BUFFER_SIZE];
    int bytesRecv = recvfrom(client->sock, buf, sizeof(buf), 0, NULL, NULL);

    if (bytesRecv == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK || err == WSAEINTR) {
            return 0;
        }
        return -1;
    }

    if (bytesRecv < 5) {
        return -1;
    }

    uint8_t pid = (uint8_t)buf[0];
    if (pid != 4) {
        return -1;
    }

    int32_t n;
    memcpy(&n, &buf[1], sizeof(n));
    n = ntohl(n);

    if (n < 0) {
        return -1;
    }

    int expectedSize = 5 + n * 24;
    if (bytesRecv < expectedSize) {
        return -1;
    }

    int count = (n < max_states) ? n : max_states;
    for (int i = 0; i < count; i++) {
        int offset = 5 + i * 24;
        int32_t puid, pscore, pTotalLoss, pUserLoss, pcombo, pmax;
        memcpy(&puid, &buf[offset], sizeof(puid));
        memcpy(&pscore, &buf[offset+4], sizeof(pscore));
        memcpy(&pTotalLoss, &buf[offset+8], sizeof(pTotalLoss));
        memcpy(&pUserLoss, &buf[offset+12], sizeof(pUserLoss));
        memcpy(&pcombo, &buf[offset+16], sizeof(pcombo));
        memcpy(&pmax, &buf[offset+20], sizeof(pmax));

        states[i].player_uid = ntohl(puid);
        states[i].score = ntohl(pscore);
        states[i].total_loss = ntohl(pTotalLoss);
        states[i].user_loss = ntohl(pUserLoss);
        states[i].combo = ntohl(pcombo);
        states[i].max_combo = ntohl(pmax);
    }

    return count;
}
