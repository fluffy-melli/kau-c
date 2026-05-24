#pragma once

#include "note/short.h"
#include "note/long.h"

#ifdef __cplusplus
extern "C" {
#endif

int OpenPatternFile(const char* stage_json_path, ShortNoteList* short_note_list, LongNoteList* long_note_list);

#ifdef __cplusplus
}
#endif
