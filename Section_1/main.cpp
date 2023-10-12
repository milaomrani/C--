#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::vector<int> v1;
    std::vector<int> v2;

    v1.push_back(10);
    v1.push_back(20);

    v2.push_back(100);
    v2.push_back(200);

    std::cout << "v1[0] = " << v1[0] << std::endl;
    std::cout << "v1[1] = " << v1[1] << std::endl;

    std::cout << "v2[0] = " << v2[0] << std::endl;
    std::cout << "v2[1] = " << v2[1] << std::endl;

    std::vector<std::vector <int>> v_2d;
    v_2d.push_back(v1);
    std::cout << "v_2d[0][0] = " << v_2d.at(0).at(0) << std::endl;
    v_2d.push_back(v2);
    std::cout << "v_2d[0][1] = " << v_2d.at(1).at(0) << std::endl;

    std::cout << "v_2d[1][0] = " << v_2d.at(1).at(0) << std::endl;
    std::cout << "v_2d[1][1] = " << v_2d.at(1).at(1) << std::endl;

    v1.at(0) = 1000;

    std::cout << "v_2d[0][0] = " << v_2d.at(0).at(1) << std::endl;
    std::cout << "v_2d[0][1] = " << v_2d.at(1).at(1) << std::endl;
   
    
    return EXIT_SUCCESS;
}