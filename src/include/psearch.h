#ifndef PSEARCH_H
#define PSEARCH_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>
#include "img_util.h"

#define _abs(x) ((x) < 0 ? -(x) : (x))

void p_search(uint16_t **I, unsigned int N, uint16_t **P, unsigned int K);

#endif
