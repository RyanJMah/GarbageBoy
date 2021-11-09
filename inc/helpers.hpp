#pragma once

#define BIT_IS_SET(x, n)        ( ((x >> n) & 1) == 1 )
#define BIT_IS_CLEAR(x, n)      ( ((x >> n) & 1) == 0 )
