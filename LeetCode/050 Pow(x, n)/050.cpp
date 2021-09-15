class Solution {
public:
    double myPow(double x, int n) {
    if(0 == n)
        return  1.0;
    if(x == 1.0)
        return 1.0;
    if(x == -1.0)
        return n % 2 ? -1.0 : 1.0;
    if(0 == x)
        return 0;
        
    if(n < 0)
    {
        if(INT_MIN == n)
            return 1/ x / myPow(x,INT_MAX);
        else
            return 1 / myPow(x,-n);
    }
    else
    {
        if(1 == n)
            return x;
        if(2 == n)
            return x*x;
    
        return n % 2 ? myPow(x*x,n >> 1)*x : myPow(x*x,n >> 1);
    }
}
};