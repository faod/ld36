#pragma once

#include <glm/glm.hpp>

#define m_sign(x) ((x) >= 0 ? 1. : -1.)

namespace faod
{
    //Class Representing a ConvexHull.
    class ConvexHull
    {
        public:
            ConvexHull(unsigned int len, glm::vec2 *points);
            ConvexHull(unsigned int len);

            //copy and assignment
            ConvexHull(const ConvexHull &c);
            ConvexHull& operator=(const ConvexHull &c) = delete;

            ~ConvexHull();

            void translate(glm::vec2 tr);
            void rotate(float orient); //Counter clockwise rotation in rad

            bool intersects(const ConvexHull &other);

        private:
            unsigned int len_;
            glm::vec2 *points_;
    };
}
