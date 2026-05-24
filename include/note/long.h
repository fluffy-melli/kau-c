#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int lane;
    int isPressed;
    float arrival_seconds;
    float length_seconds;
} LongNote;

typedef struct {
    int length;
    LongNote* notes;
} LongNoteList;

LongNote* NewLongNote(int lane, float arrival_seconds, float length_seconds);
void CloseLongNote(LongNote* note);

LongNoteList* NewLongNoteList();
void CloseLongNoteList(LongNoteList* list);

int LongNoteListAdd(LongNoteList* list, int lane, float arrival_seconds, float length_seconds);
int LongNoteListRemove(LongNoteList* list, int index);

#ifdef __cplusplus
}
#endif

