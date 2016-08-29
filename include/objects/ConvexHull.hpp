#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#define m_sign(x) ((x) >= 0 ? 1. : -1.)
#define PI 3.14159
namespace faod
{
    //Class Representing a ConvexHull.
    class ConvexHull
    {
        public:

            //returns a rectangle ConvexHull with width = wh.x and height = wh.y
            static ConvexHull boxHull(glm::vec2 wh);
            //returns an isocele triangle
            static ConvexHull triHull(float w, float h);

            ConvexHull(unsigned int len, glm::vec2 *points);
            ConvexHull(unsigned int len);

            //copy and assignment
            ConvexHull(const ConvexHull &c);
            ConvexHull& operator=(const ConvexHull &c) = delete;

            ~ConvexHull();

            void translate(glm::vec2 tr);
            void rotate(float orient); //Counter clockwise rotation in rad

            //returns bounding box for this object (x, y, w, h)
            glm::vec4 getBoundingBox() const;

            //true whenever this intersects with other
            bool intersects(const ConvexHull &other) const;
            
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;           
        private:
            unsigned int len_;
            glm::vec2 *points_;
    };
}
