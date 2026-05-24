import json
import librosa
import numpy as np

def generate_pattern(mp3_path, num_lanes=4):
    y, sr = librosa.load(mp3_path, sr=None)

    onset_env = librosa.onset.onset_strength(y=y, sr=sr)
    onset_frames = librosa.onset.onset_detect(
        onset_envelope=onset_env, sr=sr, wait=10, delta=0.07
    )
    arrival_times = librosa.frames_to_time(onset_frames, sr=sr)

    shared_notes = []
    np.random.seed(42)

    current_lane = int(np.random.randint(0, num_lanes))

    for time in arrival_times:
        note = {
            "t": 0,
            "l": int(current_lane),
            "a": round(float(time), 3),
        }
        
        shared_notes.append(note)
        rand_choice = np.random.rand()

        if rand_choice < 0.5:
            direction = np.random.choice([-1, 1])
            next_lane = current_lane + direction
            
            if next_lane < 0:
                next_lane = 1
            elif next_lane >= num_lanes:
                next_lane = num_lanes - 2
            current_lane = next_lane

        elif rand_choice < 0.8:
            current_lane = current_lane

        else:
            current_lane = int(np.random.randint(0, num_lanes))

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
