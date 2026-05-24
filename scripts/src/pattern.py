import json
import librosa
import numpy as np

def generate_pattern(mp3_path, num_lanes=5):
    y, sr = librosa.load(mp3_path, sr=None)
    onset_env = librosa.onset.onset_strength(y=y, sr=sr)
    onset_frames = librosa.onset.onset_detect(
        onset_envelope=onset_env, sr=sr, wait=10, delta=0.07
    )
    arrival_times = librosa.frames_to_time(onset_frames, sr=sr)

    shared_notes = []
    active_long_notes = {}
    last_lane = -1
    BUFFER_TIME = 0.15 

    for idx, time in enumerate(arrival_times):
        if time < 1.0:
            continue

        active_long_notes = {
            lane: end_t for lane, end_t in active_long_notes.items() if end_t + BUFFER_TIME > time
        }

        available_lanes = [l for l in range(num_lanes) if l not in active_long_notes]
        if not available_lanes:
            continue

        preferred_lanes = [l for l in available_lanes if l != last_lane]
        
        if preferred_lanes and np.random.rand() < 0.85:
            current_lane = int(np.random.choice(preferred_lanes))
        else:
            if last_lane in available_lanes:
                current_lane = last_lane
            else:
                current_lane = int(np.random.choice(available_lanes))

        is_long = (np.random.rand() < 0.15) and (idx + 2 < len(arrival_times))

        if is_long:
            duration = arrival_times[idx + 2] - time
            duration = max(0.4, min(2.0, duration))
            
            note = {
                "t": 1,
                "l": current_lane,
                "a": round(float(time), 3),
                "len": round(float(duration), 3),
            }
            active_long_notes[current_lane] = time + duration
        else:
            note = {
                "t": 0,
                "l": current_lane,
                "a": round(float(time), 3),
            }
        
        shared_notes.append(note)
        last_lane = current_lane

    pattern_data = {"v": shared_notes}
    return pattern_data

def save_to_json(data, output_path):
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=4)

if __name__ == "__main__":
    input_mp3 = "../resources/stage/0/resources/audio.mp3"
    output_json = "../resources/stage/0/pattern.json"

    pattern = generate_pattern(input_mp3, num_lanes=5)
    save_to_json(pattern, output_json)
