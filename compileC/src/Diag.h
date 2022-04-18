//
// Created by yifeng on 2022/4/8.
//

#ifndef COMPILEC_DIAG_H
#define COMPILEC_DIAG_H

#include <string_view>
#include "Lexer.h"

namespace C100 {
    void DiagError(std::string_view code, sourceLocation location, const char *fmt ...);
}


#endif //COMPILEC_DIAG_H
