#ifndef _OUT_H_
#define _OUT_H_

#ifdef _WIN32
# include "OutWin32.h"
#else
# include "OutLinux.h"
#endif /* _WIN32 */

extern Out _out;

#endif /* _OUT_H_ */
