#ifdef RCSID
static char RcsId[] = "@(#)$Revision$";
#endif
/*
$Header$

$Log$
Revision 1.2  1992/07/13 20:18:13  mfolk
Added header to explain what it does.

 * Revision 1.1  1992/07/08  22:07:42  sxu
 * Initial revision
 *
*/
/***************************************************************
**
** This program tests correctness of writing and read datastrings
** and dimension strings.
** To avoid the '\0' inserted by HDstrncpy, compare the first 14
** characters of output and input strings in subroutine compare()
**
****************************************************************/


#include "hdf.h"
#include "dfsd.h"

int number_failed = 0;

int main()
{
    int i, j, err;
    int32 rank;
    int32 dims[2];
    float32 f32[10][10], tf32[10][10];
    char *datalabel, *dataunit, *datafmt, *coordsys;
    char in_datalabel[256], in_dataunit[256], in_datafmt[256],
in_coordsys[256];

    char *dimlabels[2], *dimunits[2], *dimfmts[2];
    char in_dimlabels[2][256], in_dimunits[2][256], in_dimfmts[2][256];

    rank = 2;
    dims[0] = 10;
    dims[1] = 10;
    datalabel  = "Datalabel";
    dataunit   = "Dataunit";
    datafmt    = "Datafmt";
    coordsys   = "coordsys";

    dimlabels[0]  = "c_dim1_label_a";
    dimunits[0]   = "c_dim1_unit_a";
    dimfmts[0]    = "c_dim1_fmt_a";

    dimlabels[1]  = "c_dim2_label_b";
    dimunits[1]   = "c_dim2_unit_b";
    dimfmts[1]    = "c_dim2_fmt_b";


    printf("Creating arrays...\n");

    for (i=0; i<10; i++) {
        for (j=0; j<10; j++) {
            f32[i][j] = (i * 10) + j;   /* range: 0 ~ 4-billion */
        }
    }

    DFSDsetdims(rank, dims);

    /* individual files */
    printf("Testing arrays in individual files...\n");

    err = DFSDsetNT(DFNT_NFLOAT32);
    err = DFSDsetdims(rank, dims);

    err = DFSDsetdatastrs(datalabel, dataunit, datafmt,coordsys);
    err = DFSDsetdimstrs(1, dimlabels[0], dimunits[0], dimfmts[0]);
    err = DFSDsetdimstrs(2, dimlabels[1], dimunits[1], dimfmts[1]);

    err = DFSDadddata("sdstrings.hdf", rank, dims, f32);

    err = DFSDgetdata("sdstrings.hdf", rank, dims, tf32);

    err = DFSDgetdatastrs(in_datalabel, in_dataunit, in_datafmt,
in_coordsys);
    err = DFSDgetdimstrs(1, in_dimlabels[0], in_dimunits[0],
in_dimfmts[0]);
    err = DFSDgetdimstrs(2, in_dimlabels[1], in_dimunits[1],
in_dimfmts[1]);

    compare(datalabel, in_datalabel);
    compare(dataunit, in_dataunit);
    compare(datafmt, in_datafmt);
    compare(coordsys, in_coordsys);

    compare(dimlabels[0], in_dimlabels[0]);
    compare(dimunits[0], in_dimunits[0]);
    compare(dimfmts[0], in_dimfmts[0]);

    compare(dimlabels[1], in_dimlabels[1]);
    compare(dimunits[1], in_dimunits[1]);
    compare(dimfmts[1], in_dimfmts[1]);

    if (number_failed > 0 ) {
        printf("\n\t>>> %d TESTS FAILED <<<\n\n", number_failed);
    }
    else
        printf("\n\t>>> ALL TESTS PASSED <<<\n\n");

}

int compare(outstring, instring)
char *outstring, *instring;
{
    if (0 == strcmp(outstring, instring))
        printf("Test passed for %s\n", outstring);
    else {
        printf(">>> Test failed for %s\n", outstring);
        printf("    Input string =  %s\n", instring);
        number_failed++;
    }
}


