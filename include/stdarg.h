#ifndef LUMAOS_STDARG_H_
#define LUMAOS_STDARG_H_

#pragma once

typedef char *va_list;

#define va_start(ap,parmn) (void)((ap) = (char*)(&(parmn) + 1))
#define va_end(ap) (void)((ap) = 0)
#define va_arg(ap, type) \
    (((type*)((ap) = ((ap) + sizeof(type))))[-1])
    
#endif
