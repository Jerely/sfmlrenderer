#include "mtx44.h"

Mtx44::Mtx44() :
    m{0} {};

Mtx44 Mtx44::operator *(const Mtx44& mat) {
    Mtx44 result;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for(int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * mat.m[k][j];
            }
        }
    }
    return result;
}

