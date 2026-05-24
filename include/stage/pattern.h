#pragma once

#include "note/short.h"

#ifdef __cplusplus
extern "C" {
#endif

int OpenPatternFile(const char* stage_json_path, ShortNoteList* short_note_list);

#ifdef __cplusplus
}
#endif
