#include <iostream>

#include "Unordered_MultiSet.h"

int main() 
{
    Unordered_Multiset<int> ms;

    ms.insert(1);
    ms.insert(2);
    ms.insert(2);
    ms.insert(3);
    ms.insert(3);
    ms.insert(3);

    std::cout << "After inserts (should be 6): " << ms.size() << "\n";

    std::cout << "Count 1: " << ms.count(1) << "\n"; // 1
    std::cout << "Count 2: " << ms.count(2) << "\n"; // 2
    std::cout << "Count 3: " << ms.count(3) << "\n"; // 3
    std::cout << "Count 4: " << ms.count(4) << "\n"; // 0

    std::cout << std::boolalpha;
    std::cout << "Contains 2: " << (ms.find(2) == ms.end()) << "\n"; // true
    std::cout << "Contains 5: " << (ms.find(5) == ms.end()) << "\n"; // false

    auto [first, last] = ms.equal_range(3);
    std::cout << "Elements equal to 3:\n";
    for (auto it = first; it != last; ++it)
        std::cout << *it << " ";

    std::cout << "\n";

    ms.erase(*(ms.find(2)));
    std::cout << "Count 2 after erase one: " << ms.count(2) << "\n"; // 1

    ms.erase(3);
    std::cout << "Count 3 after full erase: " << ms.count(3) << "\n"; // 0

    Unordered_Multiset<int> copy = ms;
    std::cout << "Copy size: " << copy.size() << "\n";

    Unordered_Multiset<int> other;
    other.insert(100);
    other.insert(200);
    ms.swap(other);
    std::cout << "After swap, ms contains:\n";
    for (int x : ms) std::cout << x << " ";
        std::cout << "\n";

    ms.clear();
    std::cout << "Size after clear: " << ms.size() << "\n";

    return 0;
}
