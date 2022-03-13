#ifndef _TOKEN_H_GUARD_
#define _TOKEN_H_GUARD_

#include "common.h"

typedef enum {
    // Unknown token
    CKT_TK_UNKNOWN,

    CKT_TK_IDENT,
    CKT_TK_NUMBER,

    // Symbols
    CKT_TK_PERIOD,
    CKT_TK_COMMA,
    CKT_TK_COLON,
    CKT_TK_SEMICOLON,
    CKT_TK_LPAREN,
    CKT_TK_RPAREN,
    CKT_TK_LSQUARE,
    CKT_TK_RSQUARE,
    CKT_TK_LCURLY,
    CKT_TK_RCURLY,
    CKT_TK_LANGLE,
    CKT_TK_RANGLE,

    // Arithmetic
    CKT_TK_PLUS,
    CKT_TK_MINUS,
    CKT_TK_MULTIPLY,
    CKT_TK_DIVIDE,
    CKT_TK_EXPONENT,

    // Keywords
    CKT_TK_KW_CIRCUIT,
    CKT_TK_KW_INTERFACE,
    CKT_TK_KW_DECLARE,
    CKT_TK_KW_CONNECT,
    CKT_TK_KW_TO,
    CKT_TK_KW_INPUT,
    CKT_TK_KW_OUTPUT,
    CKT_TK_KW_TRANSPUT,
    CKT_TK_KW_HI,
    CKT_TK_KW_LO,
} CktTokenType;

extern CktTokenType getCktTokenType(const char *s);

struct CktToken {
    int line, column, len;
    CktTokenType type;
    char *value;
    struct CktToken *prev, *next;
};

typedef struct CktToken CktToken;

/**
 * @brief Creates a new CktToken. Returns NULL on failure.
 * 
 * @param value The string value of this token
 * @param line The line on which this token occurred
 * @param column The column on which this token occured
 * @return CktToken * 
 */
extern CktToken *newCktToken(const char *value, int line, int column);

/**
 * @brief Deallocates the memory for a specified CktToken.
 * 
 * @param t A pointer to the CktToken to destroy
 */
extern void destroyCktToken(CktToken *t);

/**
 * @brief Deallocates the memory for a linked list of CktTokens.
 * 
 * @param t A pointer to the first CktToken in the linked list
 */
extern void destroyCktTokens(CktToken *t);

typedef struct {
    int len, cur;
    CktToken *tk;
    CktToken *head;
} CktTokenStream;

/**
 * @brief Creates a new CktTokenStream. Returns NULL on failure.
 * 
 * @return CktTokenStream * 
 */
extern CktTokenStream *newCktTokenStream();

/**
 * @brief Deallocates the memory for the specified CktTokenStream.
 * 
 * @param ts A pointer to the CktTokenStream to destroy
 */
extern void destroyCktTokenStream(CktTokenStream *ts);

/**
 * @brief Adds a CktToken to a CktTokenStream. Returns 1 on failure.
 * 
 * @param ts A pointer to the CktTokenStream
 * @param value The string value of the new token
 * @param line The line on which this token occurred
 * @param column The column on which this token occurred
 * @return CktError 
 */
extern CktError addCktTokenStreamToken(CktTokenStream *ts, const char *value, int line, int column);

/**
 * @brief Get the next CktToken from the stream. Returns NULL if the end of the CktTokenStream is reached.
 * 
 * @param ts A pointer to the CktTokenStream
 * @return CktToken * 
 */
extern CktToken *nextCktTokenStreamToken(CktTokenStream *ts);

/**
 * @brief Get the next CktToken from the stream without consuming it. Returns NULL if the end of the CktTokenStream is reached.
 * 
 * @param ts A pointer to the CktTokenStream
 * @return CktToken * 
 */
extern CktToken *peekCktTokenStreamToken(CktTokenStream *ts);
#endif