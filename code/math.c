static int clamp(int val,int min, int max)
{
    int ret_val = val;
    if(val < min) ret_val = min;
    if(val > max) ret_val = max;
    
    return ret_val;
}

typedef struct
{
    union
    {
        struct{
            f32 x;
            f32 y;
        };
        f32 e[2];
    };
    
}v2;