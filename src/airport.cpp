#include "airport.h"

Airport::Airport(int id, std::string name, std::string iata, double latitude, double longitude) : id(id), name(name), 
                                                                                                  iata(iata), latitude(latitude), 
                                                                                                  longitude(longitude) {
                                                                                                                                                                                        
}

std::ostream& operator<<(std::ostream& os, const Airport& ap) {
    os << "ID: " << ap.id << '\n' << "Name: " << ap.name << '\n'
       << "IATA: " << ap.iata << '\n' << "Latitude: " << ap.latitude << '\n'
       << "Longitude: " << ap.longitude << '\n' << "Num outgoing: " << ap.dest.size();
    return os;
}
