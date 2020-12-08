#include <iostream>

#include "VLVector.hpp"
#include <vector>
#include <algorithm>

#define SIZE 20
struct myclass {
    bool operator() (int i,int j) { return (i<j);}
} myobject;
//int main()
//{
//
//**
// * Push and pop
// */
//    VLVector<int> a;
//    for (int i = 1; i < 38; ++i)
//    {
//        a.push_back(i);
//    }
//    a.pop_back();
//    a.pop_back();
//    for (int i = 0; i < 35; ++i)
//    {
//        std::cout << a[i] << std::endl;
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << a.size() << std::endl;
//    std::cout << a.capacity() << std::endl;
//    a.clear();


/**
 * Insert 1
 */
//    VLVector<int> b;
//    for (int i = 20; i > 0; --i)
//    {
//        b.push_back(i);
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    auto temp = b.begin();
//    for (int i = 0; i < 3; ++i)
//    {
//        temp++;
//    }
//    auto c = b.insert(temp, 1000);
//    std::sort(b.begin(), b.end(), myobject);
//    for (auto & it : b)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    std::cout << "return:  " << *c << std::endl;


///**
// * Erase 1
// */
//    VLVector<int> b;
//    for (int i = 1; i <= SIZE; ++i)
//    {
//        b.push_back(i);
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    auto temp = b.begin();
//    for (int i = 0; i < 3; ++i)
//    {
//        temp++;
//    }
//    auto c = b.erase(temp);
//    for (auto & it : b)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    std::cout << "return:  " << *c << std::endl;

///**
// * Erase 2, begin, end
// */
//    VLVector<int> b;
//    for (int i = 1; i <= SIZE; ++i)
//    {
//        b.push_back(i);
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    auto temp = b.begin();
//    auto first = temp;
//    for (int i = 0; i < 3; ++i)
//    {
//        temp++;
//    }
//    auto c = b.erase(first, temp);
//    for (auto & it : b)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    std::cout << "return:  " << *c << std::endl;



//**
// * Iterator
// */
//    for (auto & it : a)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << a.size() << std::endl;
//    std::cout << a.capacity() << std::endl;




///**
// * ==, !=, []
// */
//    VLVector<int> b;
//    for (int i = 1; i <= SIZE; ++i)
//    {
//        b.push_back(i);
//    }
//    VLVector<int, 16> a = b;
//    std::cout << (a == b) << std::endl;   //true 1
//    b[1] = 7;
//    std::cout << (a == b) << std::endl;   // false 0
//    b[1] = 2;
//    std::cout << (a == b) << std::endl;    // true 1
//    b.pop_back();
//    std::cout << (a == b) << std::endl;    // false 0

///**
// * Copy constructor
// */
//    VLVector<int> b;
//    for (int i = 1; i <= SIZE; ++i)
//    {
//        b.push_back(i);
//    }
//    VLVector<int, 16> a = b;
//    for (auto & it : a)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << a.size() << std::endl;
//    std::cout << a.capacity() << std::endl;

/**
 * insert 2
 */
//    std::vector<int> b;
//    b.push_back(0);
//    b.push_back(1);
//    b.push_back(2);
//    b.push_back(3);
//    for (int i = 7; i <= 250; ++i)
//    {
//        b.push_back(i);
//    }
//    std::vector<int> c ={4,5,6};
//    auto first = c.begin();
//    auto last = c.end();
//    b.insert(b.begin()+4,first, last);
//    for (auto & it : b)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << b.size() << std::endl;
//    std::cout << b.capacity() << std::endl;
//    b.clear();
//    std::cout << b.empty() << std::endl;

/**
 * Constructor  1
 */
//    std::vector<int> b;
//    for (int i = 1; i <= SIZE; ++i)
//    {
//        b.push_back(i);
//    }
//    auto first = b.begin();
//    auto last = b.end();
//    VLVector<int> a(first, last);
//    for (auto & it : a)
//    {
//        std::cout << (it) << std::endl;
//
//    }
//    std::cout << "size:" << std::endl;
//    std::cout << a.size() << std::endl;
//    std::cout << a.capacity() << std::endl;
//    a.clear();
//    std::cout << a.empty() << std::endl;

//    return 0;
//}


/**
 * test 1
 */
int testDefaultCtor()
{
    VLVector<int> a;
    std::vector<int> b;
    if (!a.empty())
    {
        return EXIT_FAILURE;
    }
    for (unsigned int i = 0; i < 6678; i++)
    {
        a.push_back(i);
        b.push_back(i);
        if (a[i] != i || a.at(i) != i || a.size() != i + 1)
        {
            return EXIT_FAILURE;
        }
    }
    if (a.empty())
    {
        return EXIT_FAILURE;
    }
    if (a[6677] != 6677 || a.at(6677) != 6677 || a.size() != 6678)
    {
        return EXIT_FAILURE;
    }
    for (unsigned int i = 0; i < 6678; i++)
    {
        a.pop_back();
    }
    if (!a.empty())
    {
        return EXIT_FAILURE;
    }
    if (a.size() != 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * test dsdfvzdg
 */
int testnoa()
{
    VLVector<int> a;
    for (unsigned int i = 0; i < 5546; i++)
    {
        a.push_back(i);
        if (a[i] != i || a.at(i) != i || a.size() != i + 1)
        {
            return EXIT_FAILURE;
        }
    }
    if (a.size() != 5546)
    {
        return EXIT_FAILURE;
    }
    for (unsigned int i = 2; i < 5546; i++)
    {
        if (a[i] != i || a.at(i) != i)
        {

            return EXIT_FAILURE;
        }
    }
    for (unsigned int i = 0; i < 5546; i++)
    {
        auto iter = a.erase(a.end() - 1);
        if (a.size() != 5546 - i + 1)
        {
            return EXIT_FAILURE;
        }

        if (iter != a.end())
        {
            return EXIT_FAILURE;
        }
    }
}
/**
 * test 2
 */
int testCopyCtor()
{
    VLVector<int> a;
    for (unsigned int i = 0; i < 5546; i++)
    {
        a.push_back(i);
        if (a[i] != i || a.at(i) != i || a.size() != i + 1)
        {
            return EXIT_FAILURE;
        }
    }
    VLVector<int> b = a;
    if (b.capacity() != a.capacity() || b.size() != a.size())
    {
        return EXIT_FAILURE;
    }
    if (a != b)
    {
        return EXIT_FAILURE;
    }

    VLVector<int> c;
    c = b;
//    if (c != b)
//    {
//        return EXIT_FAILURE;
//    }
//    a[1] = 5;
//    if (a[1] != 5)
//    {
//        return EXIT_FAILURE;
//    }
    if (a.size() != 5546)
    {
        return EXIT_FAILURE;
    }
    for (unsigned int i = 2; i < 5546; i++)
    {
        if (a[i] != i || a.at(i) != i)
        {

            return EXIT_FAILURE;
        }
    }
    for (unsigned int i = 2; i < 5546; i++)
    {
        if (i == 5542)
        {
            std::cout <<"5542";
        }
        auto iter = a.erase(a.end() - 1);
        if (a.size() != 5546 - i + 1)
        {
            return EXIT_FAILURE;
        }

        if (iter != a.end())
        {
            return EXIT_FAILURE;
        }
    }
    a.clear();
    for (int i = 100; i >= 0; i--)
    {
        if (i == 76)
        {
            std::cout << i <<std::endl;
        }
        auto iter = a.insert(a.begin(), i);
        if (*iter != i || iter != a.begin())
        {
            return EXIT_FAILURE;
        }
    }
    auto it = a.begin();
    while (it !=a.end())
    {
        std::cout << "hh: "<<*(it) <<std::endl;
        it++;
    }

    for (size_t i = 0; i <=100; i++)
    {
        std::cout <<i;
        if (a[i] != i)
        {
            return EXIT_FAILURE;
        }
    }
    if (a.empty())
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * test 3
 */
int testCtorOne()
{
    std::vector<int> b;
    for (size_t i = 0; i < 2000; i++)
    {
        b.push_back(i);
    }
    auto first = b.begin();
    for (size_t i = 0; i < 50; i++)
    {
        first++;
    }
    VLVector<int> a(first, b.end());
    for (size_t i = 50; i < 2000; i++)
    {
        if (a[i - 50] != i || a.at((long) i - 50) != i)
        {
            return EXIT_FAILURE;
        }
    }
    b.clear();
    a.clear();
    if (!a.empty() || !b.empty())
    {
        return EXIT_FAILURE;
    }
    a.push_back(1);
    a.push_back(2);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    a.push_back(10);
    a.push_back(11);
    a.push_back(12);
    a.push_back(13);
    a.push_back(14);
    a.push_back(15);
    a.push_back(16);
    a.push_back(17);
    a.push_back(18);
    a.push_back(19);
    a.push_back(20);
    a.push_back(21);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);
    auto iter = a.begin() + 100;
    iter--;
    iter++;
    iter -= 5;
    iter += 5;
    iter -= 100;
    auto iter2 = a.begin() + 2;
    iter + 2;
    auto check = a.insert(iter2, b.begin(), b.end());
    if(*check != a[2] || *check != 3)
    {
        return EXIT_FAILURE;
    }
    for (size_t i = 1; i < 22; i++)
    {
        if (a[i - 1] != i || a.at((int) i - 1) != i)
        {
            return EXIT_FAILURE;
        }
    }
    if (!(iter > a.begin()) || (iter <= a.begin()) || !(a.begin() < iter))
    {
        return EXIT_FAILURE;
    }
    auto res = a.erase(a.begin() + 2, a.end() - 15);
    if (a.size() != 17 || a.empty())
    {
        return EXIT_FAILURE;
    }
    if (*res != 7)
    {
        return EXIT_FAILURE;
    }
    if (a.at(0) != 1 || a[1] != 2)
    {
        return EXIT_FAILURE;
    }
    for (size_t i = 2; i < 16; i++)
    {
        if (a[i] != i + 5 || a.at(i) != i + 5)
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

bool isTrue(size_t i)
{
    return i;
}


bool IsOdd(int i)
{
    return ((i % 2) == 1);
}

/**
 * test 4
 */
int testSTLAlgorithms()
{
    VLVector<int> a;
    for (size_t i = 0; i < 4444; i++)
    {
        //auto iter = a.insert(a.begin() + i, i);
        a.push_back(i);
        if (a[i] != i)
        {
            return EXIT_FAILURE;
        }
    }
    std::sort(a.begin(), a.end(), myobject);
    if (!std::any_of(a.begin(), a.end(), isTrue)) return EXIT_FAILURE;
    if( std::all_of(a.begin(), a.end(), isTrue)) return EXIT_FAILURE;
    if(std::none_of(a.begin(), a.end(), isTrue)) return EXIT_FAILURE;

    for (int i: a)
    {
       // std::cout <<"i :"<<i<<std::endl;
        if (a[i] != i || a.at(i) != i)
        {
            return EXIT_FAILURE;
        }
    }
    VLVector<int> b;
//    std::copy_backward(a.begin(), a.end(), b.end());
//    for (size_t i = 4443; i >= 0; i--)
//    {
//        if (b[i] != i)
//        {
//            return EXIT_FAILURE;
//        }
//    }
    std::sort(b.begin(), b.end(), myobject);
    for (size_t i = 0; i < 4444; i++)
    {
        if (a[i] != i || a.at(i) != i)
        {
            return EXIT_FAILURE;
        }
    }
    std::replace_if(a.begin(), a.end(), IsOdd, 0);
    for (size_t i = 0; i < 4444; i++)
    {
        if (IsOdd(i) && a[i] != 0)
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

//
int main()
{
    testnoa();
    if (testDefaultCtor())
    {
        std::cout << "Failure in test 1" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Passed test 1" << std::endl;
    }
//    if (testCopyCtor())
//    {
//        std::cout << "Failure in test 2" << std::endl;
//        return EXIT_FAILURE;
//    }
//    else
//    {
//        std::cout << "Passed test 2" << std::endl;
//    }
    if (testCtorOne())
    {
        std::cout << "Failure in test 3" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Passed test 3" << std::endl;
    }
    if (testSTLAlgorithms())
    {
        std::cout << "Failure in test 4" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Passed test 4" << std::endl;
    }
    std::cout << "Passed all tests :-))))))))" << std::endl;
    return EXIT_SUCCESS;
}

//int main()
//{
//    VLVector<int> from_vector;
//    for (int i = 0; i < 10; i++) {
//        from_vector.push_back(i);
//    }
//
//    VLVector<int> to_vector;
//    for (int i = 0; i < 14; i++) {
//        from_vector.push_back(0);
// /    }
//
//    std::copy_backward(from_vector.begin(), from_vector.begin()+10, to_vector.end());
//
//    std::cout << "to_vector contains: ";
//    for (auto i: to_vector) {
//        std::cout << i << " ";
//    }
//}