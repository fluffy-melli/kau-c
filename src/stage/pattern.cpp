#include "stage/pattern.h"

#include <vector>
#include <glaze/glaze.hpp>
#include "note/short.h"

enum NoteType {
    Short
};

struct SharedNote {
    NoteType type;
    int lane;
    float arrival_seconds;
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
        "a", &T::arrival_seconds
    );
};

template <>
struct glz::meta<Pattern> {
    using T = Pattern;
    static constexpr auto value = glz::object(
        "v", &T::v
    );
};

int OpenPatternFile(const char* stage_json_path, ShortNoteList* short_note_list) {
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
            default:
                break;
        }
    }

    return 0;
}
