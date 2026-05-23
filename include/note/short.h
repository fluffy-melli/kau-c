#pragma once

typedef struct {
    int lane;
    float arrival_seconds;
} ShortNote;

typedef struct {
    int length;
    ShortNote* notes;
} ShortNoteList;

ShortNote* NewShortNote(int lane, float arrival_seconds);
void CloseShortNote(ShortNote* note);

ShortNoteList* NewShortNoteList();
void CloseShortNoteList(ShortNoteList* list);

int ShortNoteListAdd(ShortNoteList* list, int lane, float arrival_seconds);
int ShortNoteListRemove(ShortNoteList* list, int index);
