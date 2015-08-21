#include "PlayerProfile.h"

#include <boost/algorithm/string.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// ----------------------------------------------------------------------------
struct PlayerProfile_Struct
{
  unsigned int checksum;
  short gender;
  std::string name;
};

// ----------------------------------------------------------------------------
int main()
{

  PlayerProfile_Struct profile;
  profile.checksum = 0;
  profile.gender = 1;
  profile.name = "ricky";
  
  // Use memcpy --------
  // Doesnt work well for complicated structures. Eg. those with 
  // pointers as fields. Dont know size at compile time...
  // Painful work around would be to do multiple memcpy calls

  // serialize
  const unsigned int size = 2 * sizeof(unsigned int) + sizeof(short);
  char *target = new char[size + profile.name.length()+1];
  memcpy(target, static_cast<void*>(&profile), size);
  memcpy(target+size, static_cast<void*>(&profile.name), profile.name.length()+1);  

  // Use string separators --------
  std::string output = 
    std::to_string(profile.checksum) + "|" + 
    std::to_string(profile.gender) + "|" + 
    profile.name;
  
  std::vector<std::string> fields;
  boost::split(fields, output, boost::is_any_of("|"));

  profile.checksum = std::stoi(fields.at(0));
  profile.gender = std::stoi(fields.at(1));
  profile.name = fields.at(2);

  // Boost serialization ---------------
  std::map<std::string,int> scores;
  scores["ricky"]=10;
  

  PlayerProfile pProfile(0,"ricky",scores);
  
  // serialize and write to file;
  std::ofstream ofs("serializedProfile");
  boost::archive::text_oarchive oa(ofs);
  oa << pProfile;

  // deserialize
  {
    std::ifstream ifs("serializedProfile");
    //boost::archive::text_iarchive ia(ifs);
    //ia >> pProfile;
  }

  return 0;
}
