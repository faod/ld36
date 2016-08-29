#include <utils/Animation.hpp>

#include <cassert>

namespace faod
{

    Animation::Frame::Frame(sf::Sprite sprite, int duration):
        sprite(sprite),
        duration(duration)
    {}



    Animation::Animation(bool loop):
        loop_(loop),
        totalTime_(0l),
        elapsTime_(0L)
    {}

    void Animation::addFrame(sf::Sprite sprite, unsigned int duration_ms)
    {
        frames_.push_back(Frame(sprite, duration_ms));
        totalTime_ += duration_ms;
    }

    sf::Sprite* Animation::getFrame(unsigned int id)
    {
        if (id < frames_.size())
        {
            return &(frames_[id].sprite);
        }
        return NULL;
    }

    void Animation::reset()
    {
        elapsTime_ = 0L;
    }

    void Animation::update(unsigned int delta_t_ms)
    {
        elapsTime_ += delta_t_ms;
    }

    sf::Sprite* Animation::getCurrentSprite()
    {
        assert(frames_.size());
        if (loop_ || elapsTime_ <= totalTime_)
        {
            unsigned long eltime = elapsTime_;
            if (loop_)
            {
                eltime = eltime % totalTime_;
            }

            std::vector<Frame>::iterator frame_it;
            unsigned long sumtime = 0L;
            for (frame_it = frames_.begin(); frame_it < frames_.end(); frame_it++)
            {
                sumtime += frame_it->duration;
                if (sumtime > eltime)
                {
                    return &(frame_it->sprite);
                }
            }
        }
        return NULL;
    }

    bool Animation::animate(sf::RenderTarget& target, sf::RenderStates states)
    {
        sf::Sprite *sprite = getCurrentSprite();
        if (sprite)
        {
            target.draw(*sprite, states);
        }
        return loop_ || sprite != NULL;
    }

}
