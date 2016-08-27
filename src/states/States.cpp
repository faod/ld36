#include <states/States.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <utils/HSL.hpp>

namespace faod
{

    void FooBar::draw() {
        Context context = getContext();
        context.window_->clear(HSL(current.asMilliseconds()/10, .5, .3).toRGB());
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
