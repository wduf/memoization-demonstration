#include <chrono>
#include <iostream>
#include <unordered_map>

using namespace std;

class MemoDemo
{  // memoization demonstration
    public:
        unordered_map<int, int> m;

        int tri_normal(int n)
        {
            if(n < 2)
            {
                return n;
            }
            return (n + tri_normal(n - 1));
        }

        int tri_memo(int n)
        {
            if(n < 2)
            {
                return n;
            }
            if(m.count(n) != 0)
            {  // check if answer is in cache
                return m[n];
            }
            // not in cache
            m[n] = (n + tri_memo(n - 1));
            return m[n];
        }
};

using namespace chrono;

int main()
{  // print all triangle numbers between 0 and n, time both functions
    int n = 10000;
    printf("calculating all triangle numbers between 0 and %d\n\n", n);
    MemoDemo* md = new MemoDemo();
    // first, no memo approach
    auto start = high_resolution_clock::now();
    for(int i = 0; i <= n; i++)
    {
        md->tri_normal(i);
    }
    auto stop = high_resolution_clock::now();
    auto time1 = duration_cast<microseconds>(stop - start);
    // second, memo approach
    start = high_resolution_clock::now();
    for(int i = 0; i <= n; i++)
    {
        md->tri_memo(i);
    }
    stop = high_resolution_clock::now();
    auto time2 = duration_cast<microseconds>(stop - start);
    printf("times:\nwithout memo:\t%ld microseconds\nwith memo:\t\t%ld microseconds\n\n", time1, time2);
    printf("tri_memo() was %dx faster", ((time1) / time2));
    return 0;
}
