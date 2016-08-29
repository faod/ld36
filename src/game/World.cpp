#include <game/World.hpp>
#include <states/GameState.hpp>
#include <objects/Catapult.hpp>
#include <objects/Foe.hpp>
#include <objects/Projectile.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


namespace faod
{
    World::World(sf::RenderWindow& window, GameState &state, State::Context context, std::string mapname)
        : window_(window)
          ,view_(window.getDefaultView())
          ,owningstate_(&state)
          ,context_(context)
          ,mapname_(mapname)
          ,map_(nullptr)
          ,mapList_(context.maps_)
    {
        loadMap();
        loadTextures();
        buildScene();
    }

    void World::update(sf::Time delta)
    {

        while(!commandQueue_.isEmpty())
        {
            sceneGraph_.onCommand(commandQueue_.pop(), delta);
        }
        //then scenegraph
        sceneGraph_.update(delta);
    }

    void World::draw()
    {
        window_.clear(sf::Color(0 , 0 ,0));
        window_.setView(view_);
        view_.setCenter(catapult_->getPosition());
        window_.draw(*map_);
        window_.draw(sceneGraph_);

        //draw catapult power bar
        //frame rectangle
        sf::RectangleShape rect(sf::Vector2f(100., 20.));
        rect.setOutlineColor(sf::Color(255, 0, 0));
        rect.setOutlineThickness(3.);
        rect.setFillColor(sf::Color::Transparent);

        //power bar
        float size = ((catapult_->getCurrentForce() - catapult_->getForceMin()) / (catapult_->getForceMax() - catapult_->getForceMin())) * 100.;
        sf::RectangleShape power(sf::Vector2f(size, 20.));
        power.setFillColor(sf::Color::Yellow);

        rect.setPosition(sf::Vector2f(catapult_->getPosition().x - 50., catapult_->getPosition().y + 270.));
        power.setPosition(sf::Vector2f(catapult_->getPosition().x - 50., catapult_->getPosition().y + 270.));

        window_.draw(rect);
        window_.draw(power);
    }

    CommandQueue& World::getCommandQueue()
    {
        return commandQueue_;
    }

    void World::loadTextures()
    {
        //Load catapult spritesheet
        if(!context_.textures_->isIn("catapult"))
        {
            context_.textures_->load("catapult", "assets/sprites/Catapult.png");
        }
        if(!context_.textures_->isIn("foe"))
        {
            context_.textures_->load("foe", "assets/sprites/Foes.png");
        }
    }

    void World::buildScene()
    {
        /*
         * Then all the pickups
         */
        {
            tmx::ObjectGroup &obj = map_->GetObjectGroup("bonuses");
            auto &objects = obj.GetObjects();

            for(auto it = objects.begin(); it != objects.end(); ++it)
            {
                //Pumpkins
                if(it->GetName() == "pumpkin")
                {
                    Pumpkin *pump = nullptr;
                    float x = it->GetX();
                    float y = it->GetY();
                    it->visible = false;
                    sf::Texture *text = const_cast<sf::Texture*>(it->tile_.GetTexture());
                    pump = new Pumpkin(*text, x + 6, y - 10, &manager_);
                    Pumpkin::Smart_ptr ptr(pump);
                    sceneGraph_.attachChild(ptr);
                    manager_.addCollidable(std::static_pointer_cast<CollidableObject>(ptr));
                }
                //Rocks
                if(it->GetName() == "rock")
                {
                    Rock *pump = nullptr;
                    float x = it->GetX();
                    float y = it->GetY();
                    it->visible = false;
                    sf::Texture *text = const_cast<sf::Texture*>(it->tile_.GetTexture());
                    pump = new Rock(*text, x + 6, y - 10, &manager_);
                    Rock::Smart_ptr ptr(pump);
                    sceneGraph_.attachChild(ptr);
                    manager_.addCollidable(std::static_pointer_cast<CollidableObject>(ptr));
                }
            }

        }
        /*
         * End of loading pickups
         */
        {
            //First thing first, add the catapult
            //Find catapult position on map
            tmx::ObjectGroup &obj = map_->GetObjectGroup("spawns");
            auto &objects = obj.GetObjects();
            float x, y;

            for(auto it = objects.begin(); it != objects.end(); ++it)
            {
                x = it->GetX();
                y = it->GetY();
                if(it->GetName() == "catapult")
                {
                    catapult_ = new Catapult(context_.textures_->get("catapult"), context_.fonts_, &manager_, x, y);
                    Catapult::Smart_ptr ptr(catapult_);
                    sceneGraph_.attachChild(std::move(ptr));
                    manager_.addCollidable(std::static_pointer_cast<CollidableObject>(ptr));
                }
                else
                {
                    Foe *foe = new Foe(this, context_.textures_->get("foe"), 3, x, y, it->rotation_, &manager_);
                    Foe::Smart_ptr ptr(foe);
                    sceneGraph_.attachChild(ptr);
                    manager_.addCollidable(std::static_pointer_cast<CollidableObject>(ptr));
                }
            }
        }

    }
    void World::loadMap()
    {
        //If map is not already in the manager
        if(!mapList_->isIn(mapname_))
        {
            mapList_->load(mapname_, mapname_);
        }
        map_ = &mapList_->get(mapname_);
        map_->ShowObjects();
        //continue loading map
    }

    Catapult* World::getCatapult()
    {
        return catapult_;
    }
}
