#include <states/TitleState.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <utils/HSL.hpp>

namespace faod
{
    TitleState::TitleState(StateStack& stack, Context context) : State(stack, context)
    {
        // Background image
        if(!context.textures_->isIn("title_bg"))
        {
            context.textures_->load("title_bg", "assets/title.png");
        }

        //menu prompt initialisation
        menuprompt_.setFont(context.fonts_->get("pixel"));
        menuprompt_.setString("Press [space] to start the game");
        menuprompt_.setCharacterSize(24);

        //origin at center
        sf::FloatRect bounds = menuprompt_.getLocalBounds();
        menuprompt_.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
        menuprompt_.setPosition(context.window_->getSize().x /2. , context.window_->getSize().y / 2.);
    }

    void TitleState::draw() {
        Context context = getContext();
        context.window_->clear(HSL(current_.asMilliseconds()/10, .5, .3).toRGB());

        // Draw background image
        sf::Transform sc; sc = sc.scale(5.0, 5.0);
        sf::Transform tr; tr = tr.translate(40.0, 30.0);
        context.window_->draw(sf::Sprite(context.textures_->get("title_bg")), sf::RenderStates(tr * sc));

        //draw menuprompt
        context.window_->draw(menuprompt_);
    }

    bool TitleState::update(sf::Time delta) {
        current_ += delta;
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
