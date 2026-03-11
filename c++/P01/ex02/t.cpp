#include <iostream>
#include <cmath>
#include <string>

using namespace std;

/**
 *  transforms power from w to kW
 *  parameter: int w - power in watts
 *  return: float calculated value
 */
float power_transform(int w) {

    float KW = w * pow(10,-3);
    return KW;
}

int main()
{
    int w = 5200;
    

	float kw = power_transform(w);

    cout << "\n Power = " << kw << "kW";

    return 0;
}

