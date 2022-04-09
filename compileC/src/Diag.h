//
// Created by yifeng on 2022/4/8.
//

#ifndef COMPILEC_DIAG_H
#define COMPILEC_DIAG_H

#include <string_view>

namespace C100 {
    void DiagError(std::string_view code, int line, int col, const char *fmt ...);
}


#endif //COMPILEC_DIAG_H
