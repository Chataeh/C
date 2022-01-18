#ifndef C_H
#define C_H

void cipherText(FILE* fp_msg, FILE* fp_tx, unsigned char cipher_code);
void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code);
#endif