#ifndef HOM
#define HOM

#include <stdio.h>
#include "bmpio.h"
//start from imin,jmin and return i first time reach to a full whithe line -1 if unable to fine
int i_tasefid(int jmin, int jmax, int imin, int imax);

//start from imin,jmin and return j first time reach to a full whithe line -1 if unable to fine
int j_tasefid(int jmin, int jmax, int imin, int imax);

//start from imin,jmin and return i first time reach to a line with black pixle -1 if unable to fine
int i_tasiah(int jmin, int jmax, int imin, int imax);

//start from imin,jmin and return j first time reach to a line with black pixle -1 if unable to fine
int j_tasiah(int jmin, int jmax, int imin, int imax);

//start from imax,jmax(paiin) and return i first time reach to a full with line -1 if unable to fine
int i_tasiahp(int jmin, int jmax, int imin, int imax);

//start from imin,jmin and return j first time reach to a full with line -1 if unable to fine
int j_tasiahp(int jmin, int jmax, int imin, int imax);

//copy arry between jmin,jamx,imin,imax  from pic to temp;
void cparry(int jmin, int jmax, int imin, int imax);

//this function will delete margin(hashie) of given arry and save it
int hazfehashie(int jmin, int jmax, int imin, int imax);

//check if a pixle is whith(return 1) or not(return 0) and
int sefidi(int i, int j);

//doing the same job as hazfehashie but for a complite image
void crop(char p[100]);

//resize a image to nwidth nheight(just increasing size)
void resize (char p[100],int nwidth,int nheight);

//increase size in x to nwidth
void xbozorg(double nesbat, int nwidth, int height);

//increas size in y to nwith
void ybozorg(double nesbat, int nwidth, int nheight);

//crop and resiz dataset to a 887 750 (maximum size of data set) then calculat the avrage for each number and save in fixedlearned"i".bmp
int learning();

//first crop and resize given photo of a digital clock and detect evry number and return a number lilke 10:30:15 -> 103015
int detecting();

//absolot 
int abs(int a);
#endif#
