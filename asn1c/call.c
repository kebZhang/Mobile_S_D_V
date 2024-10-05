#include <stdio.h>
#include <sys/types.h>
#include "MyTypes.h"
#include "MyTypes1.h"
 
int main(int ac, char **av) {
    char buf[1024];      /* Temporary buffer      */
    MyTypes_t *t =0;
    MyTypes1_t *t1 =0;
    asn_dec_rval_t rval; /* Decoder return value  */
    asn_dec_rval_t rval1; /* Decoder return value  */
    asn_TYPE_descriptor_t *pduType = NULL;
    FILE *fp;            /* Input file handler    */
    size_t size;         /* Number of bytes read  */
    char *filename;      /* Input file name */
    void *structure = 0;

 
    /* Require a single filename argument */
    if(ac != 2) {
      fprintf(stderr, "Usage: %s <file.ber>\n", av[0]);
      exit(64); /* better, EX_USAGE */
    } else {
      filename = av[1];
    }
 
    /* Open input file as read-only binary */
    fp = fopen(filename, "rb");
    if(!fp) {
      perror(filename);
      exit(66); /* better, EX_NOINPUT */
    }
  
    /* Read up to the buffer size */
    size = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
    if(!size) {
      fprintf(stderr, "%s: Empty or broken\n", filename);
      exit(65); /* better, EX_DATAERR */
    }
 
    /* Decode the input buffer as Rectangle type */
    rval = uper_decode(0, &asn_DEF_MyTypes, (void **)&t,
                                   buf, size, 0, 0);
    rval1 = uper_decode(0, &asn_DEF_MyTypes1, (void **)&t1,
                                   buf+2, size-2, 0, 0);

    // rval = ber_decode(0, &asn_DEF_Rectangle,
    //   (void **)&rectangle, buf, size);
    if(rval.code != RC_OK) {
      fprintf(stderr,
        "%s: Broken A encoding at byte %ld\n",
        filename, (long)rval.consumed);
      exit(65); /* better, EX_DATAERR */
    }
    if(rval1.code != RC_OK) {
      fprintf(stderr,
        "%s: 1 A encoding at byte %ld\n",
        filename, (long)rval.consumed);
      exit(65); /* better, EX_DATAERR */
    }
 
    /* Print the decoded Rectangle type as XML */
    xer_fprint(stdout, &asn_DEF_MyTypes, t);
    xer_fprint(stdout, &asn_DEF_MyTypes1, t1);
 
    return 0; /* Decoding finished successfully */
}
