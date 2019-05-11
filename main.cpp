/**

*@brief only test 4x4

*/

void transpose_neon_4x4(float *src, float *dst) {

asm volatile (

    "ldr q0, [%[src]]\n"          // a0123

    "ldr q1, [%[src], #16]\n"    // b0123

    "ldr q2, [%[src], #32]\n"    // c0123

    "ldr q3, [%[src], #48]\n"    // d0123

    // zip1: get upper half and interleave store

    "zip1 v4.4s, v0.4s, v2.4s\n"  // a0c0a1c1

    "zip1 v5.4s, v1.4s, v3.4s\n"  // b0d0b1d1

    // zip2: get lower half and interleave

    "zip2 v6.4s, v0.4s, v2.4s\n"  // a2c2a3c3

   "zip2 v7.4s, v1.4s, v3.4s\n"  // b2d2b3d3

    // transpose part

    "zip1 v0.4s, v4.4s, v5.4s\n"  // a0b0c0d0

    "zip2 v1.4s, v4.4s, v5.4s\n"  // a1b1c1d1

    "zip1 v2.4s, v6.4s, v7.4s\n"  // a2b2c2d2

    "zip2 v3.4s, v6.4s, v7.4s\n"  // a3b3c3d3

    "str q0, [%[dst]]\n"

    "str q1, [%[dst], #16]\n"

    "str q2, [%[dst], #32]\n"

    "str q3, [%[dst], #48]\n"

    : [src] "+r" (src),

      [dst] "+r" (dst)

    :

    : "v0", "v1", "v2", "v3",

      "v4", "v5", "v6", "v7",

      "memory"

  );

}
