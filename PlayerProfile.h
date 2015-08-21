#ifndef PLAYERPROFILE_H
#define PLAYERPROFILE_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <string>
#include <map>


// ----------------------------------------------------------------------------
class PlayerProfile
{
private:
  typedef std::map<std::string, int> ScoreMap;

  unsigned int checksum;
  std::string name;
  ScoreMap highscores;

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    // Simply list all the field to be serialized/deserialized
    ar & checksum;
    ar & name;
    ar & highscores;
  }

public:
  PlayerProfile(){};
  PlayerProfile(int _checksum, std::string _name, ScoreMap _highscores) :
    checksum(_checksum), name(_name), highscores(_highscores) {}

};

#endif
