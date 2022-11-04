#include <iostream>
#include <fstream>
#include <map>
#include<stdlib.h>
#include <vector>
#include<bitset>
#include<queue>
#include"PROJECT-A.h"
using namespace std;




int main()
{
   
    priority_queue<Tree*, vector<Tree*>, Order> p1;
    fillMap(p1);

    createTree(p1);

    createCode(p1);

    return 0;
}