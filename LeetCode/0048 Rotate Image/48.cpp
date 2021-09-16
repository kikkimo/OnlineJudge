class Solution {
public:
    void rotate(vector<vector<int>> &matrix) {
        int len = matrix.size();
        if (len <= 1)
            return;
        for (int i = 0; i < len / 2; ++i) // col
        {
            auto temp = 0;
            for (int j = len - 1 - i; j > i; --j) // row
            {
                auto temp = matrix[ j ][ i ];
                //   A[3][0] = A[3][3];
                //   A[2][0] = A[3][2];
                //   A[1][0] = A[3][1];
                matrix[ j ][ i ] = matrix[ len - i - 1 ][ j ];
                //   A[3][3] = A[0][3];
                //   A[3][2] = A[1][3];
                //   A[3][1] = A[2][3];
                matrix[ len - i - 1 ][ j ] = matrix[ len - j - 1 ][ len - i - 1 ];
                //   A[0][3] = A[0][0];
                //   A[1][3] = A[0][1];
                //   A[2][3] = A[0][2];
                matrix[ len - j - 1 ][ len - i - 1 ] = matrix[ i ][ len - j - 1 ];
                //   A[0][0] = A[3][0];
                //   A[0][1] = A[2][0];
                //   A[0][2] = A[1][0];
                matrix[ i ][ len - j - 1 ] = temp; // matrix[ j ][ i ]
            }
        }
    }
};