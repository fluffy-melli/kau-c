#include "stage/pattern.h"

#include <vector>
#include <glaze/glaze.hpp>
#include "note/short.h"

enum NoteType {
    Short = 0,
    Long = 1
};

struct SharedNote {
    NoteType type;
    int lane;
    float arrival_seconds;
    float length_seconds = 0.0f;
};

struct Pattern {
    std::vector<SharedNote> v;
};

template <>
struct glz::meta<SharedNote> {
    using T = SharedNote;
    static constexpr auto value = glz::object(
        "t", &T::type,
        "l", &T::lane,
        "a", &T::arrival_seconds,
        "len", &T::length_seconds
    );
};

template <>
struct glz::meta<Pattern> {
    using T = Pattern;
    static constexpr auto value = glz::object(
        "v", &T::v
    );
};

int OpenPatternFile(const char* stage_json_path, ShortNoteList* short_note_list, LongNoteList* long_note_list) {
    auto* pattern = new Pattern();

    static std::vector<std::byte> buffer;
    auto ec = glz::read_file_json(*pattern, stage_json_path, buffer);

    if (ec) {
        delete pattern;
        return -1;
    }

    for (SharedNote note : pattern->v) {
        switch (note.type) {
            case NoteType::Short:
                ShortNoteListAdd(short_note_list, note.lane, note.arrival_seconds);
                break;
            case NoteType::Long:
                LongNoteListAdd(long_note_list, note.lane, note.arrival_seconds, note.length_seconds);
                break;
            default:
                break;
        }
    }

    delete pattern;
    return 0;
}
