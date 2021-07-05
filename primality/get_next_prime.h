#ifndef GET_NEXT_PRIME
#define GET_NEXT_PRIME

#include <stdio.h>
#include <stdlib.h>

#include "../dtypes/natural.h"
#include "lucas_lehmer.h"
#include "miller_rabin.h"

natural* get_next_prime(natural* low, int trial_divisions, int witnesses);
natural** get_next_primes(natural* low, int trial_divisions, int witnesses,
        int num_primes);

#endif
