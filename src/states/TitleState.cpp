#include <states/TitleState.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <utils/HSL.hpp>

namespace faod
{
    TitleState::TitleState(StateStack& stack, Context context) : State(stack, context)
    {
    }

    void TitleState::draw() {
        Context context = getContext();
        context.window_->clear(HSL(current.asMilliseconds()/10, .5, .3).toRGB());
    }

    bool TitleState::update(sf::Time delta) {
        current += delta;
        return false;
    }

    bool TitleState::handleEvent(const sf::Event& event) {
        if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
        {
            requestStackPush(States::ID::Game);
        }

        return false;
    }

}
