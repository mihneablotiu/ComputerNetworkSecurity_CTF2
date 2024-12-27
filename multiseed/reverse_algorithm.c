#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seeds[10] = {0xb19d1c5f, 0xd678b9a7, 0x3d68432d, 0xb78cf1b3, 0x43e5308b, 0x6d461699, 0x69946081, 0xbdadad6c, 0x205c11a2, 0x6565a5b0};
char flag_enc[41] = {0xdb, 0x20, 0x98, 0xc1, 0x08, 0x84, 0x5e, 0xda, 0xa3, 0xb4, 0x57, 0xe3, 0xb0, 0xe5, 0xcc, 0xe6,
                     0x8f, 0x27, 0xfe, 0x20, 0x82, 0x41, 0xb8, 0x1e, 0x07, 0xa7, 0x45, 0xb2, 0xe4, 0x11, 0xda, 0x7b,
                     0xd2, 0xd4, 0x8e, 0x48, 0xb6, 0xac, 0xac, 0x7c, 0xd9};
int flag_len = 41;

void reverse_thread_fn(int seed) {
    char recovered_input[flag_len];
    memset(recovered_input, 0, flag_len);

    char random_state[128];
    struct random_data buf;
    memset(&buf, 0, sizeof(buf));

    initstate_r(seed, random_state, sizeof(random_state), &buf);
    srandom_r(seed, &buf);

    memcpy(recovered_input, flag_enc, flag_len);

    for (int i = 0; i < flag_len; i++) {
        int32_t random_value;
        random_r(&buf, &random_value);

        recovered_input[i] ^= random_value & 0xFF;
    }

    puts(recovered_input);
}



int main() {
    for (int i = 0; i < 10; i++) {
        reverse_thread_fn(seeds[i]);
    }
    
    return 0;
}
