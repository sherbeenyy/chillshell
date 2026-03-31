#include "StringView.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


StringView sv(const char *cstr)
{
    return (StringView){
        .start = cstr,
        .count = strlen(cstr)};
}

void sv_chop_left(StringView *sv, size_t k)
{
    if (k > sv->count)
        k = sv->count;

    sv->start += k;
    sv->count -= k;
}


void sv_chop_right(StringView *sv, size_t k)
{
    if (k > sv->count)
        k = sv->count;

    sv->count -= k;
}


void sv_trimmer(StringView *sv)
{
    while (sv->count > 0 && isspace(sv->start[0]))
    {
        sv_chop_left(sv, 1);
    }
    while (sv->count > 0 && isspace(sv->start[sv->count - 1]))
    {
        sv_chop_right(sv, 1);
    }
}


StringView *sv_allocateTokensArray(size_t capacity)
{
    StringView *tokens = malloc(capacity * sizeof(StringView));
    if (tokens == NULL)
        return NULL;
    return tokens;
}


StringView *sv_Tokenizer(const StringView *sv)
{
    StringView frame = *sv;

    sv_trimmer(&frame);

    size_t capacity = 20;
    StringView *tokens = sv_allocateTokensArray(capacity);
    size_t tokens_count = 0;

    while (frame.count > 0)
    {
        size_t i = 0;
        while (i < frame.count && !isspace(frame.start[i]))
            i++;

        if (tokens_count >= capacity - 1)
        {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(StringView));
        }

        tokens[tokens_count].start = frame.start;
        tokens[tokens_count].count = i;
        tokens_count++;

        sv_chop_left(&frame, i);
        sv_trimmer(&frame);
    }
    tokens[tokens_count] = (StringView){.start = NULL, .count = 0};
    return tokens;
}
