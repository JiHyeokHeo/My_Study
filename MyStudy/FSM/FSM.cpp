#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    int multi;
    cin >> N;
    vector<int> value;
    for (int i = 0; i < N; i++)
    {
        cin >> multi;
        value.push_back(multi);
    }

    sort(value.begin(), value.end());

    if (N == 1)
    {
        cout << value[0] * value[0];
    }
    else
    {
        int first = 0;
        int second = 0;
        first = value.front();
        second = value.back();

        cout << first * second;
    }


    return 0;
}