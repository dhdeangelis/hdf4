#ifdef RCSID
static char RcsId[] = "@(#)$Revision$";
#endif
/*
$Header$

$Log$
Revision 1.2  1992/08/31 16:14:52  chouck
Added Fortran support for calibration tags

 * Revision 1.1  1992/08/25  21:40:44  koziol
 * Initial revision
 *
*/
/*-----------------------------------------------------------------------------
 * File:    dfsdF.c
 * Purpose: C stubs for Fortran SDS routines
 * Invokes: dfsd.c dfkit.c
 * Contents: 
 *  dsgdast:       Call DFSDgetdatastrs to get attributes of data
 *  dsigdis:       Call DFSDgetdimstrs to get attributes of a dimension
 *  dsgdisc:       Call DFSDgetdimscale to get scale for a dimension
 *  dsgrang:       Call DFSDgetmaxmin to get max and min data values
 *  dssdims:       Call DFSDsetdims to set dimensions for subsequent SDGs
 *  dssdisc:       Call DFSDsetdimscale to set scale for subsequent SDGs
 *  dssrang:       Call DFSDsetmaxmin to set max/min values for subsequent SDGs
 *  dsclear:       Call DFSDclear to erase values set for subsequent SDGs
 *  dsslens:       Call DFSDsetlengths to set maximum lengths of string
 *  dsgdiln:       Call DFSDgetdimlen to get lengths of strings for a dimension
 *  dsgdaln:       Call DFSDgetdatalen to get lengths of data strings
 *  dsfirst:       Call DFSDrestart to get SDGs again from beginning of file
 *  dspslc:        Call DFSDIputslice to write slice to file
 *  dseslc:        Call DFSDendslice to end slice writes, write SDG to file
 *  dssnt:         Call DFSDsetNT to set number type
 *  dsgnt:         Call DFSDgetNT to get number type for reading
 *  dsigdim:       Call DFSDgetdims to get dimensions of next SDG
 *  dsigdat:       Call DFSDgetdata to get data values
 *  dsipdat:       Call DFSDIputdata to write SDG to new file
 *  dsiadat:       Call DFSDIputdata to append SDG to existing file
 *  dsigslc:       Call DFSDIgetslice to get slice from file
 *  dsisslc:       Call DFSDstartslice to set up to write slice
 *  dslref:        Call DFSDlastref to get ref of last SDS accessed
 *  dsinum:        Call DFSDnumber to get number of SDG in the file
 *  dfsdgetdatastrs_:Call DFSDgetdatastrs to get attributes of data
 *  dfsdgetdimscale_:Call DFSDgetdimscale to get scale for a dimension
 *  dfsdgetrange_:  Call DFSDgetmaxmin to get max and min data values
 *  dfsdsetdims_:   Call DFSDsetdims to set dimensions for subsequent SDGs
 *  dfsdsetdimscale_:Call DFSDsetdimscale to set scale for subsequent SDGs
 *  dfsdsetrange_:  Call DFSDsetmaxmin to set max/min values for subsequent SDGs
 *  dfsdclear_:     Call DFSDclear to erase values set for subsequent SDGs
 *  dfsdsetlengths_:Call DFSDsetlengths to set maximum lengths of string
 *  dfsdgetdimlen_: Call DFSDgetdimlen to get lengths of strings for a dimension
 *  dfsdgetdatalen_:Call DFSDgetdatalen to get lengths of data strings
 *  dfsdrestart_:   Call DFSDrestart to get SDGs again from beginning of file
 *  dfsdputslice_:  Call DFSDIputslice to write slice to file
 *  dfsdendslice_:  Call DFSDendslice to end slice writes, write SDG to file
 *  dfsdsetnt_:     Call DFSDsetNT to set number type
 *  dfsdgetnt_:	    Call DFSDgetNT to get number type
 *  dfsdlastref_:   Call DFSDlastref to get ref of last SDS accessed
 * Remarks: no C stubs needed for the put string routines, only Fortran stubs
 *---------------------------------------------------------------------------*/

#include "dfsd.h"

/*-----------------------------------------------------------------------------
 * Name:    dsgdisc
 * Purpose: Call DFSDgetdimscale to get scale for a dimension
 * Inputs:  dim: dimension to get attributes for
 *          maxsize: size of scale array
 *          scale: array to return scale in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdimscale
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsgdisc(int *dim, int32 *maxsize, void *scale)
#else
ndsgdisc(dim, maxsize, scale)
    int *dim;
    int32 *maxsize;
    void *scale;
#endif /* PROTOTYPE */
{
    intn rank, cdim, ret;
    intn isndg;

    ret = DFSDIisndg(&isndg);
    if (isndg) 	{
        ret = DFSDIgetrrank(&rank);
        if (rank < *dim)
            return FAIL;
    	cdim = rank - *dim + 1;
    }
    else cdim = *dim;

    return(DFSDgetdimscale(cdim, *maxsize, scale));
}


/*-----------------------------------------------------------------------------
 * Name:    dsgrang
 * Purpose: Call DFSDgetrange to get maximum and minimum data values
 * Inputs:  pmax: float to return maximum in
 *          pmin: float to return minimum in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetrange
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsgrang(void *pmax, void *pmin)
#else
ndsgrang(pmax, pmin)
    void *pmax, *pmin;
#endif /* PROTOTYPE */
{
    return(DFSDgetrange(pmax, pmin));
}


/*-----------------------------------------------------------------------------
 * Name:    dssdims
 * Purpose: Call DFSDsetdims to set dimensions for subsequent SDGs
 * Inputs:  rank: no of dimensions of SDG
 *          dimsizes: array containing dimensions of SDG
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetdims
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndssdims(int32 *rank, int32 dimsizes[])
#else
ndssdims(rank, dimsizes)
    int32 *rank;
    int32 dimsizes[];
#endif /* PROTOTYPE */
{

    int32 i, *cdims, *p;
    int ret;

    p = (int32 *)HDgetspace((uint32)((*rank)*sizeof(int32)));
    if (p == NULL) return FAIL;
    cdims = p;
    for (i=1; i <=  *rank ; i++)	{
        *p = dimsizes[*rank - i];
        p++;
    }
   
    ret = DFSDsetdims((intn)*rank, cdims);
    cdims = HDfreespace((uint32 *)cdims);
    if (cdims != NULL) return FAIL;
    return(ret);
    
}


/*-----------------------------------------------------------------------------
 * Name:    dssdisc
 * Purpose: Call DFSDsetdimscale to set scales for subsequent SDGs
 * Inputs:  dim: dimension to set scale for
 *          dimsize: size of array scale
 *          scale: array of scale values
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetdimscale
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndssdisc(int *dim, int32 *dimsize, void *scale)
#else
ndssdisc(dim, dimsize, scale)
    int *dim;
    int32 *dimsize;
    void *scale;
#endif /* PROTOTYPE */
{

    int cdim, ret;
    intn rank;

    ret = DFSDIgetwrank(&rank);
    if (rank < *dim) return FAIL;
    cdim = rank - *dim + 1;

    return(DFSDsetdimscale(cdim, *dimsize, scale));
}


/*-----------------------------------------------------------------------------
 * Name:    dssrang
 * Purpose: Call DFSDsetrange to set max and min values for this SDG
 * Inputs:  max, min: max and min data values
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetrange
 * Remarks: Max and Min are set only for next SDG, reset to NULL after
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndssrang(void *max, void *min)
#else
ndssrang(max, min)
    void *max, *min;
#endif /* PROTOTYPE */
{

    return(DFSDsetrange(max, min));
}


/*-----------------------------------------------------------------------------
 * Name:    dsclear
 * Purpose: Call DFSDclear to erase values set for subsequent SDGs
 * Inputs:  none
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDclear
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsclear(void)
#else
ndsclear()
#endif /* PROTOTYPE */
{

    return(DFSDclear());
}


/*-----------------------------------------------------------------------------
 * Name:    dsslens
 * Purpose: Call DFSDsetlengths to set max lengths of strings
 * Inputs:  maxlen_label, maxlen_unit, maxlen_format, maxlen_coordsys: max lens
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetlengths
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsslens(int *maxlen_label, int *maxlen_unit, int *maxlen_format,
	 int *maxlen_coordsys)
#else
ndsslens(maxlen_label, maxlen_unit, maxlen_format, maxlen_coordsys)
    int *maxlen_label, *maxlen_unit, *maxlen_format, *maxlen_coordsys;
#endif /* PROTOTYPE */
{

    return(DFSDsetlengths(*maxlen_label, *maxlen_unit, *maxlen_format,
                                                        *maxlen_coordsys));
}


/*-----------------------------------------------------------------------------
 * Name:    dsgdiln
 * Purpose: Call DFSDgetdimlen to get actual lengths of strings
 * Inputs:  dim: dimension to get lengths for
 *          llabel, lunit, lformat: integers to return lengths of each string in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdimlen
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsgdiln(int *dim, int *llabel, int *lunit, int *lformat)
#else
ndsgdiln(dim, llabel, lunit, lformat)
    int *dim, *llabel, *lunit, *lformat;
#endif /* PROTOTYPE */
{

    intn rank, cdim, ret;
    intn isndg;

    ret = DFSDIisndg(&isndg);
    if (isndg) 	{
        ret = DFSDIgetrrank(&rank);
        if (rank < *dim)
            return FAIL;
    	cdim = rank - *dim + 1;
    }
    else cdim = *dim;

    return(DFSDgetdimlen(cdim, llabel, lunit, lformat));
}


/*-----------------------------------------------------------------------------
 * Name:    dsgdaln
 * Purpose: Call DFSDgetdatalen to get actual lengths of strings
 * Inputs:  llabel, lunit, lformat, lcoordsys: integers to return lengths in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdatalen
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsgdaln(int *llabel, int *lunit, int *lformat, int *lcoordsys)
#else
ndsgdaln(llabel, lunit, lformat, lcoordsys)
    int *llabel, *lunit, *lformat, *lcoordsys;
#endif /* PROTOTYPE */
{

    return(DFSDgetdatalen(llabel, lunit, lformat, lcoordsys));
}


/*----------------------------------------------------------------------------- 
 * Name:    dsfirst * Purpose: Call DFSDrestart to get SDGs again from the beginning
 * Inputs:  none
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDrestart
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsfirst(void)
#else
ndsfirst()
#endif /* PROTOTYPE */
{

    return(DFSDrestart());
}


/*-----------------------------------------------------------------------------
 * Name:    dspslc
 * Purpose: Call DFSDIputslice to write slice to file 
 * Inputs:  windims: array of size rank, containing size of slice 
 *          data: array containing slice 
 *          dims: dimensions of array data 
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIputslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndspslc(int32 windims[], void *data, int32 dims[])
#else
ndspslc(windims, data, dims)
    int32 windims[];
    void  *data;
    int32 dims[];
#endif /* PROTOTYPE */
{

    int32 *cdims, *cwindims, *p, *wp;
    intn i, ret, rank;

    ret = DFSDIgetwrank(&rank);
    wp = (int32 *)HDgetspace((uint32)(rank*sizeof(int32)));
    if (wp == NULL) return FAIL;
    cwindims = wp;
    p = (int32 *)HDgetspace((uint32)(rank*sizeof(int32)));
    if (p == NULL) return FAIL;
    cdims = p;
    for (i=1; i <=  rank ; i++)	{  /* reverse dims & windims */
        *p = dims[rank - i];
        p++;
        *wp = windims[rank - i];
        wp++;
    }
   
    ret = DFSDIputslice(cwindims, data, cdims, 1);
    cdims = HDfreespace((uint32 *)cdims);
    if (cdims != NULL) return FAIL;
    cwindims = HDfreespace((uint32 *)cwindims);
    if (cwindims != NULL) return FAIL;
    return(ret);
}


/*-----------------------------------------------------------------------------
 * Name:    dseslc
 * Purpose: Call DFSDIendslice to finish slice writes and write out SDG
 * Inputs:  none
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIendslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndseslc(void)
#else
ndseslc()
#endif /* PROTOTYPE */
{

    return(DFSDIendslice(1));
}


/*-----------------------------------------------------------------------------
 * Name:    dssnt
 * Purpose: Call DFSDsetNT to set number type for subsequent calls to
            DFSDputdata, DFSDadddata, DFSDsetdimscales.
 * Inputs:  numbertype
 * Returns: 0 on success, FAIL on failure with error set
 * Users:   HDF Fortran programmers
 * Method:  Invokes DFSDsetNT
 * Remarks: 0 specifies default value
 *---------------------------------------------------------------------------*/

        FRETVAL(int)
#ifdef PROTOTYPE
ndssnt(int32 *numbertype)
#else
ndssnt(numbertype)
    int32 *numbertype;
#endif /* PROTOTYPE */
{

    return(DFSDsetNT(*numbertype));
}

/*----------------------------------------------------------------------------
 * Name:    dsgnt
 * Purpose: Call DFSDgetNT to get number type for subsequent calls 
 * Inputs:  pnumbertype
 * Returns: 0 on success, FAIL on failure with error set
 * Users:   HDF Fortran programmers
 * Method:  Invokes DFSDgetNT
 * Remarks: 0 specifies default value
 *---------------------------------------------------------------------------*/

        FRETVAL(int)
#ifdef PROTOTYPE
ndsgnt(int32 *pnumbertype)
#else
ndsgnt(pnumbertype)
    int32 *pnumbertype;
#endif /* PROTOTYPE */
{

    return(DFSDgetNT(pnumbertype));
}


/*-----------------------------------------------------------------------------
 * Name:    dsigdim
 * Purpose: Call DFSDgetdims to get dimensions of next SDG
 * Inputs:  filename: name of HDF file
 *          prank: integer to return rank in
 *          sizes: array to return dimensions in
 *          maxrank: dimension of array sizes
 *          lenfn: length of filename
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   Fortran stub routine
 * Invokes: DFSDgetdims
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsigdim(_fcd filename, int32 *prank, int32 sizes[], int32 *maxrank,
	 int32 *lenfn)
#else
ndsigdim(filename, prank, sizes, maxrank, lenfn)
    _fcd filename;
    int32 *prank, sizes[], *maxrank, *lenfn;
#endif /* PROTOTYPE */
{
    char *fn;
    int32 i, tmp, isndg;
    int ret;

    fn = HDf2cstring(filename, (intn)*lenfn);
    ret = DFSDgetdims(fn,(intn *) prank, sizes, (intn) *maxrank);
    DFSDIisndg(&isndg);
    if (isndg) {
	for (i=0; i<((int32)*prank)/2; i++)	{
	    tmp = sizes[i];
	    sizes[i] = sizes[(int32)*prank -i -1];
	    sizes[(int32)*prank -i -1] = tmp;
	}
    }
    HDfreespace(fn);
    return ret;
}


/*-----------------------------------------------------------------------------
 * Name:    dsigdat
 * Purpose: Call DFSDgetdata to get data values
 * Inputs:  filename: name of HDF file
 *          rank: no of dimensions in array data
 *          maxsizes: array containing dimensions of the array data
 *          data: array to return the data in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIgetdata,DFSDIrefresh,DFSDIisndg
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsigdat(_fcd filename, int32 *rank, int32 maxsizes[], void *data,
	 int32 *fnlen)
#else
ndsigdat(filename, rank, maxsizes, data, fnlen)
    _fcd filename;
    int32 *rank, maxsizes[], *fnlen;
    void *data;
#endif /* PROTOTYPE */
{
    int32 i, isndg;
    int ret;
    char *fn;
    int32 *p, *cmaxsizes;
    
    fn = HDf2cstring(filename, (intn) *fnlen);
      /* if DFSDgetdims has not be called call DFSDIsdginfo to */
      /* refresh Readsdg       */
    if (DFSDIrefresh(fn)<0) return FAIL;
    ret = DFSDIisndg(&isndg);
    if (isndg)	{
    	p = (int32 *)HDgetspace((uint32)((*rank)*sizeof(int32)));
    	if (p == NULL) return FAIL;
        cmaxsizes = p;

    	for (i=1; i <=  *rank ; i++)	{
            *p = maxsizes[*rank - i];
            p++;
        }
    	ret = DFSDIgetdata(fn, (intn)*rank, cmaxsizes, data, 1);
    	p = cmaxsizes = HDfreespace((uint32 *)cmaxsizes);
    	if (cmaxsizes != NULL) return FAIL;
    }
    else	
        ret = DFSDIgetdata(fn, (intn)*rank, maxsizes, data, 1); /* 1==FORTRAN */
    HDfreespace(fn);
    return ret;
}


/*-----------------------------------------------------------------------------
 * Name:    dsipdat
 * Purpose: Call DFSDIputdata to write SDG to new file
 * Inputs:  filename: name of HDF file
 *          rank: no of dimensions of array data
 *          dimsizes: array containing size of each dimension of array data
 *          data: array containing data values
 *          fnlen: length of string filename
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIputdata
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsipdat(_fcd filename, int32 *rank, int32 dimsizes[], void *data,
	 int32 *fnlen)
#else
ndsipdat(filename, rank, dimsizes, data, fnlen)
    _fcd filename;
    int32 *rank;
    int32 dimsizes[];
    void *data;
    int32 *fnlen;
#endif /* PROTOTYPE */
{
    char *fn;
    int32 i, *cdims, *p;
    int ret;

	/* reverse the dimsizes first  */
    p = (int32 *)HDgetspace((uint32)((*rank)*sizeof(int32)));
    if (p == NULL) return FAIL;
    cdims = p;
    for (i=1; i <=  *rank ; i++)	{
        *p = dimsizes[*rank - i];
        p++;
    }
    fn = HDf2cstring(filename, (intn) *fnlen);

    /* 0, 1 specify create mode, called from FORTRAN program */
    /* In HDF3.2 .hdf files, data and dimsizes are in C order  */
    ret = DFSDIputdata(fn, (intn)*rank, dimsizes, data, 0, 1);
    HDfreespace(fn);
    cdims = HDfreespace((uint32 *)cdims);
    if (cdims != NULL) return FAIL;

    return(ret);
}


/*-----------------------------------------------------------------------------
 * Name:    dsiadat
 * Purpose: Call DFSDIputdata to append SDG to existing file
 * Inputs:  filename: name of HDF file
 *          rank: no of dimensions of array data
 *          dimsizes: array containing size of each dimension of array data
 *          data: array containing data values
 *          fnlen: length of string filename
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIputdata
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsiadat(_fcd filename, int32 *rank, int32 dimsizes[], void *data,
	 int32 *fnlen)
#else
ndsiadat(filename, rank, dimsizes, data, fnlen)
    _fcd filename;
    int32 *rank;
    int32 dimsizes[];
    void *data;
    int32 *fnlen;
#endif /* PROTOTYPE */     
{
    char *fn;
    int32 i,  *cdims, *p;
    int ret;

    /* reverse the dimsizes first  */
    p = (int32 *)HDgetspace((uint32)((*rank)*sizeof(int32)));
    if (p == NULL) return FAIL;
    cdims = p;
    for (i=1; i <=  *rank ; i++) {
    	*p = dimsizes[*rank - i];
    	p++;
    }
    fn = HDf2cstring(filename, (intn) *fnlen);
   
    /* 1, 1 specify create mode, called from FORTRAN program */
    /* In HDF3.2 .hdf files, data and dimsizes are in C order  */
    ret = DFSDIputdata(fn, (intn)*rank, cdims, data, 1, 1);
    HDfreespace(fn);
    cdims = HDfreespace((uint32 *)cdims);
    if (cdims != NULL) return FAIL;
    return(ret);
}


/*-----------------------------------------------------------------------------
 * Name:    dsigslc
 * Purpose: Call DFSDIgetslice to read slice from file
 * Inputs:  filename: name of HDF file
 *          winst: array of size = rank of data, containing start of slice
 *          windims: array of size rank, containing end of slice
 *          data: array for returning slice
 *          ndims: no of dims of array data
 *          dims: dimensions of array data
 *          fnlen: length of filename
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIgetslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsigslc(_fcd filename, int32 winst[], int32 windims[], void *data,
	 int32 dims[], int *fnlen)
#else
ndsigslc(filename, winst, windims, data, dims, fnlen)
    _fcd filename;
    int32 winst[], windims[];
    int32 dims[];
    void *data;
    int *fnlen;
#endif /* PROTOTYPE */
{
    char *fn;
    int ret;
    intn rank,i;
    int32 isndg, *cdims, *cwindims, *cwinst, *p, *wp, *wsp;

    fn = HDf2cstring(filename, *fnlen);
   
      /* if DFSDgetdims has not be called call DFSDIsdginfo to */
      /* refresh Readsdg       */
    if (DFSDIrefresh(fn)<0) return FAIL;
 
    ret = DFSDIisndg(&isndg);
    if (isndg)	{
	ret = DFSDIgetrrank(&rank);
    	p = (int32 *)HDgetspace((uint32)(rank*sizeof(int32)));
    	if (p == NULL) return FAIL;
        cdims = p;
    	wp = (int32 *)HDgetspace((uint32)(rank*sizeof(int32)));
    	if (wp == NULL) return FAIL;
        cwindims = wp;
    	wsp = (int32 *)HDgetspace((uint32)(rank*sizeof(int32)));
    	if (wsp == NULL) return FAIL;
        cwinst = wsp;

    	for (i=1; i <=  rank ; i++)	{
            *p = dims[rank - i];
            p++;
            *wp = windims[rank - i];
            wp++;
            *wsp = winst[rank - i];
            wsp++;
        }
    	ret = DFSDIgetslice(fn, cwinst, cwindims, data, cdims, 1);
    	p = cdims = HDfreespace((uint32 *)cdims);
    	if (cdims != NULL) return FAIL;
    	wp = cwindims = HDfreespace((uint32 *)cwindims);
    	if (cwindims != NULL) return FAIL;
    	wsp = cwinst = HDfreespace((uint32 *)cwinst);
    	if (cwinst != NULL) return FAIL;
    }
    else	
    	ret = DFSDIgetslice(fn, winst, windims, data, dims, 1);
    HDfreespace(fn);
    return(ret);
}


/*-----------------------------------------------------------------------------
 * Name:    dsisslc
 * Purpose: Call DFSDstartslice to set up to write slice
 * Inputs:  filename: name of HDF file
 *          fnlen: length of filename
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDstartslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsisslc(_fcd filename, int *fnlen)
#else
ndsisslc(filename, fnlen)
    _fcd filename;
    int *fnlen;
#endif /* PROTOTYPE */
{
    char *fn;
    int ret;

    fn = HDf2cstring(filename, *fnlen);
    ret = DFSDstartslice(fn);
    HDfreespace(fn);
    return(ret);
}

/*-----------------------------------------------------------------------------
 * Name:    dsirref
 * Purpose: Call DFSDreadref to set up next ref to read
 * Inputs:  filename: name of HDF file
 *	    ref: next ref to read
 *          fnlen: length of filename
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDstartslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsirref(_fcd filename, int32 *ref, int *fnlen)
#else
ndsirref(filename, ref, fnlen)
    _fcd filename;
    int32 *ref;
    int *fnlen;
#endif /* PROTOTYPE */
{
    char *fn;
    int ret;

    fn = HDf2cstring(filename, *fnlen);
    ret = DFSDreadref(fn, (uint16) *ref);
    HDfreespace(fn);
    return(ret);
}

/*-----------------------------------------------------------------------------
 * Name:    dslref
 * Purpose: Return last ref written or read
 * Inputs:  none
 * Globals: Lastref
 * Returns: ref on success, -1 on error with DFerror set
 * Users:   HDF users, utilities, other routines
 * Invokes: DFANlastref
 * Remarks: none
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE  
ndslref(void)
#else
ndslref()
#endif /* PROTOTYPE */
{
    return(DFSDlastref());
}


/*-----------------------------------------------------------------------------
 * Name:    dsinum
 * Purpose: Return number of SDGs in the file
 * Inputs:  filename: name of file
 *          len: length of Fortran string filename
 * Returns: number of SDGs on success, -1 on failure with DFerror set
 * Users:   dsnum, dfsdnumber
 * Invokes: DFSDnumber, HDf2cstring
 * Method:  convert string, call DFSDnumber
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE  
ndsinum(_fcd filename, int32 *len)
#else
ndsinum(filename, len)
_fcd filename;
int32 *len;
#endif /* PROTOTYPE */
{
    char *cname;
    intn status;

    cname = HDf2cstring(filename, (intn) *len);
    status = DFSDnumber(cname);
    HDfreespace(cname);

    return(status);
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdgetdatastrs
 * Purpose: Call DFSDgetdatastrs to get the data attributes
 * Inputs:  label, unit, format, coordsys: strings to return attributes in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdatastrs
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetdatastrs(_fcd label, _fcd unit, _fcd format, _fcd coordsys)
#else
ndfsdgetdatastrs(label, unit, format, coordsys)
    _fcd label, unit, format, coordsys;
#endif /* PROTOTYPE */
{

    return(DFSDgetdatastrs((char *)_fcdtocp(label), (char *)_fcdtocp(unit),
			 (char *)_fcdtocp(format), (char *)_fcdtocp(coordsys)));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdgetdimstrs
 * Purpose: Call DFSDgetdimstrs to get attributes of a dimension
 * Inputs:  label, unit, format: strings to return attributes in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdimstrs
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetdimstrs(int *dim, _fcd label, _fcd unit, _fcd format)
#else
ndfsdgetdimstrs(dim, label, unit, format)
    int *dim;
    _fcd label, unit, format;
#endif /* PROTOTYPE */
{

    int32 isndg; 
    intn rank, cdim, ret;

    ret = DFSDIisndg(&isndg);
    if (isndg) 	{
        ret = DFSDIgetrrank(&rank);
    	if (rank < *dim) return FAIL;
    	cdim = rank - *dim + 1;
    }
    else cdim = *dim;

    return(DFSDgetdimstrs(cdim, (char *)_fcdtocp(label),
			  (char *)_fcdtocp(unit), (char *)_fcdtocp(format)));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdgetdimscale
 * Purpose: Call DFSDgetdimscale to get scale for a dimension
 * Inputs:  dim: dimension to get attributes for
 *          maxsize: size of scale array
 *          scale: array to return scale in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdimscale
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetdimscale(int *dim, int32 *maxsize, void *scale)
#else
ndfsdgetdimscale(dim, maxsize, scale)
    int *dim;
    int32 *maxsize;
    void *scale;
#endif /* PROTOTYPE */
{

    int32 isndg;
    intn  rank, cdim, ret;

    ret = DFSDIisndg(&isndg);
    if (isndg) 	{
        ret = DFSDIgetrrank(&rank);
    	if (rank < *dim) return FAIL;
    	cdim = rank - *dim + 1;
    }
    else cdim = *dim;

    return(DFSDgetdimscale(cdim, *maxsize, scale));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdgetrange
 * Purpose: Call DFSDgetrange to get maximum and minimum data values
 * Inputs:  pmax: float to return maximum in
 *          pmin: float to return minimum in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetrange
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetrange(void *pmax, void *pmin)
#else
ndfsdgetrange(pmax, pmin)
    void *pmax, *pmin;
#endif /* PROTOTYPE */
{
    return(DFSDgetrange(pmax, pmin));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdsetdims
 * Purpose: Call DFSDsetdims to set dimensions for subsequent SDGs
 * Inputs:  rank: no of dimensions of SDG
 *          dimsizes: array containing dimensions of SDG
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetdims
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdsetdims(int32 *rank, int32 dimsizes[])
#else
ndfsdsetdims(rank, dimsizes)
    int32 *rank;
    int32 dimsizes[];
#endif /* PROTOTYPE */
{

    int32 i, *cdims, *p;
    int ret;

    p = (int32 *)HDgetspace((uint32)((*rank)*sizeof(int32)));
    if (p == NULL) return FAIL;
    cdims = p;
    for (i=1; i <=  *rank ; i++)	{
        *p = dimsizes[*rank - i];
        p++;
    }
   
    ret = DFSDsetdims((intn)*rank, cdims);
    cdims = HDfreespace((uint32 *)cdims);
    if (cdims != NULL) return FAIL;
    return(ret);
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdsetdimscale
 * Purpose: Call DFSDsetdimscale to set scales for subsequent SDGs
 * Inputs:  dim: dimension to set scale for
 *          dimsize: size of array scale
 *          scale: array of scale values
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetdimscale
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdsetdimscale(int *dim, int32 *dimsize, void *scale)
#else
ndfsdsetdimscale(dim, dimsize, scale)
    int *dim;
    int32 *dimsize;
    void *scale;
#endif /* PROTOTYPE */
{

    intn  rank, cdim, ret;

    ret = DFSDIgetwrank(&rank);
    if (rank < *dim) return FAIL;
    cdim = rank - *dim + 1;

    return(DFSDsetdimscale(cdim, *dimsize, scale));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdsetrange
 * Purpose: Call DFSDsetrange to set max and min values for this SDG
 * Inputs:  max, min: max and min data values
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetrange
 * Remarks: Max and Min are set only for next SDG, reset to NULL after
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdsetrange(void *max, void *min)
#else
ndfsdsetrange(max, min)
    void *max, *min;
#endif /* PROTOTYPE */
{

    return(DFSDsetrange(max, min));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdclear
 * Purpose: Call DFSDclear to erase values set for subsequent SDGs
 * Inputs:  none
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDclear
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdclear(void)
#else
ndfsdclear()
#endif /* PROTOTYPE */
{

    return(DFSDclear());
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdsetlengths
 * Purpose: Call DFSDsetlengths to set max lengths of strings
 * Inputs:  maxlen_label, maxlen_unit, maxlen_format, maxlen_coordsys: max lens
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDsetlengths
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdsetlengths(int *maxlen_label, int *maxlen_unit, int *maxlen_format,
		int *maxlen_coordsys)
#else
ndfsdsetlengths(maxlen_label, maxlen_unit, maxlen_format, maxlen_coordsys)
    int *maxlen_label, *maxlen_unit, *maxlen_format, *maxlen_coordsys;
#endif /* PROTOTYPE */
{

    return(DFSDsetlengths(*maxlen_label, *maxlen_unit, *maxlen_format,
                                                        *maxlen_coordsys));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdgetdimlen
 * Purpose: Call DFSDgetdimlen to get actual lengths of strings
 * Inputs:  dim: dimension to get lengths for
 *         llabel, lunit, lformat: integers to return lengths of each string in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdimlen
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetdimlen(int* dim, int *llabel, int *lunit, int *lformat)
#else
ndfsdgetdimlen(dim, llabel, lunit, lformat)
    int *dim, *llabel, *lunit, *lformat;
#endif /* PROTOTYPE */
{

    int32 isndg;
    intn  rank, cdim, ret;

    ret = DFSDIisndg(&isndg);
    if (isndg) 	{
        ret = DFSDIgetrrank(&rank);
    	if (rank < *dim) return FAIL;
    	cdim = rank - *dim + 1;
    }
    else cdim = *dim;

    return(DFSDgetdimlen(cdim, llabel, lunit, lformat));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdgetdatalen
 * Purpose: Call DFSDgetdatalen to get actual lengths of strings
 * Inputs:  llabel, lunit, lformat, lcoordsys: integers to return lengths in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdatalen
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetdatalen(int *llabel, int *lunit, int *lformat, int *lcoordsys)
#else
ndfsdgetdatalen(llabel, lunit, lformat, lcoordsys)
    int *llabel, *lunit, *lformat, *lcoordsys;
#endif /* PROTOTYPE */
{

    return(DFSDgetdatalen(llabel, lunit, lformat, lcoordsys));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdrestart
 * Purpose: Call DFSDrestart to get SDGs again from the beginning
 * Inputs:  none
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDrestart
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdrestart(void)
#else
ndfsdrestart()
#endif /* PROTOTYPE */
{

    return(DFSDrestart());
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdputslice
 * Purpose: Call DFSDIputslice to write slice to file
 * Inputs:  winst: array of size = rank of data, containing start of slice
 *          windims: array of size rank, containing end of slice
 *          data: array containing slice
 *          dims: dimensions of array data
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIputslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdputslice(int32 windims[], void *data, int32 dims[])
#else
ndfsdputslice(windims, data, dims)
    int32 windims[];
    void *data;
    int32 dims[];
#endif /* PROTOTYPE */
{
    intn ret, rank, i;
    int32 *cdims, *cwindims, *p, *wp;

    ret = DFSDIgetwrank(&rank);
    wp = (int32 *)HDgetspace((uint32)((rank)*sizeof(int32)));
    if (wp == NULL) return FAIL;
    cwindims = wp;
    p = (int32 *)HDgetspace((uint32)((rank)*sizeof(int32)));
    if (p == NULL) return FAIL;
    cdims = p;
    for (i=1; i <=  rank ; i++)	{  /* reverse dims & windims */
        *p = dims[rank - i];
        p++;
        *wp = windims[rank - i];
        wp++;
    }
   
    ret = DFSDIputslice(cwindims, data, cdims, 1);
    cdims = HDfreespace((uint32 *)cdims);
    if (cdims != NULL) return FAIL;
    cwindims = HDfreespace((uint32 *)cwindims);
    if (cwindims != NULL) return FAIL;
    return(ret);
}

/*-----------------------------------------------------------------------------
 * Name:    dfsdendslice
 * Purpose: Call DFSDendslice to finish slice writes and write out SDG
 * Inputs:  none
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDIendslice
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdendslice(void)
#else
ndfsdendslice()
#endif /* PROTOTYPE */
{

    return(DFSDIendslice(1));
}


/*-----------------------------------------------------------------------------
 * Name:    dfsdsetnt
 * Purpose: Call DFSDsetNT to set number type for subsequent calls to
 *          DFSDputdata, DFSDadddata, DFSDsetdimscales.
 * Inputs:  numbertype
 * Returns: 0 on success, FAIL on failure with error set
 * Users:   HDF Fortran programmers
 * Method:  Invokes DFSDsetNT
 * Remarks: 0 specifies default value
 *---------------------------------------------------------------------------*/

        FRETVAL(int)
#ifdef PROTOTYPE
ndfsdsetnt(int32 *numbertype)
#else
ndfsdsetnt(numbertype)
    int32 *numbertype;
#endif /* PROTOTYPE */
{

    return(DFSDsetNT(*numbertype));
}

/*-----------------------------------------------------------------------------
 * Name:    dfsdgetnt
 * Purpose: Call DFSDgetNT to get number type for subsequent calls 
 * Inputs:  pnumbertype
 * Returns: 0 on success, FAIL on failure with error set
 * Users:   HDF Fortran programmers
 * Method:  Invokes DFSDgetNT
 * Remarks: 0 specifies default value
 *---------------------------------------------------------------------------*/

        FRETVAL(int)
#ifdef PROTOTYPE
ndfsdgetnt(int32 *pnumbertype)
#else
ndfsdgetnt(pnumbertype)
    int32 *pnumbertype;
#endif /* PROTOTYPE */
{

    return(DFSDgetNT(pnumbertype));
}

/*-----------------------------------------------------------------------------
 * Name:    dfsdlastref
 * Purpose: Return last ref written or read
 * Inputs:  none
 * Globals: Lastref
 * Returns: ref on success, -1 on error with DFerror set
 * Users:   HDF users, utilities, other routines
 * Invokes: DFANlastref
 * Remarks: none
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndfsdlastref(void)
#else
ndfsdlastref()
#endif /* PROTOTYPE */
{
    return(DFSDlastref());
}

/*-----------------------------------------------------------------------------
 * Name:    dsisdis
 * Purpose: For the given dimension, set label, unit, format
 *          This routine needs to be called once for each dimension whose 
 *          values the user wants to set.
 * Inputs:  dim: the dimension that this info applies to
 *          label: label to be used to describe this dimension
 *          unit: units for dimension
 *          format: format to be used in displaying
 *          llabel, lunit, lformat: lengths of corresponding strings
 * Globals: 
 * Returns: 0 on success, FAIL on failure with error set
 * Users:   HDF users, utilities, other routines
 * Invokes: DFSDIsetdimstr
 * Method:  
 *---------------------------------------------------------------------------*/

FRETVAL(int32)
#ifdef PROTOTYPE
ndsisdis(int *dim, _fcd flabel, _fcd funit, _fcd fformat, 
     int *llabel, int *lunit, int *lformat)
#else
ndsisdis(dim, flabel, funit, fformat, llabel, lunit, lformat)
    int *dim;
    _fcd flabel, funit, fformat;
    int *llabel, *lunit, *lformat;
#endif /* PROTOTYPE */
{
    char *label  =  HDf2cstring(flabel, *llabel);
    char *unit   =  HDf2cstring(funit, *lunit);  
    char *format =  HDf2cstring(fformat, *lformat);
    int32 status, isndg;
    intn rank, cdim;

    status = DFSDIgetwrank(&rank);

    if (rank < *dim) return FAIL;
    cdim = rank - *dim + 1;
    
    status = DFSDIsetdimstrs(cdim, label, unit, format);

    HDfreespace(label);
    HDfreespace(unit);
    HDfreespace(format);

    return status;

}

/*-----------------------------------------------------------------------------
 * Name:    dsigdis
 * Purpose: Call DFSDgetdimstrs to get attributes of a dimension
 * Inputs:  label, unit, format: strings to return attributes in
 * Returns: 0 on success, -1 on failure with DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdimstrs
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsigdis(int *dim, _fcd label, _fcd unit, _fcd format, int32 *llabel, 
         int32 *lunit, int32 *lformat)
#else
ndsigdis(dim, label, unit, format, llabel, lunit, lformat)
     int *dim;
     _fcd label, unit, format;
     int32 *llabel, *lunit, *lformat;
#endif /* PROTOTYPE */
{
    char *ilabel, *iunit, *iformat;
    intn rank, cdim, ret;
    intn isndg, status;

    ret = DFSDIisndg(&isndg);
    if (isndg) 	{
        ret = DFSDIgetrrank(&rank);
    	if (rank < *dim) return FAIL;
    	cdim = rank - *dim + 1;
    }
    else cdim = *dim;

    iunit = ilabel = iformat = NULL;

    if(*llabel)  ilabel  = (char *) HDgetspace((uint32)*llabel + 1);
    if(*lunit)   iunit   = (char *) HDgetspace((uint32)*lunit + 1);
    if(*lformat) iformat = (char *) HDgetspace((uint32)*lformat + 1);

    status = DFSDgetdimstrs(cdim, ilabel, iunit, iformat);

    HDpackFstring(ilabel,  _fcdtocp(label),  *llabel);
    HDpackFstring(iunit,   _fcdtocp(unit),   *lunit);
    HDpackFstring(iformat, _fcdtocp(format), *lformat);

    if(ilabel)  HDfreespace(ilabel);
    if(iunit)   HDfreespace(iunit);
    if(iformat) HDfreespace(iformat);

    return status;
}

/*-----------------------------------------------------------------------------
 * Name:    DFSDIsetdatastrs()
 * Purpose: Set label, unit and format for displaying subsequent SDGs
 * Inputs:  label: label to be used to describe data
 *          unit: unit corresponding to data values
 *          format: format to be used in displaying data values
 *          coordsys: type of coordinate system
 * Globals: Writesdg, Ref
 * Returns: 0 on success, FAIL on failure with error set
 * Users:   HDF Fortran stubs
 * Invokes: DFSDIsetdatastrs
 * Method:  Stores values in global structure Writesdg
 * Remarks: 
 *---------------------------------------------------------------------------*/
#ifdef PROTOTYPE
ndsisdas(_fcd flabel, _fcd funit, _fcd fformat, _fcd fcoordsys, int *isfortran,
     int *llabel, int *lunit, int *lformat, int *lcoordsys)
#else
ndsisdas(flabel, funit, fformat, fcoordsys, isfortran, llabel, lunit,
     lformat, lcoordsys)
    _fcd flabel, funit, fformat, fcoordsys;
    int *isfortran;
    int *llabel, *lunit, *lformat, *lcoordsys;
#endif /* PROTOTYPE */
{

    char *label    =  HDf2cstring(flabel, *llabel);
    char *unit     =  HDf2cstring(funit, *lunit);  
    char *format   =  HDf2cstring(fformat, *lformat);
    char *coordsys =  HDf2cstring(fcoordsys, *lcoordsys);
    int32 status;

    status = DFSDIsetdatastrs(label, unit, format, coordsys);

    HDfreespace(label);
    HDfreespace(unit);
    HDfreespace(format);
    HDfreespace(coordsys);

    return status;

} /* ndsisdas */

/*-----------------------------------------------------------------------------
 * Name:    dsgdast
 * Purpose: Call DFSDgetdatastrs to get the data attributes
 * Inputs:  label, unit, format, coordsys: strings to return attributes in
 * Returns: 0 on success, -1 on failure with	DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdatastrs
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsigdas(_fcd label, _fcd unit, _fcd format, _fcd coordsys, int32 *llabel,
        int32 *lunit, int32 *lformat, int32 *lcoord)
#else
ndsigdas(label, unit, format, coordsys, llabel, lunit, lformat, lcoord)
     _fcd label, unit, format, coordsys;
     int32 *llabel, *lunit, *lformat, *lcoord;
#endif /* PROTOTYPE */
{
    char *ilabel, *iunit, *iformat, *icoord;
    int32 status;

    iunit = ilabel = iformat = icoord = NULL;

    if(*llabel)  ilabel  = (char *) HDgetspace((uint32)*llabel + 1);
    if(*lunit)   iunit   = (char *) HDgetspace((uint32)*lunit + 1);
    if(*lformat) iformat = (char *) HDgetspace((uint32)*lformat + 1);
    if(*lcoord)  icoord  = (char *) HDgetspace((uint32)*lcoord + 1);

    status = DFSDgetdatastrs(ilabel, iunit, iformat, icoord);
    
    HDpackFstring(ilabel,  _fcdtocp(label),    *llabel);
    HDpackFstring(iunit,   _fcdtocp(unit),     *lunit);
    HDpackFstring(iformat, _fcdtocp(format),   *lformat);
    HDpackFstring(icoord,  _fcdtocp(coordsys), *lcoord);

    if(ilabel)  HDfreespace(ilabel);
    if(iunit)   HDfreespace(iunit);
    if(iformat) HDfreespace(iformat);
    if(icoord)  HDfreespace(icoord);

    return status;

}

/*-----------------------------------------------------------------------------
 * Name:    dsscal
 * Purpose: Call DFSDsetcal to set calibration data
 * Inputs:  cal, cal_err   : calibration and error
 *          ioff, ioff_err : offset and error
 *          cal_type       : after calibration NT
 * Returns: 0 on success, -1 on failure
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdatastrs
 *---------------------------------------------------------------------------*/
    FRETVAL(int)
#ifdef PROTOTYPE
ndsscal(float64 *cal, float64 *cal_err, float64 *ioff, float64 *ioff_err,
         int32 * cal_type)
#else
ndsscal(cal, cal_err, ioff, ioff_err, cal_type)
     float64 *cal, *cal_err, *ioff, *ioff_err;
     int32   *cal_type;
#endif /* PROTOTYPE */
{

    return DFSDsetcal(*cal, *cal_err, *ioff, *ioff_err, *cal_type);


} /* ndsscal */

/*-----------------------------------------------------------------------------
 * Name:    dsgcal
 * Purpose: Call DFSDgetcal to get calibration data
 * Inputs:  cal, cal_err   : calibration and error
 *          ioff, ioff_err : offset and error
 *          cal_type       : after calibration NT
 * Returns: 0 on success, -1 on failure
 * Users:   HDF Fortran programmers
 * Invokes: DFSDgetdatastrs
 *---------------------------------------------------------------------------*/

    FRETVAL(int)
#ifdef PROTOTYPE
ndsgcal(float64 *cal, float64 *cal_err, float64 *ioff, float64 *ioff_err,
         int32 * cal_type)
#else
ndsgcal(cal, cal_err, ioff, ioff_err, cal_type)
     float64 *cal, *cal_err, *ioff, *ioff_err;
     int32   *cal_type;
#endif /* PROTOTYPE */
{

    return DFSDgetcal(cal, cal_err, ioff, ioff_err, cal_type);

} /* ndsscal */
