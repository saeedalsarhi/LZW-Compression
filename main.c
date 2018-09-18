#include <lzw.h>
#include <sequence.h>
#include <dict.h>
#include <stdio.h>
#include <string.h>
#include <bitStream.h>

/*   Course:    CS 360 Spring 2018
 Assignment:    1
     Author:    Saeed AlSarhi
 */

int main(int argc, char *argv[]){
    // Sequence *s1 = newSequence('a');
    // Sequence *s2 = newSequence('b');
    // Sequence *s3 = copySequenceAppend(s1, 'c');
    // Sequence *s4 = copySequenceAppend(s3, 'c');

    // //outputSequence(s4,fputc,stdout);
    // Dict *dict = newDict(1024);
    // insertIntoDict(dict, s1, 10);
    // insertIntoDict(dict, s2, 25);
    // insertIntoDict(dict, s3, 37);
    // insertIntoDict(dict, s4, 42);

    // int retcode = 0;
    // if (searchDict(dict, s1, &retcode))
    //     printf("Found Code: %i\n", retcode);
    // if (searchDict(dict, s2, &retcode))
    //     printf("Found Code: %i\n", retcode);
    // if (searchDict(dict, s3, &retcode))
    //     printf("Found Code: %i\n", retcode);
    // if (searchDict(dict, s4, &retcode))
    //     printf("Found Code: %i\n", retcode);

    // deleteDictDeep(dict);
    FILE *in = fopen("in.txt", "r");
    FILE *lzw = fopen("tmp.lzw", "w");
    FILE *out = fopen("out.txt", "w");

    lzwEncode(8, 24, fgetc, in, fputc, lzw);
    fclose(lzw);
    FILE *lzw2 = fopen("tmp.lzw", "r");

    lzwDecode(8, 24, fgetc, lzw2, fputc, out);
    fclose(in);
    fclose(out);
    fclose(lzw2);

    //  FILE *out = fopen("in.txt","w");

    // BitStream *bs = openOutputBitStream(fputc,out);
    // for (unsigned int i = 0; i<=16; i++){
    //     outputBits(bs,8 + i,255 + i);
    // }
    // closeAndDeleteBitStream(bs);
    // fclose(out);

    // FILE *in = fopen("in.txt","r");

    // BitStream *bs2 = openInputBitStream(fgetc, in);
    // unsigned int code = 0;
    // for (unsigned int i = 0; i <= 16; i++){
    //     readInBits(bs2, 8 + i, &code);
    //     printf("got: %u\n",code);
    // }
    // closeAndDeleteBitStream(bs2);
    // fclose(in);
}
