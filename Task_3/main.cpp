#include "hashTableOA.h"
#include "mySet.h"

using namespace std;

int main() {
    
    mySet<int> A;
    A.insert(1);
    A.insert(2);
    A.insert(3);

    mySet<int> B;
    B.insert(3);
    B.insert(4);
    B.insert(5);

    auto C = A.unionWith(B);
    auto D = A.intersectWith(B);
    auto E = A.differenceWith(B);

    cout << "Union:\n"; C.print();
    cout << "Intersection:\n"; D.print();
    cout << "Difference:\n"; E.print();

    return 0;
}