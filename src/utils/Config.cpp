#include <utils/Config.hpp>

#include <cereal/archives/xml.hpp>

#include <fstream>

namespace faod
{
    template <class Archive> void Config::_KBS::serialize(Archive &archive)
    {
        archive(CEREAL_NVP(forward),
                CEREAL_NVP(backward),
                CEREAL_NVP(turnleft),
                CEREAL_NVP(turnright));
    }

    template <class Archive> void Config::serialize(Archive &archive)
    {
        archive(CEREAL_NVP(keyBindings));
    }

    void Config::load(const char *filename, bool fallback_to_defaults)
    {
        std::ifstream is(filename);
        if (is.good())
        {
            try
            {
                cereal::XMLInputArchive bis(is);
                serialize(bis);
            }
            catch (cereal::Exception)
            {
                if (fallback_to_defaults)
                {
                    loadDefaults();
                }
            }
        }
        else if (fallback_to_defaults)
        {
            loadDefaults();
        }
    }

    void Config::save(const char *filename)
    {
        std::ofstream os(filename);
        cereal::XMLOutputArchive bos(os);
        serialize(bos);
    }

    void Config::loadDefaults()
    {
        keyBindings.forward   = sf::Keyboard::Up;
        keyBindings.backward  = sf::Keyboard::Down;
        keyBindings.turnleft  = sf::Keyboard::Left;
        keyBindings.turnright = sf::Keyboard::Right;
    }

}
