#include <states/States.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <utils/HSL.hpp>

namespace faod
{

    void FooBar::draw() {
        Context context = getContext();/*
        int hue = (int)(current.asSeconds())*100;
        context.window_->clear(HSL(hue, .5, .5).toRGB());*/
        context.window_->clear(sf::Color((int)(current.asSeconds())*10, 0, 0));
    }

    bool FooBar::update(sf::Time delta) {
        current += delta;
        return false;
    }

    bool FooBar::handleEvent(const sf::Event& event) {
        (void) event;
        return false;
    }

}
