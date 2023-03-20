#include <iostream>
#include <string>

#include "p3.h"

int main(int argc, char *argv[]) {
    bool printPrompts = true;
    if (argc == 2 && std::string(argv[1]) == "no") {
        printPrompts = false;
    }

    PersonList *list = new PersonList();

    std::string cmd, first, last, newFirst, newLast;
    int h, w;
    while (1) {
        if (printPrompts) std::cout << "Enter a command or \"help\" to get a command list: ";
        std::cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "add") {
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (printPrompts) std::cout << "\tEnter height: ";
            std::cin >> h;
            if (printPrompts) std::cout << "\tEnter weight: ";
            std::cin >> w;
            if (!list->add(first, last, h, w))
            {
                std::cout << "Error: " << first << " " << last << " already exists in the list" << std::endl;
            }
        }
        else if (cmd == "size") {
            std::cout << "\nThere are " << list->getSize() << " persons in the list" << std::endl;
        }
        else if (cmd == "printByHeight") {
            list->printByHeight(std::cout);
            std::cout << std::endl;
        }
        else if (cmd == "printByWeight") {
            list->printByWeight(std::cout);
            std::cout << std::endl;
        }
        else if (cmd == "search") {
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (!list->exists(first, last)) {
                std::cout << first << " " << last << " does not exist in the list" << std::endl;
            }
            else {
                std::cout << first << " " << last << ": height=" << list->getHeight(first, last);
                std::cout << ", weight=" << list->getWeight(first, last) << std::endl;
            }
        }
        else if (cmd == "updateName") {
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (printPrompts) std::cout << "\tEnter new first name: ";
            std::cin >> newFirst;
            if (printPrompts) std::cout << "\tEnter new last name: ";
            std::cin >> newLast;
            if (!list->updateName(first, last, newFirst, newLast))
            {
                std::cout << "Error: " << first << " " << last << " does not exist in the list" << std::endl;
            }
        }
        else if (cmd == "remove") {
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (!list->remove(first, last))
            {
                std::cout << "Error: " << first << " " << last << " does not exist in the list" << std::endl;
            }
        }
        else if (cmd == "updateHeight") {
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (printPrompts) std::cout << "\tEnter new height: ";
            std::cin >> h;
            if (!list->updateHeight(first, last, h))
            {
                std::cout << "Error: " << first << " " << last << " does not exist in the list" << std::endl;
            }
        }
        else if (cmd == "updateWeight") {
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (printPrompts) std::cout << "\tEnter new weight: ";
            std::cin >> w;
            if (!list->updateWeight(first, last, w))
            {
                std::cout << "Error: " << first << " " << last << " does not exist in the list" << std::endl;
            }
        }
        else if (cmd == "destroy") {
            delete list;
            list = new PersonList();
        }
        else if (cmd == "copycon" || cmd == "copy=") {
            PersonList *list2;
            if (cmd == "copycon")
            {
                list2 = new PersonList(*list);
            }
            else
            {
                list2 = new PersonList();
                *list2 = *list;
            }

            std::cout << "Original list by height:" << std::endl;
            list->printByHeight(std::cout);
            std::cout << std::endl << "Original list by weight:" << std::endl;
            list->printByWeight(std::cout);
            std::cout << std::endl;

            std::cout << "Copied list by height:" << std::endl;
            list2->printByHeight(std::cout);
            std::cout << std::endl << "Copied list by weight:" << std::endl;
            list2->printByWeight(std::cout);
            std::cout << std::endl;

            if (printPrompts) std::cout << "\tAdd person to copied list:" << std::endl;
            if (printPrompts) std::cout << "\tEnter first name: ";
            std::cin >> first;
            if (printPrompts) std::cout << "\tEnter last name: ";
            std::cin >> last;
            if (printPrompts) std::cout << "\tEnter height: ";
            std::cin >> h;
            if (printPrompts) std::cout << "\tEnter weight: ";
            std::cin >> w;
            if (!list2->add(first, last, h, w))
            {
                std::cout << "Error: " << first << " " << last << " already exists in the list" << std::endl;
            }

            std::cout << std::endl << "Original list by height:" << std::endl;
            list->printByHeight(std::cout);
            std::cout << std::endl << "Original list by weight:" << std::endl;
            list->printByWeight(std::cout);
            std::cout << std::endl;

            std::cout << "Copied list by height:" << std::endl;
            list2->printByHeight(std::cout);
            std::cout << std::endl << "Copied list by weight:" << std::endl;
            list2->printByWeight(std::cout);
            std::cout << std::endl;

            delete list2;
        }
        else if (cmd == "help") {
            std::cout << "Valid commands:" << std::endl;
            std::cout << "***** add" << std::endl;
            std::cout << "***** size" << std::endl;
            std::cout << "***** printByHeight" << std::endl;
            std::cout << "***** printByWeight" << std::endl;
            std::cout << "***** search" << std::endl;
            std::cout << "***** remove" << std::endl;
            std::cout << "***** updateName" << std::endl;
            std::cout << "***** updateHeight" << std::endl;
            std::cout << "***** updateWeight" << std::endl;
            std::cout << "***** destroy" << std::endl;
            std::cout << "***** copycon" << std::endl;
            std::cout << "***** copy=" << std::endl;
            std::cout << "***** help" << std::endl;
            std::cout << "***** quit" << std::endl;
        }
        else {
            if (printPrompts) std::cout << "Invalid command specified - " << cmd << std::endl;
        }
        if (printPrompts) std::cout << std::endl;
    }
    return 0;
}
