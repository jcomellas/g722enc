#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <sndfile.h>
#include <g722_1.h>

#define SAMPLE_SIZE 2
#define OBUFLEN (128 * 1024)
#define IBUFLEN (OBUFLEN / SAMPLE_SIZE)


void usage(int argc, char *argv[])
{
    printf("%s <WAV file> <G7221 file>\n\n"
           "Encode a 16 bit Linear PCM, 16 kHz, mono WAV file into a raw G722.1 file\n", argv[0]);
}


int main(int argc, char *argv[])
{
    int rc = -1;
    int16_t ibuf[IBUFLEN];
    uint8_t obuf[OBUFLEN];
    g722_1_encode_state_t state;

    SNDFILE *isfp;
    SF_INFO isfi;
    FILE *ofp;

    if (argc != 3) {
        usage(argc, argv);
        return -1;
    }

    memset(&isfi, 0, sizeof (isfi));
    isfp = sf_open(argv[1], SFM_READ, &isfi);
    if (!isfp) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        goto input_open_error;
    }

    /* The input file must use Linear PCM encoding at 16 bit, 16 kHz, mono */
    if (!(isfi.format & SF_FORMAT_PCM_16) || isfi.samplerate != 16000 || isfi.channels != 1) {
        fprintf(stderr, "Invalid input file format: must be 16 bit Linear PCM at 16 kHz, mono\n");
        goto format_check_error;
    }

    ofp = fopen(argv[2], "w");
    if (!ofp) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        goto output_open_error;
    }

    g722_1_encode_init(&state, 32000, 16000);

    while (1) {
        int rcount, ocount;

        rcount = sf_read_short(isfp, ibuf, IBUFLEN);

        if (!rcount) {
            rc = 0;
            break;
        }

        ocount = g722_1_encode(&state, obuf, ibuf, rcount);

        if (!ocount) {
            fprintf(stderr, "Error encoding output\n");
            goto encode_error;
        }

        if (fwrite(obuf, sizeof(obuf[0]), ocount, ofp) != ocount) {
            if (ferror(ofp)) {
                fprintf(stderr, "Error writing to %s: %s\n", argv[2], strerror(errno));
                goto write_error;
            }
        }
    }

write_error:
encode_error:
    fclose(ofp);
output_open_error:
format_check_error:
    sf_close(isfp);
input_open_error:
    return rc;
}
