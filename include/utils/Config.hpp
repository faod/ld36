#pragma once

#include <SFML/Window/Event.hpp>

// Serialisation engine
#include <cereal/cereal.hpp>

/*
    Serialisable config class (settings, keybindings, ...)
*/

namespace faod
{
    struct Config
    {
        // Key Bindings
        struct _KBS
        {
            sf::Keyboard::Key forward;
            sf::Keyboard::Key backward;
            sf::Keyboard::Key turnleft;
            sf::Keyboard::Key turnright;

            template <class Archive> void serialize(Archive &archive);
        } keyBindings;

        // Serialise the config to the given archive
        template <class Archive> void serialize(Archive &archive);

        // Load from config file
        void load(const char *filename, bool fallback_to_defaults);

        // Save to config file
        void save(const char *filename);

        // Loads default value
        void loadDefaults();
    };
}
