#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <stddef.h>

/**
 * @brief StringView is a window that focuses on a part of a string.
 *
 * It could be a substring or the whole string.
 *
 * @struct StringView
 * @param start Pointer to the start of the string
 * @param count Number of characters in the view (counts after the start)
 */
typedef struct
{
    const char *start;
    size_t count;

} StringView;

/**
 * @brief Converts from a C string to a StringView
 */
StringView sv(const char *cstr);

/**
 * @brief chops k characters from the left of the StringView
 * @param sv The StringView to be modified
 * @param k The number of characters to chop
 */
void sv_chop_left(StringView *sv, size_t k);

/**
 * @brief chops k characters from the right of the StringView
 * @param sv The StringView to be modified
 * @param k The number of characters to chop
 */
void sv_chop_right(StringView *sv, size_t k);

/**
 * @brief trims the spaces from the left and the right of the string.
 * leaving a clean StringView
 */
void sv_trimmer(StringView *sv);

/**
 * @brief Allocates Tokens array in the heap
 * @param capacity Size of the array (how many tokens can the array hold)
 */
StringView *sv_allocateTokensArray(size_t capacity);

/**
 * @brief Tokenize a StringView by spaces
 * @return A pointer to a dynamically allocated tokens array
 */
StringView *sv_Tokenizer(const StringView *sv);

#endif // STRINGVIEW_H
