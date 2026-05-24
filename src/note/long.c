#include "note/long.h"

#include <stdlib.h>

LongNote* NewLongNote(int lane, float arrival_seconds, float length_seconds) {
    LongNote* note = malloc(sizeof(LongNote));
    if (!note) {
        return NULL;
    }

    note->lane = lane;
    note->isPressed = 0;
    note->arrival_seconds = arrival_seconds;
    note->length_seconds = length_seconds;

    return note;
}

void CloseLongNote(LongNote* note) {
    if (note) {
        free(note);
    }
}

LongNoteList* NewLongNoteList() {
    LongNoteList* list = malloc(sizeof(LongNoteList));
    if (!list) {
        return NULL;
    }

    list->length = 0;
    list->notes = NULL;

    return list;
}

void CloseLongNoteList(LongNoteList* list) {
    if (!list) {
        return;
    }

    free(list->notes);
    free(list);
}

int LongNoteListAdd(LongNoteList* list, int lane, float arrival_seconds, float length_seconds) {
    if (!list) {
        return -1;
    }

    LongNote* new_notes = realloc(list->notes, sizeof(LongNote) * (list->length + 1));
    if (!new_notes) {
        return -1;
    }

    list->notes = new_notes;
    list->notes[list->length].lane = lane;
    list->notes[list->length].isPressed = 0;
    list->notes[list->length].arrival_seconds = arrival_seconds;
    list->notes[list->length].length_seconds = length_seconds;
    list->length++;

    return 0;
}

int LongNoteListRemove(LongNoteList* list, int index) {
    if (!list || index < 0 || index >= list->length) {
        return -1;
    }

    for (int i = index; i < list->length - 1; i++) {
        list->notes[i] = list->notes[i + 1];
    }

    LongNote* new_notes = realloc(list->notes, sizeof(LongNote) * (list->length - 1));
    if (!new_notes && list->length - 1 > 0) {
        return -1;
    }

    list->notes = new_notes;
    list->length--;

    return 0;
}
