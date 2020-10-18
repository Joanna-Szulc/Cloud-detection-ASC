/*
* #########################################################################
* #                                                                       #
* #                     I S U T I L . H                                   #
* #                                                                       #
* # This is the Isutil/Isutil.h from ISDAT, http://www.space.irfu.se/isdat#
* #                                                                       #
* #########################################################################
*
*/

#include <time.h>

#ifndef ISUTIL_H
#define ISUTIL_H

/*
* Definitions for ISDAT utility functions
*/


#ifndef NULL
#define NULL 0
#endif /* NULL */

/* define M_PI ................*/
#define M_PI 3.14159265358979323846

/* bit definitions for IsGetDirList() flags */
#define IsLIST_FILE 1
#define IsLIST_DIR 2
#define IsLIST_ALL (IsLIST_FILE | IsLIST_DIR)

/* which values used in IsGetLibList() */
#define IsLIB_OPERATOR 1		/* used when IsGetLibList() is
searching for operator libs */
#define IsLIB_DBH 2			/* used when IsGetLibList() is
searching for dbh modules */

/*
* Memory Management
*/
#define IsNew(type) ((type *) malloc((unsigned) sizeof(type)))

/*
* Isdat Time
*/

#define IsTIME_MJD_DIFF 631152000 /* seconds between 1/1 1970 and 1/1 1950 */
#define IsSEC_PER_DAY 86400	/* seconds per day */
#define IsYMD_HMS_LEN 64
#define IsSEC_PER_STC 4.68751353e-3 /* seconds per one satellite time clock */

typedef struct _IsTime { /* define Isdat time (IsTime) */
	int s;		/* seconds since January 1, 1970 */
	int ns;		/* and nanoseconds */
} IsTime;

typedef struct _IsTimePeriod {
	IsTime start;	/* start of time period */
	IsTime interval;	/* length of time period */
} IsTimePeriod;

typedef struct _IsCalendar {
	int year;		/* year, eg. 1994 */
	int month;		/* month (1 - 12) */
	int day;		/* day (1 - 31) */
	int hour;		/* hour (0 - 23) */
	int minute;		/* minute (0 - 59) */
	int second;		/* second (0 - 59) */
	int ns;		/* nanosecond (0 - 999999999) */
} IsCalendar;

/*
* Isdat Time declarations
*/
extern void IsAddTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern char *IsBinDir(
#if NeedFunctionPrototypes
	void
#endif
);
extern void IsAddTimeDouble(
#if NeedFunctionPrototypes
	IsTime *,
	double
#endif
);
extern void IsCalendar2Time(
#if NeedFunctionPrototypes
	IsCalendar *,
	IsTime *
#endif
);
extern void IsCalendar2YymdHms(
#if NeedFunctionPrototypes
	IsCalendar *,
	char *
#endif
);
extern int IsCmpTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern void IsDivTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern void IsDivTimeDouble(
#if NeedFunctionPrototypes
	IsTime *,
	double
#endif
);
extern IsTime IsDouble2Time(
#if NeedFunctionPrototypes
	double
#endif
);
extern int IsFfs(
#if NeedFunctionPrototypes
	int
#endif
);
extern char *IsFontDir(
#if NeedFunctionPrototypes
	void
#endif
);
extern void IsFreeLibList(
#if NeedFunctionPrototypes
	char **		/* libList */
#endif
);
extern char **IsGetLibList(
#if NeedFunctionPrototypes
	int			/* which */
#endif
);
extern char *IsHelpDir(
#if NeedFunctionPrototypes
	void
#endif
);
extern IsTime IsInt2Time(
#if NeedFunctionPrototypes
	int
#endif
);
extern char *IsLibDir(
#if NeedFunctionPrototypes
	void
#endif
);
extern char *IsLogDir(
#if NeedFunctionPrototypes
	void
#endif
);
extern IsTime IsRetAddTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern IsTime IsRetDivTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern IsTime IsRetMulTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern IsTime IsRetSubTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern void IsTime2Calendar(
#if NeedFunctionPrototypes
	IsTime*,
	IsCalendar *
#endif
);
extern void IsTime2Hms(
#if NeedFunctionPrototypes
	IsTime *,
	char *
#endif
);
extern double IsTime2Double(
#if NeedFunctionPrototypes
	IsTime *
#endif
);
extern int IsTime2Int(
#if NeedFunctionPrototypes
	IsTime *
#endif
);
extern double IsTime2Mjd(
#if NeedFunctionPrototypes
	IsTime *
#endif
);
extern void IsTime2Seconds(
#if NeedFunctionPrototypes
	IsTime*,
	char *
#endif
);
extern unsigned int IsTime2VikStw(
#if NeedFunctionPrototypes
	IsTime *
#endif
);
extern void IsTime2YymdHms(
#if NeedFunctionPrototypes
	IsTime*,
	char *
#endif
);
extern void IsMjd2Time(
#if NeedFunctionPrototypes
	double,
	IsTime *
#endif
);
extern void IsMulTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern void IsMulTimeDouble(
#if NeedFunctionPrototypes
	IsTime *,
	double
#endif
);
extern void IsSeconds2Time(
#if NeedFunctionPrototypes
	char *,
	IsTime *
#endif
);
extern void IsSubTime(
#if NeedFunctionPrototypes
	IsTime *,
	IsTime *
#endif
);
extern void IsSubTimeDouble(
#if NeedFunctionPrototypes
	IsTime *,
	double
#endif
);

/*
extern long IsTimeGm(
#if NeedFunctionPrototypes
struct tm *
#endif
);
*/

extern void IsVikStw2Time(
#if NeedFunctionPrototypes
	int,
	unsigned int,
	IsTime *
#endif
);
extern void IsYymdHms2Calendar(
#if NeedFunctionPrototypes
	char *,
	IsCalendar *
#endif
);
extern void IsYymdHms2Time(
#if NeedFunctionPrototypes
	char *,
	IsTime *
#endif
);


long IsTimeGm(struct tm *);



#endif /* ISUTIL_H */

