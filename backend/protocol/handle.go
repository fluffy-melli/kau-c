package protocol

import (
	"encoding/binary"
)

const (
	PacketIDClientReady    = 1
	PacketIDServerReady    = 2
	PacketIDClientExchange = 3
	PacketIDServerExchange = 4
)

type PlayerReadyState struct {
	Ready byte
}

type PlayerExchangeState struct {
	Score     int32
	TotalLoss int32
	UserLoss  int32
	Combo     int32
	MaxCombo  int32
}

type RoomState struct {
	ReadyDate map[int32]*PlayerReadyState
	Exchange  map[int32]*PlayerExchangeState
}

type Service struct {
	runtime map[int32]*RoomState
}

func NewService() *Service {
	return &Service{
		runtime: make(map[int32]*RoomState),
	}
}

func (s *Service) Handle(data []byte) []byte {
	if len(data) < 1 {
		return nil
	}

	packetID := data[0]

	switch packetID {
	case PacketIDClientReady:
		if len(data) < 10 {
			return nil
		}

		roomUID := int32(binary.BigEndian.Uint32(data[1:5]))
		playerUID := int32(binary.BigEndian.Uint32(data[5:9]))
		ready := data[9]

		room, exists := s.runtime[roomUID]
		if !exists {
			room = &RoomState{
				ReadyDate: make(map[int32]*PlayerReadyState),
				Exchange:  make(map[int32]*PlayerExchangeState),
			}
			s.runtime[roomUID] = room
		}

		playerState, exists := room.ReadyDate[playerUID]
		if !exists {
			playerState = &PlayerReadyState{}
			room.ReadyDate[playerUID] = playerState
		}
		playerState.Ready = ready

		if ready == 2 {
			delete(room.ReadyDate, playerUID)
			if room.Exchange != nil {
				delete(room.Exchange, playerUID)
			}
			return nil
		}

		n := len(room.ReadyDate)

		payloadSize := 1 + 4 + (5 * n)
		response := make([]byte, payloadSize)

		response[0] = PacketIDServerReady

		binary.BigEndian.PutUint32(response[1:5], uint32(n))

		offset := 5
		for pUID, pState := range room.ReadyDate {
			binary.BigEndian.PutUint32(response[offset:offset+4], uint32(pUID))
			response[offset+4] = pState.Ready
			offset += 5
		}

		return response
	case PacketIDClientExchange:
		if len(data) < 29 {
			return nil
		}

		roomUID := int32(binary.BigEndian.Uint32(data[1:5]))
		playerUID := int32(binary.BigEndian.Uint32(data[5:9]))
		score := int32(binary.BigEndian.Uint32(data[9:13]))
		totalLoss := int32(binary.BigEndian.Uint32(data[13:17]))
		userLoss := int32(binary.BigEndian.Uint32(data[17:21]))
		combo := int32(binary.BigEndian.Uint32(data[21:25]))
		maxCombo := int32(binary.BigEndian.Uint32(data[25:29]))

		room, exists := s.runtime[roomUID]
		if !exists {
			room = &RoomState{
				ReadyDate: make(map[int32]*PlayerReadyState),
				Exchange:  make(map[int32]*PlayerExchangeState),
			}
			s.runtime[roomUID] = room
		}

		pState, exists := room.Exchange[playerUID]
		if !exists {
			pState = &PlayerExchangeState{}
			room.Exchange[playerUID] = pState
		}

		pState.Score = score
		pState.TotalLoss = totalLoss
		pState.UserLoss = userLoss
		pState.Combo = combo
		pState.MaxCombo = maxCombo

		n := len(room.Exchange)

		payloadSize := 1 + 4 + (24 * n)
		response := make([]byte, payloadSize)

		response[0] = PacketIDServerExchange

		binary.BigEndian.PutUint32(response[1:5], uint32(n))

		offset := 5
		for pUID, eState := range room.Exchange {
			binary.BigEndian.PutUint32(response[offset:offset+4], uint32(pUID))
			binary.BigEndian.PutUint32(response[offset+4:offset+8], uint32(eState.Score))
			binary.BigEndian.PutUint32(response[offset+8:offset+12], uint32(eState.TotalLoss))
			binary.BigEndian.PutUint32(response[offset+12:offset+16], uint32(eState.UserLoss))
			binary.BigEndian.PutUint32(response[offset+16:offset+20], uint32(eState.Combo))
			binary.BigEndian.PutUint32(response[offset+20:offset+24], uint32(eState.MaxCombo))
			offset += 24
		}

		return response
	default:
		return nil
	}
}
