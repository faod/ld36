#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace faod
{
    class Animation
    {
        private:
            struct Frame
            {
                sf::Sprite sprite;
                int duration;
                Frame(sf::Sprite sprite, int duration);
            };
            std::vector<Frame> frames_;
            bool loop_;
            unsigned long totalTime_;
            unsigned long elapsTime_;

        public:
            // loop to restart the animation once finished.
            Animation(bool loop = true);
            // Append a new frame to this animation
            void addFrame(sf::Sprite sprite, unsigned int duration_ms);
            // Returns the sprite of the requested frame, or NULL if out of bounds
            sf::Sprite* getFrame(unsigned int id);

            // Update animation, append the given delta time (in ms) to internal elapsed_time
            void update(unsigned int delta_t_ms);
            // Resets the internal timestamp
            void reset();
            // Used by animate(), if you don't want to delegate ... returns NULL if animation is over
            sf::Sprite* getCurrentSprite();
            // Draws this animation. returns true is still animating (always true of loop is true)
            bool animate(sf::RenderTarget& target, sf::RenderStates states);
    };
}
