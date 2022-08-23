#include <stdio.h>
#include <string.h>

/*
https://leetcode.cn/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/solution/mian-shi-ti-10-ii-qing-wa-tiao-tai-jie-wen-ti-dong/
*/
int numWays(int n) {
    if (n < 0 || n > 100) {
        return 0;
    }

    if (0 == n || 1 == n) {
        return 1;
    }

    int dp[101] = {0};
    memset(dp, 0x00, sizeof(dp));
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i < (n+1); i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % 1000000007;
    }

    return dp[n];
}

int main(void)
{
    fprintf(stdout, "numWays(3): %d\n", numWays(3));
    fprintf(stdout, "numWays(4): %d\n", numWays(4));
    fprintf(stdout, "numWays(5): %d\n", numWays(5));
    fprintf(stdout, "numWays(6): %d\n", numWays(6));
    return 0;
}
