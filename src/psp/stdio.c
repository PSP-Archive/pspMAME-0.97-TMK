#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef unsigned int size_t;

#define BUFSIZE 100  /* Size of the output buffer */

struct s_strargument {    /* Describes the string being written to */
  char *next;                   /* Next free slot in the string */
  char *last;                   /* Last available slot in the string */
};

#define MAXDIG 20
#define PS2LIB_STR_MAX 4096

int isdigit(int __c);
size_t	strlen(const char *);
int isspace(int __c);
int isupper(int __c);
int iswspace(unsigned int);

void *memset(void *, int, size_t);

int __srefill(FILE *);

int vfprintf(FILE *pOut, const char *zFormat, va_list ap);

int vxprintf(void (*func)(char *, int, void *), void *arg, const char *format, va_list ap);

enum e_type {    /* The type of the format field */
   RADIX,            /* Integer types.  %d, %x, %o, and so forth */
   FLOAT,            /* Floating point.  %f */
   EXP,              /* Exponentional notation. %e and %E */
   GENERIC,          /* Floating or exponential, depending on exponent. %g */
   SIZE,             /* Return number of characters processed so far. %n */
   STRING,           /* Strings. %s */
   PERCENT,          /* Percent symbol. %% */
   CHAR,             /* Characters. %c */
   ERROR,            /* Used to indicate no such conversion type */
/* The rest are extensions, not normally found in printf() */
   CHARLIT,          /* Literal characters.  %' */
   SEEIT,            /* Strings with visible control characters. %S */
   MEM_STRING,       /* A string which should be deleted after use. %z */
   ORDINAL,          /* 1st, 2nd, 3rd and so forth */
};

typedef struct s_info {   /* Information about each format field */
  int  fmttype;              /* The format field code letter */
  int  base;                 /* The base for radix conversion */
  char *charset;             /* The character set for conversion */
  int  flag_signed;          /* Is the quantity signed? */
  char *prefix;              /* Prefix on non-zero values in alt format */
  enum e_type type;          /* Conversion paradigm */
} info;

static info fmtinfo[] = {
  { 'd',  10,  "0123456789",       1,    0, RADIX,      },
  { 's',   0,  0,                  0,    0, STRING,     },
  { 'S',   0,  0,                  0,    0, SEEIT,      },
  { 'z',   0,  0,                  0,    0, MEM_STRING, },
  { 'c',   0,  0,                  0,    0, CHAR,       },
  { 'o',   8,  "01234567",         0,  "0", RADIX,      },
  { 'u',  10,  "0123456789",       0,    0, RADIX,      },
  { 'x',  16,  "0123456789abcdef", 0, "x0", RADIX,      },
  { 'X',  16,  "0123456789ABCDEF", 0, "X0", RADIX,      },
  { 'r',  10,  "0123456789",       0,    0, ORDINAL,    },
  { 'f',   0,  0,                  1,    0, FLOAT,      },
  { 'e',   0,  "e",                1,    0, EXP,        },
  { 'E',   0,  "E",                1,    0, EXP,        },
  { 'g',   0,  "e",                1,    0, GENERIC,    },
  { 'G',   0,  "E",                1,    0, GENERIC,    },
  { 'i',  10,  "0123456789",       1,    0, RADIX,      },
  { 'n',   0,  0,                  0,    0, SIZE,       },
  { 'S',   0,  0,                  0,    0, SEEIT,      },
  { '%',   0,  0,                  0,    0, PERCENT,    },
  { 'b',   2,  "01",               0, "b0", RADIX,      }, /* Binary notation */
  { 'p',  16,  "0123456789ABCDEF", 0, "x0", RADIX,      }, /* Pointers */
  { '\'',  0,  0,                  0,    0, CHARLIT,    }, /* Literal char */
};
#define NINFO  (sizeof(fmtinfo)/sizeof(info))  /* Size of the fmtinfo table */

#ifndef NOFLOATINGPOINT
/*
** "*val" is a double such that 0.1 <= *val < 10.0
** Return the ascii code for the leading digit of *val, then
** multiply "*val" by 10.0 to renormalize.
**
** Example:
**     input:     *val = 3.14159
**     output:    *val = 1.4159    function return = '3'
**
** The counter *cnt is incremented each time.  After counter exceeds
** 16 (the number of significant digits in a 64-bit float) '0' is
** always returned.
*/
//TMK static int getdigit(long double *val, int *cnt){
static int getdigit(real_l_double *val, int *cnt){
  int digit;
//TMK  long double d;
  real_l_double d;
  if( (*cnt)++ >= MAXDIG ) return '0';
  digit = (int)*val;
  d = digit;
  digit += '0';
  *val = (*val - d)*10.0;
  return digit;
}
#endif


int vxprintf(func,arg,format,ap)
  void (*func)(char*,int,void*);
  void *arg;
  const char *format;
  va_list ap;
{
  register const char *fmt; /* The format string. */
  register int c;           /* Next character in the format string */
  register char *bufpt;     /* Pointer to the conversion buffer */
  register int  precision;  /* Precision of the current field */
  register int  length;     /* Length of the field */
  register int  idx;        /* A general purpose loop counter */
  int count;                /* Total number of characters output */
  int width;                /* Width of the current field */
  int flag_leftjustify;     /* True if "-" flag is present */
  int flag_plussign;        /* True if "+" flag is present */
  int flag_blanksign;       /* True if " " flag is present */
  int flag_alternateform;   /* True if "#" flag is present */
  int flag_zeropad;         /* True if field width constant starts with zero */
  int flag_long;            /* True if "l" flag is present */
  int flag_center;          /* True if "=" flag is present */
  unsigned long long longvalue;  /* Value for integer types */

//TMK  long double realvalue;    /* Value for real types */
  real_l_double realvalue;    /* Value for real types */
  info *infop;              /* Pointer to the appropriate info structure */
  char buf[BUFSIZE];        /* Conversion buffer */
  char prefix;              /* Prefix character.  "+" or "-" or " " or '\0'. */
  int  errorflag = 0;       /* True if an error is encountered */
  enum e_type xtype;        /* Conversion paradigm */
  char *zMem = 0;           /* String to be freed */
  static char spaces[] =
     "                                                    ";
#define SPACESIZE (sizeof(spaces)-1)
#ifndef NOFLOATINGPOINT
  int  exp;                 /* exponent of real numbers */
//TMK  long double rounder;      /* Used for rounding floating point values */
  real_l_double rounder;      /* Used for rounding floating point values */
  int flag_dp;              /* True if decimal point should be shown */
  int flag_rtz;             /* True if trailing zeros should be removed */
  int flag_exp;             /* True to force display of the exponent */
  int nsd;                  /* Number of significant digits returned */
#endif

  fmt = format;                     /* Put in a register for speed */
  count = length = 0;
  bufpt = 0;
  for(; (c=(*fmt))!=0; ++fmt){
    if( c!='%' ){
      register int amt;
      bufpt = (char *)fmt;
      amt = 1;
      while( (c=(*++fmt))!='%' && c!=0 ) amt++;
      (*func)(bufpt,amt,arg);
      count += amt;
      if( c==0 ) break;
    }
    if( (c=(*++fmt))==0 ){
      errorflag = 1;
      (*func)("%",1,arg);
      count++;
      break;
    }
    /* Find out what flags are present */
    flag_leftjustify = flag_plussign = flag_blanksign =
     flag_alternateform = flag_zeropad = flag_center = 0;
    do{
      switch( c ){
        case '-':   flag_leftjustify = 1;     c = 0;   break;
        case '+':   flag_plussign = 1;        c = 0;   break;
        case ' ':   flag_blanksign = 1;       c = 0;   break;
        case '#':   flag_alternateform = 1;   c = 0;   break;
        case '0':   flag_zeropad = 1;         c = 0;   break;
        case '=':   flag_center = 1;          c = 0;   break;
        default:                                       break;
      }
    }while( c==0 && (c=(*++fmt))!=0 );
    if( flag_center ) flag_leftjustify = 0;
    /* Get the field width */
    width = 0;
    if( c=='*' ){
      width = va_arg(ap,int);
      if( width<0 ){
        flag_leftjustify = 1;
        width = -width;
      }
      c = *++fmt;
    }else{
      while( isdigit(c) ){
        width = width*10 + c - '0';
        c = *++fmt;
      }
    }
    if( width > BUFSIZE-10 ){
      width = BUFSIZE-10;
    }
    /* Get the precision */
    if( c=='.' ){
      precision = 0;
      c = *++fmt;
      if( c=='*' ){
        precision = va_arg(ap,int);
#ifndef COMPATIBILITY
        /* This is sensible, but SUN OS 4.1 doesn't do it. */
        if( precision<0 ) precision = -precision;
#endif
        c = *++fmt;
      }else{
        while( isdigit(c) ){
          precision = precision*10 + c - '0';
          c = *++fmt;
        }
      }
      /* Limit the precision to prevent overflowing buf[] during conversion */
      if( precision>BUFSIZE-40 ) precision = BUFSIZE-40;
    }else{
      precision = -1;
    }
    /* Get the conversion type modifier */
    if( c=='l' ){
      flag_long = 1;
      c = *++fmt;
      if( c == 'l' ){
	flag_long = 2;
	c = *++fmt;
      }
    }else{
      flag_long = 0;
    }
    /* Fetch the info entry for the field */
    infop = 0;
    for(idx=0; idx<NINFO; idx++){
      if( c==fmtinfo[idx].fmttype ){
        infop = &fmtinfo[idx];
        break;
      }
    }
    /* No info entry found.  It must be an error. */
    if( infop==0 ){
      xtype = ERROR;
    }else{
      xtype = infop->type;
    }

    /*
    ** At this point, variables are initialized as follows:
    **
    **   flag_alternateform          TRUE if a '#' is present.
    **   flag_plussign               TRUE if a '+' is present.
    **   flag_leftjustify            TRUE if a '-' is present or if the
    **                               field width was negative.
    **   flag_zeropad                TRUE if the width began with 0.
    **   flag_long                   TRUE if the letter 'l' (ell) prefixed
    **                               the conversion character.
    **   flag_blanksign              TRUE if a ' ' is present.
    **   width                       The specified field width.  This is
    **                               always non-negative.  Zero is the default.
    **   precision                   The specified precision.  The default
    **                               is -1.
    **   xtype                       The class of the conversion.
    **   infop                       Pointer to the appropriate info struct.
    */
    switch( xtype ){
      case ORDINAL:
      case RADIX:
        if(( flag_long>1 )&&( infop->flag_signed )){
	    signed long long t = va_arg(ap,signed long long);
	    longvalue = t;
	}else if(( flag_long>1 )&&( !infop->flag_signed )){
	    unsigned long long t = va_arg(ap,unsigned long long);
	    longvalue = t;
	}else if(( flag_long )&&( infop->flag_signed )){
	    signed long t = va_arg(ap,signed long);
	    longvalue = t;
	}else if(( flag_long )&&( !infop->flag_signed )){
	    unsigned long t = va_arg(ap,unsigned long);
	    longvalue = t;
	}else if(( !flag_long )&&( infop->flag_signed )){
	    signed int t = va_arg(ap,signed int) & ((unsigned long) 0xffffffff);
	    longvalue = t;
	}else{
	    unsigned int t = va_arg(ap,unsigned int) & ((unsigned long) 0xffffffff);
	    longvalue = t;
	}
#ifdef COMPATIBILITY
        /* For the format %#x, the value zero is printed "0" not "0x0".
        ** I think this is stupid. */
        if( longvalue==0 ) flag_alternateform = 0;
#else
        /* More sensible: turn off the prefix for octal (to prevent "00"),
        ** but leave the prefix for hex. */
        if( longvalue==0 && infop->base==8 ) flag_alternateform = 0;
#endif
        if( infop->flag_signed ){
          if( *(long long*)&longvalue<0 ){
	    longvalue = -*(long long*)&longvalue;
            prefix = '-';
          }else if( flag_plussign )  prefix = '+';
          else if( flag_blanksign )  prefix = ' ';
          else                       prefix = 0;
        }else                        prefix = 0;
        if( flag_zeropad && precision<width-(prefix!=0) ){
          precision = width-(prefix!=0);
	}
        bufpt = &buf[BUFSIZE];
        if( xtype==ORDINAL ){
          long a,b;
          a = longvalue%10;
          b = longvalue%100;
          bufpt -= 2;
          if( a==0 || a>3 || (b>10 && b<14) ){
            bufpt[0] = 't';
            bufpt[1] = 'h';
          }else if( a==1 ){
            bufpt[0] = 's';
            bufpt[1] = 't';
          }else if( a==2 ){
            bufpt[0] = 'n';
            bufpt[1] = 'd';
          }else if( a==3 ){
            bufpt[0] = 'r';
            bufpt[1] = 'd';
          }
        }
        {
          register char *cset;      /* Use registers for speed */
          register int base;
          cset = infop->charset;
          base = infop->base;
          do{                                           /* Convert to ascii */
            *(--bufpt) = cset[longvalue%base];
            longvalue = longvalue/base;
          }while( longvalue>0 );
	}
        length = (int)(&buf[BUFSIZE]-bufpt);
	if(infop->fmttype == 'p')
        {
		precision = 8;
		flag_alternateform = 1;
        }

        for(idx=precision-length; idx>0; idx--){
          *(--bufpt) = '0';                             /* Zero pad */
	}
        if( prefix ) *(--bufpt) = prefix;               /* Add sign */
        if( flag_alternateform && infop->prefix ){      /* Add "0" or "0x" */
          char *pre, x;
          pre = infop->prefix;
          if( *bufpt!=pre[0] ){
            for(pre=infop->prefix; (x=(*pre))!=0; pre++) *(--bufpt) = x;
	  }
        }

        length = (int)(&buf[BUFSIZE]-bufpt);
        break;
      case FLOAT:
      case EXP:
      case GENERIC:
//TMK        realvalue = va_arg(ap,double);
        realvalue = va_arg(ap,real_double);
#ifndef NOFLOATINGPOINT
        if( precision<0 ) precision = 6;         /* Set default precision */
        if( precision>BUFSIZE-10 ) precision = BUFSIZE-10;
        if( realvalue<0.0 ){
          realvalue = -realvalue;
          prefix = '-';
	}else{
          if( flag_plussign )          prefix = '+';
          else if( flag_blanksign )    prefix = ' ';
          else                         prefix = 0;
	}
        if( infop->type==GENERIC && precision>0 ) precision--;
        rounder = 0.0;
#ifdef COMPATIBILITY
        /* Rounding works like BSD when the constant 0.4999 is used.  Wierd! */
        for(idx=precision, rounder=0.4999; idx>0; idx--, rounder*=0.1);
#else
        /* It makes more sense to use 0.5 */
        if( precision>MAXDIG-1 ) idx = MAXDIG-1;
        else                     idx = precision;
        for(rounder=0.5; idx>0; idx--, rounder*=0.1);
#endif
        if( infop->type==FLOAT ) realvalue += rounder;
        /* Normalize realvalue to within 10.0 > realvalue >= 1.0 */
        exp = 0;
        if( realvalue>0.0 ){
          int k = 0;
          while( realvalue>=1e8 && k++<100 ){ realvalue *= 1e-8; exp+=8; }
          while( realvalue>=10.0 && k++<100 ){ realvalue *= 0.1; exp++; }
          while( realvalue<1e-8 && k++<100 ){ realvalue *= 1e8; exp-=8; }
          while( realvalue<1.0 && k++<100 ){ realvalue *= 10.0; exp--; }
          if( k>=100 ){
            bufpt = "NaN";
            length = 3;
            break;
          }
	}
        bufpt = buf;
        /*
        ** If the field type is GENERIC, then convert to either EXP
        ** or FLOAT, as appropriate.
        */
        flag_exp = xtype==EXP;
        if( xtype!=FLOAT ){
          realvalue += rounder;
          if( realvalue>=10.0 ){ realvalue *= 0.1; exp++; }
        }
        if( xtype==GENERIC ){
          flag_rtz = !flag_alternateform;
          if( exp<-4 || exp>precision ){
            xtype = EXP;
          }else{
            precision = precision - exp;
            xtype = FLOAT;
          }
	}else{
          flag_rtz = 0;
	}
        /*
        ** The "exp+precision" test causes output to be of type EXP if
        ** the precision is too large to fit in buf[].
        */
        nsd = 0;
        if( xtype==FLOAT && exp+precision<BUFSIZE-30 ){
          flag_dp = (precision>0 || flag_alternateform);
          if( prefix ) *(bufpt++) = prefix;         /* Sign */
          if( exp<0 )  *(bufpt++) = '0';            /* Digits before "." */
          else for(; exp>=0; exp--) *(bufpt++) = getdigit(&realvalue,&nsd);
          if( flag_dp ) *(bufpt++) = '.';           /* The decimal point */
          for(exp++; exp<0 && precision>0; precision--, exp++){
            *(bufpt++) = '0';
          }
          while( (precision--)>0 ) *(bufpt++) = getdigit(&realvalue,&nsd);
          *(bufpt--) = 0;                           /* Null terminate */
          if( flag_rtz && flag_dp ){     /* Remove trailing zeros and "." */
            while( bufpt>=buf && *bufpt=='0' ) *(bufpt--) = 0;
            if( bufpt>=buf && *bufpt=='.' ) *(bufpt--) = 0;
          }
          bufpt++;                            /* point to next free slot */
	}else{    /* EXP or GENERIC */
          flag_dp = (precision>0 || flag_alternateform);
          if( prefix ) *(bufpt++) = prefix;   /* Sign */
          *(bufpt++) = getdigit(&realvalue,&nsd);  /* First digit */
          if( flag_dp ) *(bufpt++) = '.';     /* Decimal point */
          while( (precision--)>0 ) *(bufpt++) = getdigit(&realvalue,&nsd);
          bufpt--;                            /* point to last digit */
          if( flag_rtz && flag_dp ){          /* Remove tail zeros */
            while( bufpt>=buf && *bufpt=='0' ) *(bufpt--) = 0;
            if( bufpt>=buf && *bufpt=='.' ) *(bufpt--) = 0;
          }
          bufpt++;                            /* point to next free slot */
          if( exp || flag_exp ){
            *(bufpt++) = infop->charset[0];
            if( exp<0 ){ *(bufpt++) = '-'; exp = -exp; } /* sign of exp */
            else       { *(bufpt++) = '+'; }
            if( exp>=100 ){
              *(bufpt++) = (exp/100)+'0';                /* 100's digit */
              exp %= 100;
  	    }
            *(bufpt++) = exp/10+'0';                     /* 10's digit */
            *(bufpt++) = exp%10+'0';                     /* 1's digit */
          }
	}
        /* The converted number is in buf[] and zero terminated. Output it.
        ** Note that the number is in the usual order, not reversed as with
        ** integer conversions. */
        length = (int)(bufpt-buf);
        bufpt = buf;

        /* Special case:  Add leading zeros if the flag_zeropad flag is
        ** set and we are not left justified */
        if( flag_zeropad && !flag_leftjustify && length < width){
          int i;
          int nPad = width - length;
          for(i=width; i>=nPad; i--){
            bufpt[i] = bufpt[i-nPad];
          }
          i = prefix!=0;
          while( nPad-- ) bufpt[i++] = '0';
          length = width;
        }
#endif
        break;
      case SIZE:
        *(va_arg(ap,int*)) = count;
        length = width = 0;
        break;
      case PERCENT:
        buf[0] = '%';
        bufpt = buf;
        length = 1;
        break;
      case CHARLIT:
      case CHAR:
        c = buf[0] = (xtype==CHAR ? va_arg(ap,int) : *++fmt);
        if( precision>=0 ){
          for(idx=1; idx<precision; idx++) buf[idx] = c;
          length = precision;
	}else{
          length =1;
	}
        bufpt = buf;
        break;
      case STRING:
      case MEM_STRING:
        zMem = bufpt = va_arg(ap,char*);
        if( bufpt==0 ) bufpt = "(null)";
        length = strlen(bufpt);
        if( precision>=0 && precision<length ) length = precision;
        break;
      case SEEIT:
        {
          int i;
          int c;
          char *arg = va_arg(ap,char*);
          for(i=0; i<BUFSIZE-1 && (c = *arg++)!=0; i++){
            if( c<0x20 || c>=0x7f ){
              buf[i++] = '^';
              buf[i] = (c&0x1f)+0x40;
            }else{
              buf[i] = c;
            }
          }
          bufpt = buf;
          length = i;
          if( precision>=0 && precision<length ) length = precision;
        }
        break;
      case ERROR:
        buf[0] = '%';
        buf[1] = c;
        errorflag = 0;
        idx = 1+(c!=0);
        (*func)("%",idx,arg);
        count += idx;
        if( c==0 ) fmt--;
        break;
    }/* End switch over the format type */
    /*
    ** The text of the conversion is pointed to by "bufpt" and is
    ** "length" characters long.  The field width is "width".  Do
    ** the output.
    */
    if( !flag_leftjustify ){
      register int nspace;
      nspace = width-length;
      if( nspace>0 ){
        if( flag_center ){
          nspace = nspace/2;
          width -= nspace;
          flag_leftjustify = 1;
	}
        count += nspace;
        while( nspace>=SPACESIZE ){
          (*func)(spaces,SPACESIZE,arg);
          nspace -= SPACESIZE;
        }
        if( nspace>0 ) (*func)(spaces,nspace,arg);
      }
    }
    if( length>0 ){
      (*func)(bufpt,length,arg);
      count += length;
    }
    if( xtype==MEM_STRING && zMem ){
      free(zMem);
    }
    if( flag_leftjustify ){
      register int nspace;
      nspace = width-length;
      if( nspace>0 ){
        count += nspace;
        while( nspace>=SPACESIZE ){
          (*func)(spaces,SPACESIZE,arg);
          nspace -= SPACESIZE;
        }
        if( nspace>0 ) (*func)(spaces,nspace,arg);
      }
    }
  }/* End for loop over the format string */
  return errorflag ? -1 : count;
} /* End of function */

void __sout(char *txt, int amt, void *arg)
{
  register char *head;
  register const char *t;
  register int a;
  register char *tail;
  a = amt;
  t = txt;
  head = ((struct s_strargument*)arg)->next;
  tail = ((struct s_strargument*)arg)->last;
  if( tail ){
    while( a-- >0 && head<tail ) *(head++) = *(t++);
  }else{
    while( a-- >0 ) *(head++) = *(t++);
  }
  *head = 0;
  ((struct s_strargument*)arg)->next = head;
}

void __fout(char *zNewText, int nNewChar, void *arg)
{
	fwrite(zNewText,1,nNewChar,(FILE*)arg);
}

int vsnprintf(char *buf, size_t n, const char *fmt, va_list ap){
  struct s_strargument arg;
  arg.next = buf;
  arg.last = &buf[n-1];
  *buf = 0;
  return vxprintf(__sout,&arg,fmt,ap);
}

int snprintf(char *str, size_t sz, const char *format, ...)
{
	va_list args;
	struct s_strargument arg;
	int ret;

	arg.next = str;
	arg.last = &str[sz-1];

	va_start(args, format);
	ret = vxprintf(__sout, &arg, format, args);
	va_end(args);

	return ret;
}

int vsprintf(char *buf, const char *fmt, va_list ap){
  struct s_strargument arg;
  arg.next = buf;
  arg.last = NULL;
  *buf = 0;
  return vxprintf(__sout,&arg,fmt,ap);
}

int sprintf (char *str, const char *format, ...)
{
	va_list args;
	struct s_strargument arg;
	int ret;

	arg.next = str;
	arg.last = NULL;

	va_start(args, format);
	ret = vxprintf(__sout, &arg, format, args);
	va_end(args);

	return ret;
}

int fprintf(FILE *pOut, const char *zFormat, ...){
  va_list ap;
  int retc;

  va_start(ap,zFormat);
//  retc = vxprintf(__fout,pOut,zFormat,ap);
  retc = vfprintf(pOut, zFormat, ap);
  va_end(ap);
  return retc;
}

int vfprintf(FILE *pOut, const char *zFormat, va_list ap) {

  if (stdout ==pOut || stderr ==pOut)
    return vprintf(zFormat,ap);
  else
    return vxprintf(__fout,pOut,zFormat,ap);

}

int printf(const char *format, ...)
{
	va_list args;
	int ret;

	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);

	return ret;
}

int vprintf(const char *format, va_list args)
{
  static char buf[PS2LIB_STR_MAX];
	int ret;

	ret = vsnprintf(buf, PS2LIB_STR_MAX, format, args);

//	sceIoWrite(1, buf, ret);
//	return ret;
	return printfnw_(buf);
}

////////////////////////////////////////////////////////////////////////////////
#define	BUF	40
#define BufferEmpty (fp->_r <= 0 && __srefill(fp))

/*
 * Flags used during conversion.
 */

#define	LONG		0x01	/* l: long or double */
#define	LONGDBL		0x02	/* L/ll: long double or long long */
#define	SHORT		0x04	/* h: short */
#define CHAR		0x08	/* hh: 8 bit integer */
#define	SUPPRESS	0x10	/* suppress assignment */
#define	POINTER		0x20	/* weird %p pointer (`fake hex') */
#define	NOSKIP		0x40	/* do not skip blanks */

/*
 * The following are used in numeric conversions only:
 * SIGNOK, NDIGITS, DPTOK, and EXPOK are for floating point;
 * SIGNOK, NDIGITS, PFXOK, and NZDIGITS are for integral.
 */

#define	SIGNOK		0x80	/* +/- is (still) legal */
#define	NDIGITS		0x100	/* no digits detected */

#define	DPTOK		0x200	/* (float) decimal point is still legal */
#define	EXPOK		0x400	/* (float) exponent (e+3, etc) still legal */

#define	PFXOK		0x200	/* 0x prefix is (still) legal */
#define	NZDIGITS	0x400	/* no zero digits detected */
#define	NNZDIGITS	0x800	/* no non-zero digits detected */

/*
 * Conversion types.
 */

#define	CT_CHAR		0	/* %c conversion */
#define	CT_CCL		1	/* %[...] conversion */
#define	CT_STRING	2	/* %s conversion */
#define	CT_INT		3	/* integer, i.e., strtol or strtoul */
#define	CT_FLOAT	4	/* floating, i.e., strtod */

//typedef long double _LONG_DOUBLE;
typedef real_l_double __LONG_DOUBLE;
typedef unsigned char u_char;
typedef unsigned long u_long;
typedef unsigned long long  u_long_long;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    unsigned char __wchb[4];
  } __value;		/* Value so far.  */
} mbstate_t;

static int eofread(void *cookie, char *buf, int len)
{
  return 0;
}

size_t _mbrtowc_r(struct _reent *, wchar_t *, const char *, size_t, mbstate_t *);
int __svfscanf_r(struct _reent *rptr, register FILE *fp, char const *fmt0, va_list ap);
u_char *__sccl(register char *tab, register u_char *fmt);
long _strtol_r(struct _reent *, const char *__n, char **__end_PTR, int __base);

int sscanf(const char *str, const char *fmt, ...)
{
  int ret;
  va_list ap;
  FILE f;

  f._flags = __SRD | __SSTR;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._r = strlen (str);
  f._read = eofread;
  f._ub._base = NULL;
  f._lb._base = NULL;
  f._file = -1;  /* No file. */
  va_start (ap, fmt);
  ret = __svfscanf_r (_REENT, &f, fmt, ap);
  va_end (ap);
  return ret;
}

int __svfscanf_r(struct _reent *rptr, register FILE *fp, char const *fmt0, va_list ap)
{
  register u_char *fmt = (u_char *) fmt0;
  register int c;		/* character from format, or conversion */
  register size_t width;	/* field width, or 0 */
  register char *p;		/* points into all kinds of strings */
  register int n;		/* handy integer */
  register int flags;		/* flags as defined above */
  register char *p0;		/* saves original value of p when necessary */
  int nassigned;		/* number of fields assigned */
  int nread;			/* number of characters consumed from fp */
  int base = 0;			/* base argument to strtol/strtoul */
  int nbytes = 1;               /* number of bytes read from fmt string */
  wchar_t wc;                   /* wchar to use to read format string */
  wchar_t *wcp;                 /* handy wide character pointer */
  size_t mbslen;                /* length of converted multibyte sequence */
  mbstate_t state;              /* value to keep track of multibyte state */

  u_long (*ccfn) () = 0;	/* conversion function (strtol/strtoul) */
  char ccltab[256];		/* character class table for %[...] */
  char buf[BUF];		/* buffer for numeric conversions */
  char *lptr;                   /* literal pointer */

  char *cp;
  short *sp;
  int *ip;
  float *flp;
  __LONG_DOUBLE *ldp;
  double *dp;
  long *lp;
#ifndef _NO_LONGLONG
  long long *llp;
#endif

  /* `basefix' is used to avoid `if' tests in the integer scanner */
  static _CONST short basefix[17] =
    {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  _flockfile (fp);
 
  nassigned = 0;
  nread = 0;
  for (;;)
    {
#ifndef _MB_CAPABLE
      wc = *fmt;
#else
      memset (&state, '\0', sizeof (state));
      nbytes = _mbtowc_r (rptr, &wc, fmt, MB_CUR_MAX, &state);
#endif
      fmt += nbytes;
      if (wc == 0)
	goto all_done;
      if (nbytes == 1 && isspace (wc))
	{
	  for (;;)
	    {
	      if (BufferEmpty || !isspace (*fp->_p))
		break;
	      nread++, fp->_r--, fp->_p++;
	    }
	  continue;
	}
      if (wc != '%')
	goto literal;
      width = 0;
      flags = 0;

      /*
       * switch on the format.  continue if done; break once format
       * type is derived.
       */

    again:
      c = *fmt++;

      switch (c)
	{
	case '%':
	literal:
          lptr = fmt - nbytes;
          for (n = 0; n < nbytes; ++n)
            {
	      if (BufferEmpty)
	        goto input_failure;
	      if (*fp->_p != *lptr)
	        goto match_failure;
	      fp->_r--, fp->_p++;
	      nread++;
              ++lptr;
            }
	  continue;

	case '*':
	  flags |= SUPPRESS;
	  goto again;
	case 'l':
	  if (*fmt == 'l')	/* Check for 'll' = long long (SUSv3) */
	    {
	      ++fmt;
	      flags |= LONGDBL;
	    }
	  else
	    flags |= LONG;
	  goto again;
	case 'L':
	  flags |= LONGDBL;
	  goto again;
	case 'h':
	  if (*fmt == 'h')	/* Check for 'hh' = char int (SUSv3) */
	    {
	      ++fmt;
	      flags |= CHAR;
	    }
	  else
	    flags |= SHORT;
	  goto again;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  width = width * 10 + c - '0';
	  goto again;

	  /*
	   * Conversions. Those marked `compat' are for
	   * 4.[123]BSD compatibility.
	   *
	   * (According to ANSI, E and X formats are supposed to
	   * the same as e and x.  Sorry about that.)
	   */

	case 'D':		/* compat */
	  flags |= LONG;
	  /* FALLTHROUGH */
	case 'd':
	  c = CT_INT;
	  ccfn = (u_long (*)())_strtol_r;
	  base = 10;
	  break;

	case 'i':
	  c = CT_INT;
	  ccfn = (u_long (*)())_strtol_r;
	  base = 0;
	  break;

	case 'O':		/* compat */
	  flags |= LONG;
	  /* FALLTHROUGH */
	case 'o':
	  c = CT_INT;
	  ccfn = _strtoul_r;
	  base = 8;
	  break;

	case 'u':
	  c = CT_INT;
	  ccfn = _strtoul_r;
	  base = 10;
	  break;

	case 'X':		/* compat   XXX */
	case 'x':
	  flags |= PFXOK;	/* enable 0x prefixing */
	  c = CT_INT;
	  ccfn = _strtoul_r;
	  base = 16;
	  break;

#ifdef FLOATING_POINT
	case 'E':		/* compat   XXX */
	case 'G':		/* compat   XXX */
/* ANSI says that E,G and X behave the same way as e,g,x */
	  /* FALLTHROUGH */
	case 'e':
	case 'f':
	case 'g':
	  c = CT_FLOAT;
	  break;
#endif
        case 'S':
          flags |= LONG;
          /* FALLTHROUGH */

	case 's':
	  c = CT_STRING;
	  break;

	case '[':
	  fmt = __sccl (ccltab, fmt);
	  flags |= NOSKIP;
	  c = CT_CCL;
	  break;

        case 'C':
          flags |= LONG;
          /* FALLTHROUGH */

	case 'c':
	  flags |= NOSKIP;
	  c = CT_CHAR;
	  break;

	case 'p':		/* pointer format is like hex */
	  flags |= POINTER | PFXOK;
	  c = CT_INT;
	  ccfn = _strtoul_r;
	  base = 16;
	  break;

	case 'n':
	  if (flags & SUPPRESS)	/* ??? */
	    continue;
	  if (flags & CHAR)
	    {
	      cp = va_arg (ap, char *);
	      *cp = nread;
	    }
	  else if (flags & SHORT)
	    {
	      sp = va_arg (ap, short *);
	      *sp = nread;
	    }
	  else if (flags & LONG)
	    {
	      lp = va_arg (ap, long *);
	      *lp = nread;
	    }
#ifndef _NO_LONGLONG
	  else if (flags & LONGDBL)
	    {
	      llp = va_arg (ap, long long*);
	      *llp = nread;
	    }
#endif
	  else
	    {
	      ip = va_arg (ap, int *);
	      *ip = nread;
	    }
	  continue;

	  /*
	   * Disgusting backwards compatibility hacks.	XXX
	   */
	case '\0':		/* compat */
	  _funlockfile (fp);
	  return EOF;

	default:		/* compat */
	  if (isupper (c))
	    flags |= LONG;
	  c = CT_INT;
	  ccfn = (u_long (*)())_strtol_r;
	  base = 10;
	  break;
	}

      /*
       * We have a conversion that requires input.
       */
      if (BufferEmpty)
	goto input_failure;

      /*
       * Consume leading white space, except for formats that
       * suppress this.
       */
      if ((flags & NOSKIP) == 0)
	{
	  while (isspace (*fp->_p))
	    {
	      nread++;
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
		goto input_failure;
	    }
	  /*
	   * Note that there is at least one character in the
	   * buffer, so conversions that do not set NOSKIP ca
	   * no longer result in an input failure.
	   */
	}

      /*
       * Do the conversion.
       */
      switch (c)
	{

	case CT_CHAR:
	  /* scan arbitrary characters (sets NOSKIP) */
	  if (width == 0)
	    width = 1;
          if (flags & LONG) 
            {
              if ((flags & SUPPRESS) == 0)
                wcp = va_arg (ap, wchar_t *);
              else
                wcp = NULL;
              n = 0;
              while (width != 0) 
                {
                  if (n == MB_CUR_MAX)
                    goto input_failure;
                  buf[n++] = *fp->_p;
                  fp->_r -= 1;
                  fp->_p += 1;
                  memset ((_PTR)&state, '\0', sizeof (mbstate_t));
                  if ((mbslen = _mbrtowc_r (rptr, wcp, buf, n, &state)) 
                                                         == (size_t)-1)
                    goto input_failure; /* Invalid sequence */
                  if (mbslen == 0 && !(flags & SUPPRESS))
                    *wcp = L'\0';
                  if (mbslen != (size_t)-2) /* Incomplete sequence */
                    {
                      nread += n;
                      width -= 1;
                      if (!(flags & SUPPRESS))
                        wcp += 1;
                      n = 0;
                    }
                  if (BufferEmpty) 
	            {
                      if (n != 0) 
                        goto input_failure;
                      break;
                    }
                }
              if (!(flags & SUPPRESS))
                nassigned++;
            } 
          else if (flags & SUPPRESS) 
	    {
	      size_t sum = 0;
	      for (;;)
		{
		  if ((n = fp->_r) < (int)width)
		    {
		      sum += n;
		      width -= n;
		      fp->_p += n;
		      if (__srefill (fp))
			{
			  if (sum == 0)
			    goto input_failure;
			  break;
			}
		    }
		  else
		    {
		      sum += width;
		      fp->_r -= width;
		      fp->_p += width;
		      break;
		    }
		}
	      nread += sum;
	    }
	  else
	    {
	      size_t r = fread ((_PTR) va_arg (ap, char *), 1, width, fp);

	      if (r == 0)
		goto input_failure;
	      nread += r;
	      nassigned++;
	    }
	  break;

	case CT_CCL:
	  /* scan a (nonempty) character class (sets NOSKIP) */
	  if (width == 0)
	    width = ~0;		/* `infinity' */
	  /* take only those things in the class */
	  if (flags & SUPPRESS)
	    {
	      n = 0;
	      while (ccltab[*fp->_p])
		{
		  n++, fp->_r--, fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    {
		      if (n == 0)
			goto input_failure;
		      break;
		    }
		}
	      if (n == 0)
		goto match_failure;
	    }
	  else
	    {
	      p0 = p = va_arg (ap, char *);
	      while (ccltab[*fp->_p])
		{
		  fp->_r--;
		  *p++ = *fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    {
		      if (p == p0)
			goto input_failure;
		      break;
		    }
		}
	      n = p - p0;
	      if (n == 0)
		goto match_failure;
	      *p = 0;
	      nassigned++;
	    }
	  nread += n;
	  break;

	case CT_STRING:
	  /* like CCL, but zero-length string OK, & no NOSKIP */
	  if (width == 0)
            width = (size_t)~0;
          if (flags & LONG) 
            {
              /* Process %S and %ls placeholders */
              if ((flags & SUPPRESS) == 0)
                wcp = va_arg (ap, wchar_t *);
              else
                wcp = &wc;
              n = 0;
              while (!isspace (*fp->_p) && width != 0) 
                {
                  if (n == MB_CUR_MAX)
                    goto input_failure;
                  buf[n++] = *fp->_p;
                  fp->_r -= 1;
                  fp->_p += 1;
                  memset ((_PTR)&state, '\0', sizeof (mbstate_t));
                  if ((mbslen = _mbrtowc_r (rptr, wcp, buf, n, &state)) 
                                                        == (size_t)-1)
                    goto input_failure;
                  if (mbslen == 0)
                    *wcp = L'\0';
                  if (mbslen != (size_t)-2) /* Incomplete sequence */
                    {
                      if (iswspace(*wcp)) 
                        {
                          while (n != 0)
                            ungetc (buf[--n], fp);
                          break;
                        }
                      nread += n;
                      width -= 1;
                      if ((flags & SUPPRESS) == 0)
                        wcp += 1;
                      n = 0;
                    }
                  if (BufferEmpty) 
                    {
                      if (n != 0)
                        goto input_failure;
                      break;
                    }
                }
              if (!(flags & SUPPRESS)) 
                {
                  *wcp = L'\0';
                  nassigned++;
                }
            }
          else if (flags & SUPPRESS) 
	    {
	      n = 0;
	      while (!isspace (*fp->_p))
		{
		  n++, fp->_r--, fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    break;
		}
	      nread += n;
	    }
	  else
	    {
	      p0 = p = va_arg (ap, char *);
	      while (!isspace (*fp->_p))
		{
		  fp->_r--;
		  *p++ = *fp->_p++;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    break;
		}
	      *p = 0;
	      nread += p - p0;
	      nassigned++;
	    }
	  continue;

	case CT_INT:
	{
	  /* scan an integer as if by strtol/strtoul */
	  unsigned width_left = 0;
	  int skips = 0;
#ifdef hardway
	  if (width == 0 || width > sizeof (buf) - 1)
#else
	  /* size_t is unsigned, hence this optimisation */
	  if (width - 1 > sizeof (buf) - 2)
#endif
	    {
	      width_left = width - (sizeof (buf) - 1);
	      width = sizeof (buf) - 1;
	    }
	  flags |= SIGNOK | NDIGITS | NZDIGITS | NNZDIGITS;
	  for (p = buf; width; width--)
	    {
	      c = *fp->_p;
	      /*
	       * Switch on the character; `goto ok' if we
	       * accept it as a part of number.
	       */
	      switch (c)
		{
		  /*
		   * The digit 0 is always legal, but is special.
		   * For %i conversions, if no digits (zero or nonzero)
		   * have been scanned (only signs), we will have base==0.
		   * In that case, we should set it to 8 and enable 0x
		   * prefixing. Also, if we have not scanned zero digits
		   * before this, do not turn off prefixing (someone else
		   * will turn it off if we have scanned any nonzero digits).
		   */
		case '0':
		  if (! (flags & NNZDIGITS))
		    goto ok;
		  if (base == 0)
		    {
		      base = 8;
		      flags |= PFXOK;
		    }
		  if (flags & NZDIGITS)
		    {
		      flags &= ~(SIGNOK | NZDIGITS | NDIGITS);
		      goto ok;
		    }
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  if (width_left)
		    {
		      width_left--;
		      width++;
		    }
		  ++skips;
		  goto skip;

		  /* 1 through 7 always legal */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		  base = basefix[base];
		  flags &= ~(SIGNOK | PFXOK | NDIGITS | NNZDIGITS);
		  goto ok;

		  /* digits 8 and 9 ok iff decimal or hex */
		case '8':
		case '9':
		  base = basefix[base];
		  if (base <= 8)
		    break;	/* not legal here */
		  flags &= ~(SIGNOK | PFXOK | NDIGITS | NNZDIGITS);
		  goto ok;

		  /* letters ok iff hex */
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		  /* no need to fix base here */
		  if (base <= 10)
		    break;	/* not legal here */
		  flags &= ~(SIGNOK | PFXOK | NDIGITS | NNZDIGITS);
		  goto ok;

		  /* sign ok only as first character */
		case '+':
		case '-':
		  if (flags & SIGNOK)
		    {
		      flags &= ~SIGNOK;
		      goto ok;
		    }
		  break;

		  /* x ok iff flag still set & 2nd char */
		case 'x':
		case 'X':
		  if (flags & PFXOK && p == buf + 1)
		    {
		      base = 16;/* if %i */
		      flags &= ~PFXOK;
		      /* We must reset the NZDIGITS and NDIGITS
		         flags that would have been unset by seeing
			 the zero that preceded the X or x.  */
		      flags |= NZDIGITS | NDIGITS;
		      goto ok;
		    }
		  break;
		}

	      /*
	       * If we got here, c is not a legal character
	       * for a number.  Stop accumulating digits.
	       */
	      break;
	    ok:
	      /*
	       * c is legal: store it and look at the next.
	       */
	      *p++ = c;
	    skip:
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
		break;		/* EOF */
	    }
	  /*
	   * If we had only a sign, it is no good; push back the sign.
	   * If the number ends in `x', it was [sign] '0' 'x', so push back
	   * the x and treat it as [sign] '0'.
	   */
	  if (flags & NDIGITS)
	    {
	      if (p > buf)
		_CAST_VOID ungetc (*(u_char *)-- p, fp);
	      goto match_failure;
	    }
	  c = ((u_char *) p)[-1];
	  if (c == 'x' || c == 'X')
	    {
	      --p;
	      /*(void)*/ ungetc (c, fp);
	    }
	  if ((flags & SUPPRESS) == 0)
	    {
	      u_long res;

	      *p = 0;
	      res = (*ccfn) (rptr, buf, (char **) NULL, base);
	      if (flags & POINTER)
		*(va_arg (ap, _PTR *)) = (_PTR) (unsigned _POINTER_INT) res;
	      else if (flags & CHAR)
		{
		  cp = va_arg (ap, char *);
		  *cp = res;
		}
	      else if (flags & SHORT)
		{
		  sp = va_arg (ap, short *);
		  *sp = res;
		}
	      else if (flags & LONG)
		{
		  lp = va_arg (ap, long *);
		  *lp = res;
		}
#ifndef _NO_LONGLONG
	      else if (flags & LONGDBL)
		{
		  u_long_long resll;
		  if (ccfn == _strtoul_r)
		    resll = _strtoull_r (rptr, buf, (char **) NULL, base);
		  else
		    resll = _strtoll_r (rptr, buf, (char **) NULL, base);
		  llp = va_arg (ap, long long*);
		  *llp = resll;
		}
#endif
	      else
		{
		  ip = va_arg (ap, int *);
		  *ip = res;
		}
	      nassigned++;
	    }
	  nread += p - buf + skips;
	  break;
	}
#ifdef FLOATING_POINT
	case CT_FLOAT:
	{
	  /* scan a floating point number as if by strtod */
	  /* This code used to assume that the number of digits is reasonable.
	     However, ANSI / ISO C makes no such stipulation; we have to get
	     exact results even when there is an unreasonable amount of
	     leading zeroes.  */
	  long leading_zeroes = 0;
	  long zeroes, exp_adjust;
	  char *exp_start = NULL;
	  unsigned width_left = 0;
#ifdef hardway
	  if (width == 0 || width > sizeof (buf) - 1)
#else
	  /* size_t is unsigned, hence this optimisation */
	  if (width - 1 > sizeof (buf) - 2)
#endif
	    {
	      width_left = width - (sizeof (buf) - 1);
	      width = sizeof (buf) - 1;
	    }
	  flags |= SIGNOK | NDIGITS | DPTOK | EXPOK;
	  zeroes = 0;
	  exp_adjust = 0;
	  for (p = buf; width; )
	    {
	      c = *fp->_p;
	      /*
	       * This code mimicks the integer conversion
	       * code, but is much simpler.
	       */
	      switch (c)
		{

		case '0':
		  if (flags & NDIGITS)
		    {
		      flags &= ~SIGNOK;
		      zeroes++;
		      if (width_left)
			{
			  width_left--;
			  width++;
			}
		      goto fskip;
		    }
		  /* Fall through.  */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		  flags &= ~(SIGNOK | NDIGITS);
		  goto fok;

		case '+':
		case '-':
		  if (flags & SIGNOK)
		    {
		      flags &= ~SIGNOK;
		      goto fok;
		    }
		  break;
		case '.':
		  if (flags & DPTOK)
		    {
		      flags &= ~(SIGNOK | DPTOK);
		      leading_zeroes = zeroes;
		      goto fok;
		    }
		  break;
		case 'e':
		case 'E':
		  /* no exponent without some digits */
		  if ((flags & (NDIGITS | EXPOK)) == EXPOK
		      || ((flags & EXPOK) && zeroes))
		    {
		      if (! (flags & DPTOK))
			{
			  exp_adjust = zeroes - leading_zeroes;
			  exp_start = p;
			}
		      flags =
			(flags & ~(EXPOK | DPTOK)) |
			SIGNOK | NDIGITS;
		      zeroes = 0;
		      goto fok;
		    }
		  break;
		}
	      break;
	    fok:
	      *p++ = c;
	    fskip:
	      width--;
              ++nread;
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
		break;		/* EOF */
	    }
	  if (zeroes)
	    flags &= ~NDIGITS;
	  /*
	   * If no digits, might be missing exponent digits
	   * (just give back the exponent) or might be missing
	   * regular digits, but had sign and/or decimal point.
	   */
	  if (flags & NDIGITS)
	    {
	      if (flags & EXPOK)
		{
		  /* no digits at all */
		  while (p > buf)
                    {
		      ungetc (*(u_char *)-- p, fp);
                      --nread;
                    }
		  goto match_failure;
		}
	      /* just a bad exponent (e and maybe sign) */
	      c = *(u_char *)-- p;
              --nread;
	      if (c != 'e' && c != 'E')
		{
		  _CAST_VOID ungetc (c, fp);	/* sign */
		  c = *(u_char *)-- p;
                  --nread;
		}
	      _CAST_VOID ungetc (c, fp);
	    }
	  if ((flags & SUPPRESS) == 0)
	    {
	      double res = 0;
#ifdef _NO_LONGDBL
#define QUAD_RES res;
#else  /* !_NO_LONG_DBL */
//TMK	      long double qres = 0;
	      long real_double qres = 0;
#define QUAD_RES qres;
#endif /* !_NO_LONG_DBL */
	      long new_exp = 0;

	      *p = 0;
	      if ((flags & (DPTOK | EXPOK)) == EXPOK)
		{
		  exp_adjust = zeroes - leading_zeroes;
		  new_exp = -exp_adjust;
		  exp_start = p;
		}
	      else if (exp_adjust)
                new_exp = _strtol_r (rptr, (exp_start + 1), NULL, 10) - exp_adjust;
	      if (exp_adjust)
		{

		  /* If there might not be enough space for the new exponent,
		     truncate some trailing digits to make room.  */
		  if (exp_start >= buf + sizeof (buf) - MAX_LONG_LEN)
		    exp_start = buf + sizeof (buf) - MAX_LONG_LEN - 1;
                 sprintf (exp_start, "e%ld", new_exp);
		}

	      /* Current _strtold routine is markedly slower than 
	         _strtod_r.  Only use it if we have a long double
	         result.  */
#ifndef _NO_LONGDBL /* !_NO_LONGDBL */
	      if (flags & LONGDBL)
	      	qres = _strtold (buf, NULL);
	      else
#endif
	        res = _strtod_r (rptr, buf, NULL);

	      if (flags & LONG)
		{
//TMK		  dp = va_arg (ap, double *);
		  dp = va_arg (ap, real_double *);
		  *dp = res;
		}
	      else if (flags & LONGDBL)
		{
		  ldp = va_arg (ap, __LONG_DOUBLE *);
		  *ldp = QUAD_RES;
		}
	      else
		{
		  flp = va_arg (ap, float *);
		  *flp = res;
		}
	      nassigned++;
	    }
	  break;
	}
#endif /* FLOATING_POINT */
	}
    }
input_failure:
  _funlockfile (fp);
  return nassigned ? nassigned : -1;
match_failure:
all_done:
  _funlockfile (fp);
  return nassigned;
}
