#include "StringView.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Converts from a C string to a StringView
 */
StringView sv(const char *cstr)
{
    return (StringView){
        .start = cstr,
        .count = strlen(cstr)};
}
/**
 * @brief chops k characters from the left of the StringView
 * @param sv The StringView to be modified
 * @param k The number of characters to chop
 */
void sv_chop_left(StringView *sv, size_t k)
{
    if (k > sv->count)
        k = sv->count;

    sv->start += k;
    sv->count -= k;
}

/**
 * @brief chops k characters from the right of the StringView
 * @param sv The StringView to be modified
 * @param k The number of characters to chop
 */
void sv_chop_right(StringView *sv, size_t k)
{
    if (k > sv->count)
        k = sv->count;

    sv->count -= k;
}

/**
 * @brief trims the spaces from the left and the right of the string.
 * leaving a clean StringView
 */
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

/**
 * @brief Allocates Tokens array in the heap
 * @param capacity Size of the array (how many tokens can the array hold)
 */
StringView *sv_allocateTokensArray(size_t capacity)
{
    StringView *tokens = malloc(capacity * sizeof(StringView));
    if (tokens == NULL)
        return NULL;
    return tokens;
}

/**
 * @brief Tokenize a StringView by spaces
 * @return A pointer to a dynamically allocated tokens array
 */
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
