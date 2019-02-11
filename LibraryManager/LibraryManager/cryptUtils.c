//
//  cryptUtils.c
//  LibraryManager
//
//  Created by David Hein & Felix Hieser on 29.01.19.
//  Copyright © 2019 David Hein & Felix Hieser. All rights reserved.
//

#include "cryptUtils.h"

// https://de.wikipedia.org/wiki/Extended_Tiny_Encryption_Algorithm

// Idee:
// Bei Speichern mit Zufall Schlüsselbits generieren,
// Anzahl Durchlaufzyklus auch zufällig wählen.
// 128 Schlüsselbits als erstes in Datei schreiben, Durchläufe ans Ende.



/* gegeben sind 64 Datenbits in v[0] und v[1] und 128 Schlüsselbits in k[0] bis k[3] */
/* Die Daten werden mit 2 * num_cycles Runden verschlüsselt */



void encipher (unsigned int cycles, uint32_t v[2], uint32_t const k[4]) {
    const uint32_t delta = 0x9E3779B9;
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    for (int i = 0; i < cycles; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
    }
    v[0] = v0;
    v[1] = v1;
}

void decipher (unsigned int cycles, uint32_t v[2], uint32_t const k[4]) {
    const uint32_t delta = 0x9E3779B9;
    uint32_t v0 = v[0], v1 = v[1], sum = delta * cycles;
    for (int i = 0; i < cycles; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
    }
    v[0] = v0;
    v[1] = v1;
}
