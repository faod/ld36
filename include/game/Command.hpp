#pragma once

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

namespace faod
{

    class SceneNode;

    struct Command
    {
            Command();

            std::function<void(SceneNode&, sf::Time)>   action_;
            unsigned int                                category_;
    };

    template <typename GameObject, typename Function>
    std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
    {
        return [=] (SceneNode& node, sf::Time delta)
        {
            //attempt to cast
            assert(dynamic_cast<GameObject*>(&node) != nullptr);

            //Downcast
            fn(static_cast<GameObject&>(node), delta);
        };
    }
}
