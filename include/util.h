/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

typedef char BYTE;
typedef BYTE *PBYTE;

typedef enum _STATUS
{
    SUCCESS = 0,
    ERROR = 1,
    FILE_NOT_FOUND = 2,
    INVALIDARG = 3,
    ACCESSDENIED = 13,
    OUTOFMEMORY = 14,
    HANDLE = 38,
    POINTER = 125,
    NOTIMPL = 213,
    NOINIT = 214,
    BOUNDS = 280,
    ILLEGAL_METHOD_CALL = 310,
    ILLEGAL_DELEGATE_ASSIGNMENT = 311,
    ILLEGAL_STATE_CHANGE = 332,
} STATUS;

#define FAILED(st) ((STATUS)(st) < 0)
#define RETURN_IF_FAILED(st) do { STATUS __stRet = st; if (FAILED(__stRet)) { return st; }} while (0)