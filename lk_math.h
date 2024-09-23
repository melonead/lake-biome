// vector of 3 dimensions
struct v3 {
    float x;
    float y;
    float z;
};

struct v4 {
    float x;
    float y;
    float z;
    float w;
};

// vector of 2 dimensions
struct v2 {
    float x;
    float y;
};

struct m3 {
    struct v3 r1;
    struct v3 r2;
    struct v3 r3;
};

struct m4 {
    struct v4 r1;
    struct v4 r2;
    struct v4 r3;
    struct v4 r4;
};