#include <map>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <set>
#include <ctime>
#include <algorithm>

int Run(int argc, const char* argv[])
{
    // basic repositories of text strings used for benchmarking
    std::vector<std::string> items;

    const int times = atoi(argv[2]);
    
    std::ifstream itemfile(argv[1], std::ifstream::in);

    std::string bulk_items_str;

    // read the file into itemlist
    while(itemfile.good())
    {
        char buffer[20000];
        itemfile.getline(buffer, sizeof(buffer));
        if (itemfile.gcount()) { // not an empty line?
            items.push_back(buffer); // add to itemslist
            (bulk_items_str += "\n") += buffer;
        }
    }

    // sort them for use later in binary_search
    std::sort(items.begin(), items.end());

    std::cout << "Number of elements: " << items.size() << std::endl;
    std::cout << "Length of bulk items string: " << bulk_items_str.size() << std::endl;

    std::set<std::string> test_set(items.begin(), items.end());
    std::unordered_set<std::string> test_hash(items.begin(), items.end());
    
    time_t mark(time(0));
    for(int i = 0; i < times; ++i)
        for (auto item = items.begin(); item != items.end(); ++item)
            test_set.find(*item);
    time_t lap(time(0));
    std::cout << "STL set: " << lap - mark << " seconds" << std::endl;
    
    mark = time(0);
    for(int i = 0; i < times; ++i)
        for (auto item = items.begin(); item != items.end(); ++item)
            test_set.find(*item);
    lap = time(0);
    std::cout << "Character Pointer Map: " << lap - mark << " seconds" << std::endl;
    
    mark = time(0);
    for(int i = 0; i < times; ++i)
        for (auto item = items.begin(); item != items.end(); ++item)
            strstr(bulk_items_str.c_str(), item->c_str());
    lap = time(0);
    std::cout << "strstr:" << lap - mark << " seconds" << std::endl;
    
    mark = time(0);
    for(int i = 0; i < times; ++i)
        for (auto item = items.begin(); item != items.end(); ++item)
            std::binary_search(items.begin(), items.end(), *item);
    lap = time(0);
    std::cout << "sorted vector:" << lap - mark << " seconds" << std::endl;
    
    mark = time(0);
    for(int i = 0; i < times; ++i)
        for (auto item = items.begin(); item != items.end(); ++item)
            test_hash.find(*item);
    lap = time(0);
    std::cout << "hash set:" << lap - mark << " seconds" << std::endl;
    
    return 0;
}


int main(int argc, const char* argv[])
{
    try
    {
	return Run(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << " seconds" << std::endl;
	return -1;
    }

    return 0;
}

//
// $Id$
//
