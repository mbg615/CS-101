#include <iostream>
#include <string>

#include "p3.h"

#define DEBUG true

using namespace std;

Person::Person() {
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight) {
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList() {
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize() {
    return size;
}

void PersonList::printByHeight(ostream &os) {
    for(Person *curNode = headHeightList; curNode != nullptr; curNode = curNode->nextHeight) {
        os << curNode->first << " " << curNode->last << ": height=" << curNode->height << ", weight=" << curNode->weight << "\n";
    }
}

void PersonList::printByWeight(ostream &os) {
    for(Person *curNode = headWeightList; curNode != nullptr; curNode = curNode->nextWeight) {
        os << curNode->first << " " << curNode->last << ": height=" << curNode->height << ", weight=" << curNode->weight << "\n";
    }
}

bool PersonList::exists(string first, string last) {
    for(Person *curNode = headHeightList; curNode != nullptr; curNode = curNode->nextHeight) {
        if(curNode->first == first && curNode->last == last) {
            return true;
        }
    }
    return false;
}

int PersonList::getHeight(string first, string last) {
    for(Person *curNode = headHeightList; curNode != nullptr; curNode = curNode->nextHeight) {
        if(curNode->first == first && curNode->last == last) {
            return curNode->height;
        }
    }
    return -1;
}

int PersonList::getWeight(string first, string last) {
    for(Person *curNode = headWeightList; curNode != nullptr; curNode = curNode->nextWeight) {
        if(curNode->first == first && curNode->last == last) {
            return curNode->weight;
        }
    }
    return -1;
}

bool PersonList::add(std::string first, std::string last, int height, int weight) {
    // Doesn't work for all cases: Final Grade: 88/100

    if(this->exists(first, last)) {
        return false;
    }

    Person *newPerson = new Person(first, last, height, weight);

    if(size == 0) {
        newPerson->nextHeight = this->headHeightList;
        this->headHeightList = newPerson;
        newPerson->nextHeight = nullptr;

        newPerson->nextWeight = this->headWeightList;
        this->headWeightList = newPerson;
        newPerson->nextWeight = nullptr;

        size++;
        return true;
    }

    if(newPerson->height > this->headHeightList->height) {
        newPerson->nextHeight = this->headHeightList;
        this->headHeightList = newPerson;
    } else if(newPerson->height < this->headHeightList->height && this->headHeightList->nextHeight == nullptr) {
        this->headHeightList->nextHeight = newPerson;
        newPerson->nextHeight = nullptr;
    } else if(newPerson->height == this->headHeightList->height) {
        if(newPerson->weight == this->headHeightList->weight || newPerson->weight > this->headHeightList->weight) {
            newPerson->nextHeight = this->headHeightList->nextHeight;
            this->headHeightList->nextHeight = newPerson;
        } else if(newPerson->weight < this->headHeightList->weight) {
            newPerson->nextHeight = this->headHeightList;
            this->headHeightList = newPerson;
        }
    } else {
        Person *prevNode = this->headHeightList;
        for(Person *curNode = this->headHeightList->nextHeight; curNode != nullptr; curNode = curNode->nextHeight) {
            if(newPerson->height < curNode->height && curNode->nextHeight != nullptr) {
                prevNode = curNode;
                continue;
            } else if(newPerson->height < curNode->height && curNode->nextHeight == nullptr) {
                curNode->nextHeight = newPerson;
                newPerson->nextHeight = nullptr;
                prevNode = curNode;
                break;
            } else if(newPerson->height > curNode->height) {
                prevNode->nextHeight = newPerson;
                newPerson->nextHeight = curNode;
                prevNode = curNode;
                break;
            } else if(newPerson->height == curNode->height) {
                std::cout << "\t\t\tHEY_RIGHT_HERE!";
                if(newPerson->weight == curNode->weight || newPerson->weight > curNode->weight) {
                    if(curNode->nextHeight == nullptr) {
                        curNode->nextHeight = newPerson;
                        newPerson->nextHeight = nullptr;
                        prevNode = curNode;
                        break;
                    } else {
                        newPerson->nextHeight = curNode->nextHeight;
                        curNode->nextHeight = newPerson;
                        prevNode = curNode;
                        break;
                    }
                } else if(newPerson->weight < curNode->weight) {
                    prevNode->nextHeight = newPerson;
                    newPerson->nextHeight = curNode;
                    prevNode = curNode;
                    break;
                }
            } else if(curNode->nextHeight == nullptr) {
                if(newPerson->height == curNode->height) {
                    if(newPerson->weight < curNode->weight) {
                        prevNode->nextHeight = newPerson;
                        newPerson->nextHeight = curNode;
                        prevNode = curNode;
                        break;
                    } else if(newPerson->weight > curNode->weight || newPerson->weight == curNode->weight) {
                        newPerson->nextHeight = curNode->nextHeight;
                        curNode->nextHeight = newPerson;
                        prevNode = curNode;
                        break;
                    }
                } else {
                    curNode->nextHeight = newPerson;
                    newPerson->nextHeight = nullptr;
                    prevNode = curNode;
                    break;
                }
                prevNode = curNode;
                break;
            }
            prevNode = curNode;
        }
    }

    if(newPerson->weight < this->headWeightList->weight) {
        newPerson->nextWeight = this->headWeightList;
        this->headWeightList = newPerson;
    } else if(newPerson->weight > this->headWeightList->weight && this->headWeightList->nextWeight == nullptr) {
        this->headWeightList->nextWeight = newPerson;
        newPerson->nextWeight = nullptr;
    } else if(newPerson->weight == this->headWeightList->weight) {
        if(newPerson->height == this->headWeightList->height || newPerson->height < this->headWeightList->height) {
            newPerson->nextWeight = this->headWeightList->nextWeight;
            this->headWeightList->nextWeight = newPerson;
        } else if(newPerson->height > this->headWeightList->height) {
            newPerson->nextWeight = this->headWeightList;
            this->headWeightList = newPerson;
        }
    } else {
        Person *prevNode = this->headWeightList;
        for(Person *curNode = this->headWeightList->nextWeight; curNode != nullptr; curNode = curNode->nextWeight) {
            if(newPerson->weight > curNode->weight && curNode->nextWeight != nullptr) {
                prevNode = curNode;
                continue;
            } else if(newPerson->weight > curNode->weight && curNode->nextWeight == nullptr) {
                curNode->nextWeight = newPerson;
                newPerson->nextWeight = nullptr;
                prevNode = curNode;
                break;
            } else if(newPerson->weight < curNode->weight) {
                prevNode->nextWeight = newPerson;
                newPerson->nextWeight = curNode;
                prevNode = curNode;
                break;
            } else if(newPerson->weight == curNode->weight) {
                if(newPerson->height == curNode->height || newPerson->height < curNode->height) {
                    if(curNode->nextWeight == nullptr) {
                        curNode->nextWeight = newPerson;
                        newPerson->nextWeight = nullptr;
                        prevNode = curNode;
                        break;
                    } else {
                        newPerson->nextWeight = curNode->nextWeight;
                        curNode->nextWeight= newPerson;
                        prevNode = curNode;
                        break;
                    }
                } else if(newPerson->height > curNode->height) {
                    prevNode->nextWeight = newPerson;
                    newPerson->nextWeight = curNode;
                    prevNode = curNode;
                    break;
                }
            } else if(curNode->nextWeight == nullptr) {
                if(newPerson->weight == curNode->weight) {
                    if(newPerson->height > curNode->height) {
                        prevNode->nextWeight = newPerson;
                        newPerson->nextWeight = curNode;
                        prevNode = curNode;
                        break;
                    } else if(newPerson->height < curNode->height || newPerson->height == curNode->height) {
                        newPerson->nextWeight = curNode->nextWeight;
                        curNode->nextWeight = newPerson;
                        prevNode = curNode;
                        break;
                    }
                } else {
                    curNode->nextWeight = newPerson;
                    newPerson->nextWeight = nullptr;
                    prevNode = curNode;
                    break;
                }
                prevNode = curNode;
                break;
            }
            prevNode = curNode;
        }
    }

    size++;
    return true;
}

bool PersonList::remove(string first, string last) {
    Person *prevNode = nullptr;
    Person *nodeToDelete = nullptr;
    for(Person *curNode = headHeightList; curNode != nullptr; curNode = curNode->nextHeight) {
        if(curNode->first == first && curNode->last == last) {
            nodeToDelete = curNode;
            break;
        }
        prevNode = curNode;
    }

    if(prevNode == nullptr) {
        this->headHeightList = nodeToDelete->nextHeight;
    } else {
        prevNode->nextHeight = nodeToDelete->nextHeight;
    }

    prevNode = nullptr;
    for(Person *curNode = headWeightList; curNode != nullptr; curNode = curNode->nextWeight) {
        if(curNode->first == first && curNode->last == last) {
            break;
        }
        prevNode = curNode;
    }

    if(prevNode == nullptr) {
        this->headWeightList = nodeToDelete->nextWeight;
    } else {
        prevNode->nextWeight = nodeToDelete->nextWeight;
    }

    delete nodeToDelete;
    size--;

    return true;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast) {
    for(Person *curNode = headHeightList; curNode != nullptr; curNode = curNode->nextHeight) {
        if(curNode->first == first && curNode->last == last) {
            curNode->first = newFirst;
            curNode->last = newLast;
            return true;
        }
    }
    return false;
}

bool PersonList::updateHeight(string first, string last, int height) {
    int weight = 0;
    for(Person *curNode = headHeightList; curNode != nullptr; curNode = curNode->nextHeight) {
        if(curNode->first == first && curNode->last == last) {
            weight = curNode->weight;
            break;
        }
    }

    remove(first, last);
    add(first, last, height, weight);

    return true;
}

bool PersonList::updateWeight(string first, string last, int weight) {
    int height = 0;
    for(Person *curNode = headWeightList; curNode != nullptr; curNode = curNode->nextWeight) {
        if(curNode->first == first && curNode->last == last) {
            height = curNode->height;
            break;
        }
    }

    remove(first, last);
    add(first, last, height, weight);

    return true;
}

void PersonList::deepCopy(const PersonList &src) {
    if (src.headHeightList == nullptr || src.headWeightList == nullptr) {
        return;
    }

    size = src.size;

    Person *ptr = src.headHeightList;
    headHeightList = new Person(ptr->first, ptr->last, ptr->height, ptr->weight);
    Person *backOfList = headHeightList;
    for (ptr = src.headHeightList->nextHeight; ptr != nullptr; ptr = ptr->nextHeight) {
        Person *newPerson = new Person(ptr->first, ptr->last, ptr->height, ptr->weight);
        backOfList->nextHeight = newPerson;
        backOfList = newPerson;
        newPerson->nextHeight = nullptr;
    }

    ptr = src.headWeightList;
    for (Person *curHeight = headHeightList; curHeight != nullptr; curHeight = curHeight->nextHeight) {
        if (curHeight->first == ptr->first && curHeight->last == ptr->last) {
            headWeightList = curHeight;
        }
    }
    backOfList = headWeightList;
    for (ptr = src.headWeightList->nextWeight; ptr != nullptr; ptr = ptr->nextWeight) {
        for (Person *curHeight = headHeightList; curHeight != nullptr; curHeight = curHeight->nextHeight) {
            if (curHeight->first == ptr->first && curHeight->last == ptr->last) {
                backOfList->nextWeight = curHeight;
                backOfList = curHeight;
                curHeight->nextWeight = nullptr;
            }
        }
    }
}

void PersonList::clear() {
    while(headHeightList != nullptr) {
        remove(headHeightList->first, headHeightList->last);
    }
}

PersonList::~PersonList() {
    clear();
}

PersonList::PersonList(const PersonList &src) {
    headHeightList = nullptr;
    headWeightList = nullptr;
    deepCopy(src);
}

const PersonList &PersonList::operator=(const PersonList &src) {
    if(this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}
