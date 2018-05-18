#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEAP_SIZE (1 << 10)
#define MAX_HASH_SIZE (1 << 8)
#define MAX_STRING_SIZE (1 << 10)

typedef unsigned char Byte;
typedef long long Integer;
typedef void* Generic;

#include "basic_structures/tree.h"
#include "basic_structures/heap.h"
#include "basic_structures/deque.h"
#include "basic_structures/hash.h"
#include "basic_structures/bit.h"
#include "huff_main/decompress.h"

#endif