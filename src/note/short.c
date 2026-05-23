#include "note/short.h"

#include <stdlib.h>

ShortNote* NewShortNote(int lane, float arrival_seconds) {
    ShortNote* note = malloc(sizeof(ShortNote));
    if (!note) {
        return NULL;
    }

    note->lane = lane;
    note->arrival_seconds = arrival_seconds;

    return note;
}

void CloseShortNote(ShortNote* note) {
    if (note) {
        free(note);
    }
}

ShortNoteList* NewShortNoteList() {
    ShortNoteList* list = malloc(sizeof(ShortNoteList));
    if (!list) {
        return NULL;
    }

    list->length = 0;
    list->notes = NULL;

    return list;
}

void CloseShortNoteList(ShortNoteList* list) {
    if (!list) {
        return;
    }

    free(list->notes);
    free(list);
}

int ShortNoteListAdd(ShortNoteList* list, int lane, float arrival_seconds) {
    if (!list) {
        return -1;
    }

    ShortNote* new_notes = realloc(list->notes, sizeof(ShortNote) * (list->length + 1));
    if (!new_notes) {
        return -1;
    }

    list->notes = new_notes;
    list->notes[list->length].lane = lane;
    list->notes[list->length].arrival_seconds = arrival_seconds;
    list->length++;

    return 0;
}

int ShortNoteListRemove(ShortNoteList* list, int index) {
    if (!list || index < 0 || index >= list->length) {
        return -1;
    }

    for (int i = index; i < list->length - 1; i++) {
        list->notes[i] = list->notes[i + 1];
    }

    ShortNote* new_notes = realloc(list->notes, sizeof(ShortNote) * (list->length - 1));
    if (!new_notes && list->length - 1 > 0) {
        return -1;
    }

    list->notes = new_notes;
    list->length--;

    return 0;
}
