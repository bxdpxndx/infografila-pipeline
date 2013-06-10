#ifndef Utils_hpp
#define Utils_hpp


// Interpolate funcions. reverse interpolate returns a float such that
// if a, b anc c are floats, then
// c == interpolate(a, b, reverse_interpolate(a, b, c));
template <typename T>
T interpolate (const T & t1, const T & t2, float value) {
    return (t2 * value) + (t1 * ( 1.0 - value));
}

float reverse_interpolate(float t1, float t2, float t3) {
    float ret = (t1 - t3)/(t1 - t2);
    return ret;
}

#endif

