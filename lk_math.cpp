#include "lk_math.h"

v3 create_vec3(float x, float y, float z) {
    struct v3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

v4 create_vec4(float x, float y, float z, float w) {
    struct v4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

m3 create_mat3(v3 a, v3 b, v3 c) {
    struct m3 m;
    m.r1 = a;
    m.r2 = b;
    m.r3 = c;
    return m;
}

m3 create_mat3(v3 a, v3 b, v3 c) {
    struct m3 m;
    m.r1 = a;
    m.r2 = b;
    m.r3 = c;
    return m;
}

m4 create_mat4(v4 a, v4 b, v4 c, v4 d) {
    struct m4 m;
    m.r1 = a;
    m.r2 = b;
    m.r3 = c;
    m.r4 = d;
    return m;
}

v4 m4xv4(m4 m, v4 v) {
    float x = m.r1.x * v.x + m.r1.y * v.y + m.r1.z * v.z + m.r1.w * v.w;
    float y = m.r2.x * v.x + m.r2.y * v.y + m.r2.z * v.z + m.r2.w * v.w;
    float z = m.r3.x * v.x + m.r3.y * v.y + m.r3.z * v.z + m.r4.w * v.w;
    float w = m.r4.x * v.x + m.r4.y * v.y + m.r4.z * v.z + m.r4.w * v.w;
    return create_vec4(x, y, z, w);
}

v3 m3xv3(m3 m, v3 v) {
    float x = m.r1.x * v.x + m.r1.y * v.y + m.r1.z * v.z;
    float y = m.r2.x * v.x + m.r2.y * v.y + m.r2.z * v.z;
    float z = m.r3.x * v.x + m.r3.y * v.y + m.r3.z * v.z;
    return create_vec3(x, y, z);
}

m4 m4xm4(m4 m, m4 n) {
    struct m4 mt;
    // row 1
    mt.r1.x = m.r1.x * n.r1.x + m.r1.y * n.r2.x + m.r1.x * n.r3.x + m.r1.x * n.r4.x;
    mt.r1.y = m.r1.x * n.r1.y + m.r1.y * n.r2.y + m.r1.y * n.r3.y + m.r1.y * n.r4.y;
    mt.r1.z = m.r1.x * n.r1.z + m.r1.z * n.r2.z + m.r1.z * n.r3.z + m.r1.z * n.r4.z;
    mt.r1.w = m.r1.x * n.r1.w + m.r1.w * n.r2.w + m.r1.w * n.r3.z + m.r1.w * n.r4.w;

    // row 2
    mt.r2.x = m.r2.x * n.r1.x + m.r2.y * n.r2.x + m.r2.x * n.r3.x + m.r2.x * n.r4.x;
    mt.r2.y = m.r2.x * n.r1.y + m.r2.y * n.r2.y + m.r2.y * n.r3.y + m.r2.y * n.r4.y;
    mt.r2.z = m.r2.x * n.r1.z + m.r2.z * n.r2.z + m.r2.z * n.r3.z + m.r2.z * n.r4.z;
    mt.r2.w = m.r2.x * n.r1.w + m.r2.w * n.r2.w + m.r2.w * n.r3.z + m.r2.w * n.r4.w;

    // row 3
    mt.r3.x = m.r3.x * n.r1.x + m.r3.y * n.r2.x + m.r3.x * n.r3.x + m.r3.x * n.r4.x;
    mt.r3.y = m.r3.x * n.r1.y + m.r3.y * n.r2.y + m.r3.y * n.r3.y + m.r3.y * n.r4.y;
    mt.r3.z = m.r3.x * n.r1.z + m.r3.z * n.r2.z + m.r3.z * n.r3.z + m.r3.z * n.r4.z;
    mt.r3.w = m.r3.x * n.r1.w + m.r3.w * n.r2.w + m.r3.w * n.r3.z + m.r3.w * n.r4.w;

    // row 4
    mt.r4.x = m.r4.x * n.r1.x + m.r4.y * n.r2.x + m.r4.x * n.r3.x + m.r4.x * n.r4.x;
    mt.r4.y = m.r4.x * n.r1.y + m.r4.y * n.r2.y + m.r4.y * n.r3.y + m.r4.y * n.r4.y;
    mt.r4.z = m.r4.x * n.r1.z + m.r4.z * n.r2.z + m.r4.z * n.r3.z + m.r4.z * n.r4.z;
    mt.r4.w = m.r4.x * n.r1.w + m.r4.w * n.r2.w + m.r4.w * n.r3.z + m.r4.w * n.r4.w;

    return mt;

}

m3 m3xm3(m3 m, m3 n) {
    struct m3 mt;
    // row 1
    mt.r1.x = m.r1.x * n.r1.x + m.r1.y * n.r2.x + m.r1.x * n.r3.x;
    mt.r1.y = m.r1.x * n.r1.y + m.r1.y * n.r2.y + m.r1.y * n.r3.y;
    mt.r1.z = m.r1.x * n.r1.z + m.r1.z * n.r2.z + m.r1.z * n.r3.z;

    // row 2
    mt.r2.x = m.r2.x * n.r1.x + m.r2.y * n.r2.x + m.r2.x * n.r3.x;
    mt.r2.y = m.r2.x * n.r1.y + m.r2.y * n.r2.y + m.r2.y * n.r3.y;
    mt.r2.z = m.r2.x * n.r1.z + m.r2.z * n.r2.z + m.r2.z * n.r3.z;

    // row 3
    mt.r3.x = m.r3.x * n.r1.x + m.r3.y * n.r2.x + m.r3.x * n.r3.x;
    mt.r3.y = m.r3.x * n.r1.y + m.r3.y * n.r2.y + m.r3.y * n.r3.y;
    mt.r3.z = m.r3.x * n.r1.z + m.r3.z * n.r2.z + m.r3.z * n.r3.z;

    return mt;

}

m4 unit_m4() {
    struct m4 m;
    m.r1.x = 1.0f;
    m.r2.y = 1.0f;
    m.r3.z = 1.0f;
    m.r4.w = 1.0f;
    return m;
}

v4 translate(m4 m, v4 v) {
    
}

v4 scale(m4 m, v4 v) {

}

v4 rotate(m4 m, v4 v) {

}

