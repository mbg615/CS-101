#include <iostream>

#include "zipcode.h"

using namespace std;

/*
enum class CompareType {
    LessZip,
    LessCityState,
    LessStateCity,
    LessLatLonState,
    LessLonLatState
};
*/
// Complete this method by implementing the comparison logic
bool ZipCode::compare(ZipCode &rhs, ZipCode::CompareType t) {
    switch(t) {
        case ZipCode::CompareType::LessZip:
            return this->getZip() < rhs.getZip();
        case ZipCode::CompareType::LessCityState:
            if(this->getCity() < rhs.getCity()) return true;
            if(this->getCity() > rhs.getCity()) return false;
            if(this->getState() < rhs.getState()) return true;
            if(this->getState() > rhs.getState()) return false;
        case ZipCode::CompareType::LessStateCity:
            if(this->getState() < rhs.getState()) return true;
            if(this->getState() > rhs.getState()) return false;
            if(this->getCity() < rhs.getCity()) return true;
            if(this->getCity() > rhs.getCity()) return false;
        case ZipCode::CompareType::LessLatLonState:
            if(this->getLat() < rhs.getLat()) return true;
            if(this->getLat() > rhs.getLat()) return false;
            if(this->getLon() < rhs.getLon()) return true;
            if(this->getLon() > rhs.getLon()) return false;
            return this->getState() < rhs.getState();
        case ZipCode::CompareType::LessLonLatState:
            if(this->getLon() < rhs.getLon()) return true;
            if(this->getLon() > rhs.getLon()) return false;
            if(this->getLat() < rhs.getLat()) return true;
            if(this->getLat() > rhs.getLat()) return false;
            return this->getState() < rhs.getState();
        default:
            return false;
    }
}

// Do not edit below this line

ZipCode::ZipCode(int zip, string city, string state, int lat, int lon) {
    this->zip = zip;
    this->city = city;
    this->state = state;
    this->lat = lat;
    this->lon = lon;
}

void ZipCode::print() {
    cout << zip << "\t" << city << "\t";
    if (city.length() < 8) cout << "\t";
    cout << state << "\t" << lat << "\t"<< lon;
}

int ZipCode::getZip() {
    return zip;
}

string ZipCode::getCity() {
    return city;
}

string ZipCode::getState() {
    return state;
}

int ZipCode::getLat() {
    return lat;
}

int ZipCode::getLon() {
    return lon;
}
