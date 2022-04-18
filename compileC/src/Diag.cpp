//
// Created by yifeng on 2022/4/8.
//

#include "Diag.h"
#include <iostream>

namespace C100 {
    void DiagError(std::string_view code, sourceLocation location , const char *fmt ...) {
        va_list ap;
        va_start(ap, fmt);
        std::cerr << code << std::endl;
        fprintf(stderr, "%*s^ ", location.col, "");
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
        va_end(ap);
        exit(0);
    }
}